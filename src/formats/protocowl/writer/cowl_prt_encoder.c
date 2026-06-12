/**
 * @author Valerio Di Ceglie
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "../cowl_prt_constants.h"
#include "../cowl_prt_index.h"

#include "cowl.h"
#include "cowl_anon_ind.h"
#include "cowl_datatype.h"
#include "cowl_impl.h"
#include "cowl_object.h"
#include "cowl_ontology_private.h"
#include "cowl_ret.h"
#include "cowl_string.h"
#include "cowl_string_private.h"
#include "cowl_xsd_vocab.h"
#include "ulib.h"
#include "unumber.h"
#include "ustream_varint.h"
#include "ustring.h"
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct CowlPRTEncoder {
    CowlPRTIndex index;
    CowlOntology *to_flush;
    UOStream *stream;
    ulib_uint index_size;
    ulib_uint cur_size;
    cowl_ret state;
    bool encode_anon;
} CowlPRTEncoder;

static cowl_ret encoder_init(CowlPRTEncoder *e) {
    *e = (CowlPRTEncoder){
        .encode_anon = true,
        .index_size = COWL_PROTOCOWL_INDEX_SIZE_UNBOUNDED,
    };
    return e->state = cowl_prt_index_init(&e->index, true);
}

static void encoder_deinit(CowlPRTEncoder *e) {
    cowl_release(e->to_flush);
    cowl_prt_index_deinit(&e->index);
}

static cowl_ret flush_state_empty(CowlPRTEncoder *e) {
    cowl_release(e->to_flush);
    if (!(e->to_flush = cowl_ontology())) {
        e->state = COWL_ERR_MEM;
        goto end;
    }
    cowl_ontology_disable_indexing(e->to_flush);
    e->cur_size = 0;
end:
    return e->state;
}

static cowl_ret encoder_reset(CowlPRTEncoder *e, bool prefixes) {
    if ((e->state = cowl_prt_index_reset_ids(&e->index))) return e->state;
    if (prefixes && (e->state = cowl_prt_index_reset_prefixes(&e->index))) return e->state;
    return flush_state_empty(e);
}

static inline cowl_ret encoder_state(CowlPRTEncoder *e) {
    return e->state ? e->state : cowl_ret_from_ulib(e->stream->state);
}

static cowl_ret encoder_add_prefix(CowlPRTEncoder *e, CowlString *ns, CowlString *prefix) {
    return e->state = cowl_prt_index_add_prefix(&e->index, ns, prefix);
}

static cowl_ret encoder_add_primitive(CowlPRTEncoder *e, CowlAnyPrimitive *primitive) {
    return e->state = cowl_prt_index_add_primitive(&e->index, primitive);
}

static cowl_ret for_each_primitive(void *ctx, CowlAnyPrimitive *primitive) {
    return encoder_add_primitive(ctx, primitive);
}

static cowl_ret populate_index(CowlPRTEncoder *e, CowlOntology *onto) {
    ulib_uint const primitive_count = cowl_ontology_primitive_count(onto, COWL_PF_ALL);
    if (cowl_prt_index_reserve_ids(&e->index, primitive_count)) goto err;

    CowlPrefixMap *pm = cowl_ontology_get_prefix_map(onto);
    CowlTable *prefix_ns_map = cowl_prefix_map_get_table(pm, false);

    cowl_table_foreach (prefix_ns_map, entry) {
        if (encoder_add_prefix(e, *entry.val, *entry.key)) goto err;
    }

    CowlIRI *iri = cowl_ontology_get_iri(onto);
    if (iri && encoder_add_primitive(e, iri)) goto err;

    iri = cowl_ontology_get_version(onto);
    if (iri && encoder_add_primitive(e, iri)) goto err;

    CowlIterator iter = { e, for_each_primitive };
    if (cowl_ontology_iterate_primitives(onto, COWL_PF_ALL, &iter)) goto err;
    if (cowl_ontology_iterate_imports(onto, &iter)) goto err;

    return COWL_OK;

err:
    cowl_prt_index_deinit(&e->index);
    return COWL_ERR_MEM;
}

static void write_bytes(CowlPRTEncoder *e, void const *data, ulib_uint length) {
    uostream_write_all(e->stream, data, length, NULL);
}

static void write_varint(CowlPRTEncoder *e, ulib_uint value) {
    uostream_write_varint(e->stream, value, NULL);
}

static void encode_object(CowlPRTEncoder *e, CowlAny *obj);

static void uostream_write_prt_cstring(UOStream *o, char const *string, ulib_uint length) {
    uostream_write_varint(o, length, NULL);
    if (length) uostream_write_all(o, string, length, NULL);
}

static void uostream_write_prt_ustring(UOStream *o, UString const *string) {
    uostream_write_prt_cstring(o, ustring_data(*string), ustring_length(*string));
}

static void uostream_write_prt_string(UOStream *o, CowlString *string) {
    uostream_write_prt_ustring(o, cowl_string_get_raw(string));
}

static void encode_string(CowlPRTEncoder *e, CowlString *string) {
    uostream_write_prt_string(e->stream, string);
}

static void encode_id_offset(CowlPRTEncoder *e, CowlIRIOrAnonInd *id, ulib_uint offset) {
    ulib_uint idx = cowl_prt_index_get_id_idx(&e->index, id);
    if (idx == COWL_PRT_NOT_FOUND) {
        e->state = COWL_ERR;
        return;
    }
    write_varint(e, idx + offset);
}

static void encode_id(CowlPRTEncoder *e, CowlIRIOrAnonInd *id) {
    encode_id_offset(e, id, 0);
}

static void encode_uvec(CowlPRTEncoder *e, UVec(CowlObjectPtr) const *vec,
                        void (*encode)(CowlPRTEncoder *, void *)) {
    write_varint(e, uvec_count(CowlObjectPtr, vec));
    uvec_foreach (CowlObjectPtr, vec, obj) {
        encode(e, *obj.item);
    }
}

static void encode_vector(CowlPRTEncoder *e, CowlVector *vec) {
    encode_uvec(e, cowl_vector_get_data(vec), encode_object);
}

static void encode_datatype(CowlPRTEncoder *e, CowlDatatype *datatype, bool is_data_range) {
    ulib_uint offset = is_data_range ? COWL_DRT_COUNT - 1 : 0;
    encode_id_offset(e, cowl_datatype_get_iri(datatype), offset);
}

static CowlPRTLiteralValueFormat encode_literal_int(UOStream *o, ulib_int val) {
    if (val < 0) {
        uostream_write_svarint(o, val, NULL);
        return COWL_LVF_INT;
    }
    uostream_write_varint(o, (ulib_uint)val, NULL);
    return COWL_LVF_UINT;
}

static CowlPRTLiteralValueFormat encode_literal_maybe_int(UOStream *o, CowlString *string) {
    ulib_int val;
    return cowl_string_to_int(string, &val, 10) ? COWL_LVF_STRING : encode_literal_int(o, val);
}

static ulib_ret bool_value(CowlString *string, ulib_byte *out) {
    UString const raw = *cowl_string_get_raw(string);
    CowlPRTLiteralBool val = 0;
    ulib_ret ret = ULIB_OK;
    if (ustring_equals(raw, ustring_literal("true"))) {
        val = COWL_LB_TRUE;
    } else if (ustring_equals(raw, ustring_literal("false"))) {
        val = COWL_LB_FALSE;
    } else {
        ret = ULIB_ERR;
    }
    if (ret == ULIB_OK && out) *out = (ulib_byte)val;
    return ret;
}

static CowlPRTLiteralValueFormat encode_literal_maybe_bool(UOStream *o, CowlString *string) {
    ulib_byte val;
    if (bool_value(string, &val)) return encode_literal_maybe_int(o, string);
    uostream_write(o, &val, 1, NULL);
    return COWL_LVF_BOOL;
}

static CowlPRTLiteralValueFormat
encode_literal_fixed_point(UOStream *o, ulib_int whole, ulib_uint frac) {
    uostream_write_svarint(o, whole, NULL);
    uostream_write_varint(o, frac, NULL);
    return COWL_LVF_FIXED_POINT;
}

static CowlPRTLiteralValueFormat
encode_literal_e_notation(UOStream *o, ulib_int whole, ulib_uint frac, ulib_int exp) {
    encode_literal_fixed_point(o, whole, frac);
    uostream_write_svarint(o, exp, NULL);
    return COWL_LVF_E_NOTATION;
}

static ulib_uint parse_uint_reverse(char const *src, char **end) {
    ulib_uint ret = 0;
    char *last = (char *)src;
    while (isdigit(*last)) ++last;

    for (char const *p = last - 1; p >= src; --p) {
        ulib_uint d = (ulib_uint)(*p - '0');
        ret = (ret * 10U) + d;
    }
    if (end) *end = last;
    return ret;
}

static CowlPRTLiteralValueFormat encode_literal_maybe_dec(UOStream *o, CowlString *string) {
    char const *s = cowl_string_get_cstring(string);
    ulib_uint len = cowl_string_get_length(string);
    char const *const max = s + len;
    char *end;
    ulib_int whole;
    ulib_uint frac;
    ulib_int exp;

    // Whole part
    whole = ulib_str_to_int(s, &end, 10);
    if (end == s) goto err;
    if (end == max) return encode_literal_int(o, whole);

    // Dot
    if (*end != '.' || (end + 1 == max)) goto err;

    // Fractional part
    s = end + 1;
    frac = parse_uint_reverse(s, &end);
    if (end == s) goto err;
    if (end == max) return encode_literal_fixed_point(o, whole, frac);

    // E
    if ((*end != 'E') || (end + 1 == max)) goto err;

    // Exponent part
    s = end + 1;
    exp = ulib_str_to_int(s, &end, 10);
    if (end == s || end != max) goto err;
    return encode_literal_e_notation(o, whole, frac, exp);

err:
    return COWL_LVF_STRING;
}

static inline bool dt_in(CowlDatatype *dt, CowlDatatype *const *dts, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (dt == dts[i]) return true;
    }
    return false;
}

typedef enum CowlPRTDatatypeGroup {
    COWL_PRT_DG_STRING = 0,
    COWL_PRT_DG_BOOL,
    COWL_PRT_DG_INT,
    COWL_PRT_DG_DEC,
} CowlPRTDatatypeGroup;

static void encode_literal_header_value(CowlPRTEncoder *e, CowlPRTLiteralType type,
                                        CowlPRTDatatypeGroup group, CowlString *value) {
    UOStream o;
    UStrBuf buf = ustrbuf();
    CowlPRTLiteralValueFormat fmt = COWL_LVF_STRING;
    ulib_byte header = (ulib_byte)type;

    if (uostream_to_strbuf(&o, &buf)) {
        e->state = COWL_ERR_MEM;
        goto end;
    }

    switch (group) {
        case COWL_PRT_DG_BOOL: fmt = encode_literal_maybe_bool(&o, value); break;
        case COWL_PRT_DG_INT: fmt = encode_literal_maybe_int(&o, value); break;
        case COWL_PRT_DG_DEC: fmt = encode_literal_maybe_dec(&o, value); break;
        default: break;
    }

    if (fmt == COWL_LVF_STRING) {
        write_bytes(e, &header, 1);
        encode_string(e, value);
    } else {
        header |= (ulib_byte)(fmt << COWL_PRT_VALUE_FORMAT_OFFSET);
        write_bytes(e, &header, 1);
        write_bytes(e, ustrbuf_data(&buf), ustrbuf_length(&buf));
    }

end:
    uostream_deinit(&o);
    ustrbuf_deinit(&buf);
}

static CowlPRTDatatypeGroup datatype_group(CowlDatatype *dt) {
    CowlXSDDatatypeVocab const *const v = &cowl_xsd_vocab()->dt;
    if (dt == v->boolean) return COWL_PRT_DG_BOOL;
    CowlDatatype *const int_dts[] = {
        v->integer,       v->xsd_int,          v->unsigned_int,     v->positive_int,
        v->negative_int,  v->non_positive_int, v->non_negative_int, v->xsd_long,
        v->unsigned_long, v->xsd_short,        v->unsigned_short,   v->byte,
        v->unsigned_byte
    };
    if (dt_in(dt, int_dts, ulib_array_count(int_dts))) return COWL_PRT_DG_INT;
    CowlDatatype *const dec_dts[] = { v->xsd_float, v->xsd_double, v->decimal };
    if (dt_in(dt, dec_dts, ulib_array_count(dec_dts))) return COWL_PRT_DG_DEC;
    return COWL_PRT_DG_STRING;
}

static CowlPRTLiteralType
literal_type(CowlDatatype *dt, CowlString *lang, CowlPRTDatatypeGroup *group) {
    if (lang) return COWL_OLT_STRING_LITERAL_LANGUAGE;
    if (dt == cowl_xsd_vocab()->dt.string) return COWL_OLT_STRING_LITERAL;
    *group = datatype_group(dt);
    return COWL_OLT_TYPED_LITERAL;
}

static void encode_literal(CowlPRTEncoder *e, CowlLiteral *literal) {
    CowlDatatype *dt = cowl_literal_get_datatype(literal);
    CowlString *value = cowl_literal_get_value(literal);
    CowlString *lang = cowl_literal_get_lang(literal);

    CowlPRTDatatypeGroup group = COWL_PRT_DG_STRING;
    CowlPRTLiteralType const type = literal_type(dt, lang, &group);
    encode_literal_header_value(e, type, group, value);

    switch (type) {
        case COWL_OLT_STRING_LITERAL_LANGUAGE: encode_string(e, lang); break;
        case COWL_OLT_TYPED_LITERAL: encode_datatype(e, dt, false); break;
        default: break;
    }
}

static void encode_facet_restr(CowlPRTEncoder *e, CowlFacetRestr *restr) {
    encode_id(e, cowl_facet_restr_get_facet(restr));
    encode_literal(e, cowl_facet_restr_get_value(restr));
}

static void encode_named_ind(CowlPRTEncoder *e, CowlNamedInd *ind) {
    encode_id(e, cowl_named_ind_get_iri(ind));
}

static void encode_class(CowlPRTEncoder *e, CowlClass *class, bool is_expression) {
    ulib_uint offset = is_expression ? COWL_CET_COUNT - 1 : 0;
    encode_id_offset(e, cowl_class_get_iri(class), offset);
}

static void encode_obj_prop(CowlPRTEncoder *e, CowlObjProp *prop, bool is_expression) {
    ulib_uint offset = is_expression ? 1 : 0;
    encode_id_offset(e, cowl_obj_prop_get_iri(prop), offset);
}

static void encode_inv_obj_prop(CowlPRTEncoder *e, CowlAnyObjPropExp *prop) {
    write_varint(e, 0);
    encode_obj_prop(e, cowl_inv_obj_prop_get_prop(prop), false);
}

static void encode_data_prop(CowlPRTEncoder *e, CowlDataProp *prop) {
    encode_id(e, cowl_data_prop_get_iri(prop));
}

static void encode_annot_prop(CowlPRTEncoder *e, CowlAnnotProp *prop) {
    encode_id(e, cowl_annot_prop_get_iri(prop));
}

static void encode_annot_value(CowlPRTEncoder *e, CowlAnyAnnotValue *value) {
    if (cowl_annot_value_get_type(value) == COWL_AVT_LITERAL) {
        write_varint(e, 0);
        encode_literal(e, value);
    } else {
        encode_id_offset(e, value, 1);
    }
}

static void encode_annotation(CowlPRTEncoder *e, CowlAnnotation *annot) {
    CowlIRI *iri = cowl_annot_prop_get_iri(cowl_annotation_get_prop(annot));
    CowlVector *annotations = cowl_annotation_get_annot(annot);

    if (annotations) {
        write_varint(e, 0);
        encode_id(e, iri);
    } else {
        encode_id_offset(e, iri, 1);
    }

    encode_annot_value(e, cowl_annotation_get_value(annot));
    if (annotations) encode_vector(e, annotations);
}

static void encode_card_restr(CowlPRTEncoder *e, CowlAny *restr) {
    CowlClsExpType type = cowl_cls_exp_get_type(restr) - 1;
    write_varint(e, type);

    ulib_uint card = (cowl_get_uint_field(restr) << 1) | cowl_has_opt_field(restr);
    write_varint(e, card);

    unsigned count;
    CowlAny **fields = cowl_get_fields(restr, true, &count);

    for (unsigned i = 0; i < count; ++i) {
        encode_object(e, fields[i]);
    }
}

static void encode_decl_axiom(CowlPRTEncoder *e, CowlDeclAxiom *axiom) {
    CowlAnyEntity *entity = cowl_decl_axiom_get_entity(axiom);
    CowlVector *annot = cowl_axiom_get_annot(axiom);

    ulib_byte header = (ulib_byte)(COWL_PRT_FIRST_AXIOM_FRAME + cowl_entity_get_type(entity));
    if (annot) header |= COWL_PRT_AXIOM_ANNOT_BITMASK;

    write_bytes(e, &header, sizeof(header));
    encode_id(e, cowl_entity_get_iri(entity));
    if (annot) encode_vector(e, annot);
}

static ulib_byte axiom_header(CowlObjectType type, bool annot, bool utility) {
    ulib_byte header = (type - COWL_OT_FIRST_A) + (COWL_ET_COUNT - 1) + COWL_PRT_FIRST_AXIOM_FRAME;
    header |= utility << COWL_PRT_AXIOM_UTLITY_OFFSET;
    header |= annot << COWL_PRT_AXIOM_ANNOT_OFFSET;
    return header;
}

static ulib_byte cls_exp_header(CowlObjectType type) {
    return (type - COWL_OT_FIRST_CE) - 1;
}

static ulib_byte data_range_header(CowlObjectType type) {
    return (type - COWL_OT_FIRST_DR) - 1;
}

static void encode_construct_body(CowlPRTEncoder *e, CowlAny *obj) {
    unsigned count;
    CowlAny **fields = cowl_get_fields(obj, true, &count);
    for (unsigned i = 0; i < count; i++) {
        encode_object(e, fields[i]);
    }
}

static void encode_axiom_default(CowlPRTEncoder *e, CowlAnyAxiom *axiom) {
    ulib_byte const header = axiom_header(cowl_get_type(axiom), cowl_axiom_get_annot(axiom), false);
    write_bytes(e, &header, sizeof(header));
    encode_construct_body(e, axiom);
}

static void encode_cls_exp_default(CowlPRTEncoder *e, CowlAnyClsExp *exp) {
    write_varint(e, cls_exp_header(cowl_get_type(exp)));
    encode_construct_body(e, exp);
}

static void encode_data_range_default(CowlPRTEncoder *e, CowlAnyDataRange *range) {
    write_varint(e, data_range_header(cowl_get_type(range)));
    encode_construct_body(e, range);
}

static void encode_datatype_def_axiom(CowlPRTEncoder *e, CowlDatatypeDefAxiom *axiom) {
    CowlDatatype *dt = cowl_datatype_def_axiom_get_datatype(axiom);
    CowlDataRange *dr = cowl_datatype_def_axiom_get_range(axiom);
    CowlVector *annot = cowl_axiom_get_annot(axiom);

    ulib_byte const header = axiom_header(COWL_OT_A_DATATYPE_DEF, annot, false);
    write_bytes(e, &header, sizeof(header));
    encode_datatype(e, dt, false);
    encode_object(e, dr);
    if (annot) encode_vector(e, annot);
}

static void encode_sub_obj_prop_axiom(CowlPRTEncoder *e, CowlSubObjPropAxiom *axiom) {
    bool is_chain = cowl_get_type(cowl_sub_obj_prop_axiom_get_sub(axiom)) == COWL_OT_VECTOR;
    ulib_byte header = axiom_header(COWL_OT_A_SUB_OBJ_PROP, cowl_axiom_get_annot(axiom), is_chain);
    write_bytes(e, &header, sizeof(header));
    encode_construct_body(e, axiom);
}

static void encode_obj_quant(CowlPRTEncoder *e, CowlObjectType type, CowlObjQuant *exp) {
    write_varint(e, cls_exp_header(type));
    encode_object(e, cowl_obj_quant_get_prop(exp));
    encode_object(e, cowl_obj_quant_get_filler(exp));
}

static void encode_data_quant(CowlPRTEncoder *e, CowlObjectType type, CowlDataQuant *exp) {
    write_varint(e, cls_exp_header(type));
    encode_object(e, cowl_data_quant_get_prop(exp));
    encode_object(e, cowl_data_quant_get_range(exp));
}

static void encode_datatype_restr(CowlPRTEncoder *e, CowlDatatypeRestr *restr) {
    write_varint(e, data_range_header(COWL_OT_DR_DATATYPE_RESTR));
    encode_datatype(e, cowl_datatype_restr_get_datatype(restr), false);
    encode_vector(e, cowl_datatype_restr_get_restrictions(restr));
}

static void encode_annot_assert_axiom(CowlPRTEncoder *e, CowlAnnotAssertAxiom *axiom) {
    CowlVector *annot = cowl_axiom_get_annot(axiom);
    ulib_byte const header = axiom_header(COWL_OT_A_ANNOT_ASSERT, annot, false);
    write_bytes(e, &header, sizeof(header));

    encode_annot_prop(e, cowl_annot_assert_axiom_get_prop(axiom));
    encode_id(e, cowl_annot_assert_axiom_get_subject(axiom));
    encode_annot_value(e, cowl_annot_assert_axiom_get_value(axiom));
    if (annot) encode_vector(e, annot);
}

static void encode_disj_union_axiom(CowlPRTEncoder *e, CowlDisjUnionAxiom *axiom) {
    CowlVector *annot = cowl_axiom_get_annot(axiom);
    ulib_byte const header = axiom_header(COWL_OT_A_DISJ_UNION, annot, false);
    write_bytes(e, &header, sizeof(header));

    encode_class(e, cowl_disj_union_axiom_get_class(axiom), false);
    encode_vector(e, cowl_disj_union_axiom_get_disjoints(axiom));
    if (annot) encode_vector(e, annot);
}

static void encode_object(CowlPRTEncoder *e, CowlAny *obj) {
    CowlObjectType type = cowl_get_type(obj);
    switch (type) {
        case COWL_OT_STRING: encode_string(e, obj); break;
        case COWL_OT_VECTOR: encode_vector(e, obj); break;
        case COWL_OT_IRI: encode_id(e, obj); break;
        case COWL_OT_LITERAL: encode_literal(e, obj); break;
        case COWL_OT_FACET_RESTR: encode_facet_restr(e, obj); break;
        case COWL_OT_ANNOTATION: encode_annotation(e, obj); break;
        case COWL_OT_ANNOT_PROP: encode_annot_prop(e, obj); break;
        case COWL_OT_CE_CLASS: encode_class(e, obj, true); break;
        case COWL_OT_DPE_DATA_PROP: encode_data_prop(e, obj); break;
        case COWL_OT_DR_DATATYPE: encode_datatype(e, obj, true); break;
        case COWL_OT_DR_DATATYPE_RESTR: encode_datatype_restr(e, obj); break;
        case COWL_OT_I_NAMED: encode_named_ind(e, obj); break;
        case COWL_OT_OPE_OBJ_PROP: encode_obj_prop(e, obj, true); break;
        case COWL_OT_OPE_INV_OBJ_PROP: encode_inv_obj_prop(e, obj); break;
        case COWL_OT_I_ANONYMOUS: encode_id(e, obj); break;
        case COWL_OT_A_DECL: encode_decl_axiom(e, obj); break;
        case COWL_OT_A_DATATYPE_DEF: encode_datatype_def_axiom(e, obj); break;
        case COWL_OT_A_DISJ_UNION: encode_disj_union_axiom(e, obj); break;
        case COWL_OT_A_SUB_OBJ_PROP: encode_sub_obj_prop_axiom(e, obj); break;
        case COWL_OT_A_ANNOT_ASSERT: encode_annot_assert_axiom(e, obj); break;
        case COWL_OT_CE_OBJ_SOME:
        case COWL_OT_CE_OBJ_ALL: encode_obj_quant(e, type, obj); break;
        case COWL_OT_CE_DATA_SOME:
        case COWL_OT_CE_DATA_ALL: encode_data_quant(e, type, obj); break;
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD:
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: encode_card_restr(e, obj); break;
        default: {
            if (type >= COWL_OT_FIRST_A && type <= COWL_OT_LAST_A) {
                encode_axiom_default(e, obj);
            } else if (type >= COWL_OT_FIRST_CE && type <= COWL_OT_LAST_CE) {
                encode_cls_exp_default(e, obj);
            } else if (type >= COWL_OT_FIRST_DR && type <= COWL_OT_LAST_DR) {
                encode_data_range_default(e, obj);
            }
        }
    }
}

static cowl_ret encode_protocol_version(CowlPRTEncoder *e) {
    ulib_byte const header = COWL_PRT_FORMAT_VERSION;
    write_bytes(e, &header, sizeof(header));
    return encoder_state(e);
}

static void encode_prefix_decl(CowlPRTEncoder *e, CowlString *prefix, CowlString *ns) {
    encode_string(e, prefix);
    encode_string(e, ns);
}

static void encode_prefixes(CowlPRTEncoder *e, ulib_uint count, UVec(CowlObjectPtr) *ns) {
    ulib_byte const header = COWL_PRT_NS_DECLS_FRAME | COWL_PRT_NS_DECL_IS_PREFIX_BITMASK;
    write_bytes(e, &header, sizeof(header));
    write_varint(e, count);

    uvec_foreach (CowlObjectPtr, ns, i) {
        CowlString *prefix = cowl_prt_index_get_prefix(&e->index, *i.item);
        if (!prefix) {
            e->state = COWL_ERR;
            return;
        }
        encode_prefix_decl(e, prefix, *i.item);
    }
}

static void encode_namespaces(CowlPRTEncoder *e, ulib_uint count, UVec(CowlObjectPtr) *ns) {
    ulib_byte const header = COWL_PRT_NS_DECLS_FRAME;
    write_bytes(e, &header, sizeof(header));
    write_varint(e, count);
    uvec_foreach (CowlObjectPtr, ns, i) {
        encode_string(e, *i.item);
    }
}

static cowl_ret encode_ns_decls(CowlPRTEncoder *e) {
    UVec(CowlObjectPtr) prefix_view;
    UVec(CowlObjectPtr) ns_view;
    cowl_prt_index_unencoded_prefixes(&e->index, &prefix_view, &ns_view);

    ulib_uint count = uvec_count(CowlObjectPtr, &prefix_view);
    if (count) encode_prefixes(e, count, &prefix_view);
    count = uvec_count(CowlObjectPtr, &ns_view);
    if (count) encode_namespaces(e, count, &ns_view);

    return encoder_state(e);
}

static void encode_iri_decls(CowlPRTEncoder *e, ulib_uint count, UVec(CowlObjectPtr) *iris) {
    ulib_byte const header = COWL_PRT_ID_DECLS_FRAME | COWL_PRT_ID_DECL_IS_IRI_BITMASK;
    write_bytes(e, &header, sizeof(header));
    write_varint(e, count);
    uvec_foreach (CowlObjectPtr, iris, i) {
        ulib_uint const idx = cowl_prt_index_get_ns_idx(&e->index, cowl_iri_get_ns(*i.item));
        if (idx == COWL_PRT_NOT_FOUND) {
            e->state = COWL_ERR;
            return;
        }
        write_varint(e, idx);
        encode_string(e, cowl_iri_get_rem(*i.item));
    }
}

static void
encode_anon_id_decls(CowlPRTEncoder *e, ulib_uint count, UVec(CowlObjectPtr) *anon_view) {
    ulib_byte const header = COWL_PRT_ID_DECLS_FRAME;
    write_bytes(e, &header, sizeof(header));
    write_varint(e, count);
    uvec_foreach (CowlObjectPtr, anon_view, i) {
        CowlString *ind = cowl_anon_ind_get_id(*i.item);
        encode_string(e, ind);
    }
}

static cowl_ret encode_id_decls(CowlPRTEncoder *e) {
    UVec(CowlObjectPtr) iri_view;
    UVec(CowlObjectPtr) anon_view;
    cowl_prt_index_unencoded_ids(&e->index, &iri_view, &anon_view);

    ulib_uint count = uvec_count(CowlObjectPtr, &iri_view);
    if (count) encode_iri_decls(e, count, &iri_view);
    count = uvec_count(CowlObjectPtr, &anon_view);
    if (e->encode_anon && count) encode_anon_id_decls(e, count, &anon_view);

    return encoder_state(e);
}

static cowl_ret encode_iri_version(CowlPRTEncoder *e, CowlIRI *iri, CowlIRI *version) {
    if (!iri) return COWL_OK;
    ulib_byte const header = COWL_PRT_IRI_VERSION_FRAME | (!!version << COWL_PRT_VERSION_OFFSET);
    write_bytes(e, &header, sizeof(header));
    encode_id(e, iri);
    if (version) encode_id(e, version);
    return encoder_state(e);
}

static cowl_ret encode_import(void *e, CowlAny *iri) {
    encode_id(e, iri);
    return encoder_state(e);
}

static void annotation_item(CowlPRTEncoder *e, CowlAny *annot) {
    encode_annotation(e, annot);
}

static cowl_ret encode_axiom(void *e, CowlAnyAxiom *axiom) {
    encode_object(e, axiom);
    return encoder_state(e);
}

static cowl_ret encode_onto_iri_version(CowlPRTEncoder *e, CowlOntology *onto) {
    return encode_iri_version(e, cowl_ontology_get_iri(onto), cowl_ontology_get_version(onto));
}

static cowl_ret encode_onto_imports(CowlPRTEncoder *e, CowlOntology *onto) {
    ulib_uint count = cowl_ontology_import_count(onto);
    if (!count) return COWL_OK;
    ulib_byte const header = COWL_PRT_IMPORTS_FRAME;
    write_bytes(e, &header, sizeof(header));
    write_varint(e, count);
    CowlIterator iter = { e, encode_import };
    cowl_ontology_iterate_imports(onto, &iter);
    return encoder_state(e);
}

static cowl_ret encode_onto_annotations(CowlPRTEncoder *e, CowlOntology *onto) {
    UVec(CowlObjectPtr) const *annot = cowl_vector_get_data(cowl_ontology_get_annot(onto));
    if (!uvec_count(CowlObjectPtr, annot)) return COWL_OK;
    ulib_byte const header = COWL_PRT_ANNOTATIONS_FRAME;
    write_bytes(e, &header, sizeof(header));
    encode_uvec(e, annot, annotation_item);
    return encoder_state(e);
}

static cowl_ret encode_onto_axioms(CowlPRTEncoder *e, CowlOntology *onto) {
    CowlIterator iter = { e, encode_axiom };
    cowl_ontology_iterate_axioms(onto, &iter);
    return encoder_state(e);
}

static cowl_ret encode_data(CowlPRTEncoder *e, CowlOntology *onto) {
    cowl_ret ret;
    if ((ret = encode_ns_decls(e))) return ret;
    if ((ret = encode_id_decls(e))) return ret;
    if ((ret = encode_onto_iri_version(e, onto))) return ret;
    if ((ret = encode_onto_imports(e, onto))) return ret;
    if ((ret = encode_onto_annotations(e, onto))) return ret;
    return encode_onto_axioms(e, onto);
}

static cowl_ret write_ontology(void *ctx, UOStream *stream, CowlOntology *onto) {
    CowlPRTEncoder *e = ctx;
    if (!e) return COWL_ERR_MEM;
    e->stream = stream;

    if (encoder_reset(e, true) || populate_index(e, onto)) goto end;
    if (encode_protocol_version(e)) goto end;
    if (encode_data(e, onto)) goto end;

end:
    encoder_reset(e, true);
    return encoder_state(e);
}

static void stream_encoder_flush(CowlPRTEncoder *e) {
    encode_data(e, e->to_flush);
    flush_state_empty(e);
}

static inline void stream_encoder_write_ctrl_frame(CowlPRTEncoder *e, ulib_byte ctrl) {
    write_bytes(e, &ctrl, sizeof(ctrl));
}

static void stream_encoder_write_reset_frame(CowlPRTEncoder *e, bool prefixes, bool ids) {
    ulib_byte header = COWL_PRT_RESET_FRAME;
    header |= (!!prefixes << COWL_PRT_RESET_NS_OFFSET);
    header |= (!!ids << COWL_PRT_RESET_ID_OFFSET);
    stream_encoder_write_ctrl_frame(e, header);
}

static inline bool encoder_should_flush(CowlPRTEncoder *e, bool *reset, bool *prefixes) {
    ulib_uint const prefix_count = cowl_prt_index_prefix_count(&e->index) -
                                   COWL_PRT_STANDARD_PREFIX_COUNT;
    ulib_uint const id_count = cowl_prt_index_id_count(&e->index);

    if (prefix_count + id_count > e->index_size) {
        *reset = true;
        *prefixes = prefix_count > (e->index_size >> 2);
        return true;
    }

    *reset = false;
    *prefixes = false;
    return e->cur_size > e->index_size;
}

static cowl_ret stream_encoder_flush_if_needed(CowlPRTEncoder *e) {
    bool reset;
    bool reset_prefixes;
    if (encoder_should_flush(e, &reset, &reset_prefixes)) {
        stream_encoder_flush(e);
        if (reset) {
            stream_encoder_write_reset_frame(e, reset_prefixes, true);
            encoder_reset(e, reset_prefixes);
        }
    }
    return encoder_state(e);
}

static cowl_ret axiom_adder(CowlPRTEncoder *e, CowlAny *axiom) {
    return cowl_ontology_add_axiom(e->to_flush, axiom);
}

static cowl_ret import_adder(CowlPRTEncoder *e, CowlAny *iri) {
    return cowl_ontology_add_import(e->to_flush, iri);
}

static cowl_ret annot_adder(CowlPRTEncoder *e, CowlAny *annot) {
    return cowl_ontology_add_annot(e->to_flush, annot);
}

static cowl_ret stream_encoder_add(CowlPRTEncoder *e, CowlAny *obj,
                                   cowl_ret (*adder)(CowlPRTEncoder *, CowlAny *)) {
    CowlIterator iter = { e, for_each_primitive };
    if (cowl_iterate_primitives(obj, COWL_PF_ALL, &iter)) return e->state;
    if ((e->state = adder(e, obj))) return e->state;
    e->cur_size++;
    return stream_encoder_flush_if_needed(e);
}

static cowl_ret stream_encode_prefixes(CowlPRTEncoder *e, CowlPrefixMap *pm) {
    CowlTable *prefixes = cowl_prefix_map_get_table(pm, false);
    cowl_table_foreach (prefixes, p) {
        if (encoder_add_prefix(e, *p.val, *p.key) || stream_encoder_flush_if_needed(e)) break;
    }
    return encoder_state(e);
}

static cowl_ret stream_encode_iri_version(CowlPRTEncoder *e, CowlIRI *iri, CowlIRI *version) {
    cowl_ontology_set_iri(e->to_flush, iri);
    if (encoder_add_primitive(e, iri)) goto end;
    if (!version) goto end;
    cowl_ontology_set_version(e->to_flush, version);
    if (encoder_add_primitive(e, version)) goto end;
end:
    return stream_encoder_flush_if_needed(e);
}

static cowl_ret stream_encode_imports(CowlPRTEncoder *e, UVec(CowlObjectPtr) const *imports) {
    cowl_ret ret = COWL_OK;
    uvec_foreach (CowlObjectPtr, imports, import) {
        if ((ret = stream_encoder_add(e, *import.item, import_adder))) break;
    }
    return ret;
}

static cowl_ret
stream_encode_annotations(CowlPRTEncoder *e, UVec(CowlObjectPtr) const *annotations) {
    cowl_ret ret = COWL_OK;
    uvec_foreach (CowlObjectPtr, annotations, annot) {
        if ((ret = stream_encoder_add(e, *annot.item, annot_adder))) break;
    }
    return ret;
}

static cowl_ret write_header(void *ctx, UOStream *stream, CowlOntologyHeader header) {
    CowlPRTEncoder *e = ctx;
    if (!e) return COWL_ERR_MEM;
    e->stream = stream;

    if (encoder_reset(e, true)) goto end;
    if (encode_protocol_version(e)) goto end;
    if (stream_encode_prefixes(e, header.pm)) goto end;
    if (stream_encode_iri_version(e, header.iri, header.version)) goto end;
    if (stream_encode_imports(e, header.imports)) goto end;
    if (stream_encode_annotations(e, header.annotations)) goto end;

end:
    return encoder_state(e);
}

static cowl_ret stream_encode_axiom(CowlPRTEncoder *e, CowlAnyAxiom *axiom) {
    return stream_encoder_add(e, axiom, axiom_adder);
}

static cowl_ret write_axiom(void *ctx, UOStream *stream, CowlAnyAxiom *axiom) {
    CowlPRTEncoder *e = ctx;
    if (!e) return COWL_ERR_MEM;
    e->stream = stream;
    return stream_encode_axiom(e, axiom);
}

static cowl_ret write_footer(void *ctx, UOStream *stream) {
    CowlPRTEncoder *e = ctx;
    if (!e) return COWL_ERR_MEM;
    e->stream = stream;
    stream_encoder_flush(e);
    stream_encoder_write_ctrl_frame(e, COWL_PRT_END_FRAME);
    encoder_reset(e, true);
    return encoder_state(e);
}

static void free_ctx(void *ctx) {
    encoder_deinit(ctx);
    ulib_free(ctx);
}

CowlWriter *cowl_writer_protocowl(void) {
    CowlPRTEncoder *e = ulib_alloc(e);
    if (e) encoder_init(e);
    return cowl_writer((CowlWriterImpl){
        .name = "ProtocOWL",
        .ctx = e,
        .free = free_ctx,
        .write_header = write_header,
        .write_axiom = write_axiom,
        .write_footer = write_footer,
        .write_ontology = write_ontology,
    });
}

void cowl_writer_protocowl_set_index_size(CowlWriter *writer, ulib_uint index_size) {
    CowlWriterImpl *impl = cowl_writer_get_impl(writer);
    CowlPRTEncoder *e = impl->ctx;
    if (!e) return;
    if (!index_size) index_size = COWL_PROTOCOWL_INDEX_SIZE_UNBOUNDED;
    e->index_size = index_size;
    if (index_size == COWL_PROTOCOWL_INDEX_SIZE_UNBOUNDED) {
        impl->write_ontology = write_ontology;
    } else {
        impl->write_ontology = NULL;
    }
}

void cowl_writer_protocowl_set_encode_anon(CowlWriter *writer, bool encode_anon) {
    CowlWriterImpl *impl = cowl_writer_get_impl(writer);
    CowlPRTEncoder *e = impl->ctx;
    if (e) e->encode_anon = encode_anon;
}

cowl_ret cowl_writer_protocowl_write_add_frame(CowlWriter *writer, UOStream *stream) {
    CowlPRTEncoder *e = cowl_writer_get_impl(writer)->ctx;
    if (!e) return COWL_ERR_MEM;
    e->stream = stream;
    stream_encoder_flush(e);
    stream_encoder_write_ctrl_frame(e, COWL_PRT_ADD_FRAME);
    return encoder_state(e);
}

cowl_ret cowl_writer_protocowl_write_remove_frame(CowlWriter *writer, UOStream *stream) {
    CowlPRTEncoder *e = cowl_writer_get_impl(writer)->ctx;
    if (!e) return COWL_ERR_MEM;
    e->stream = stream;
    stream_encoder_flush(e);
    stream_encoder_write_ctrl_frame(e, COWL_PRT_REMOVE_FRAME);
    return encoder_state(e);
}

cowl_ret
cowl_writer_protocowl_write_reset_frame(CowlWriter *writer, UOStream *stream, bool reset_prefixes) {
    CowlPRTEncoder *e = cowl_writer_get_impl(writer)->ctx;
    if (!e) return COWL_ERR_MEM;
    e->stream = stream;
    stream_encoder_flush(e);
    stream_encoder_write_reset_frame(e, reset_prefixes, true);
    encoder_reset(e, reset_prefixes);
    return encoder_state(e);
}
