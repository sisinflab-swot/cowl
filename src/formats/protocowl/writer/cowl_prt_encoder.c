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
#include "cowl_impl.h"
#include "ulib.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct CowlPRTEncoder {
    CowlPRTIndex index;
    UVec(CowlObjectPtr) imports;
    UVec(CowlObjectPtr) annots;
    UVec(CowlObjectPtr) axioms;
    UOStream *stream;
    CowlIRI *iri;
    CowlIRI *version;
    ulib_uint index_size;
    cowl_ret state;
    bool encode_anon;
} CowlPRTEncoder;

static void encoder_init_ex(CowlPRTEncoder *e, CowlPRTIndex *index) {
    *e = (CowlPRTEncoder){ 0 };
    if (index) e->index = *index;
    e->encode_anon = true;
    e->index_size = COWL_PROTOCOWL_INDEX_SIZE_UNBOUNDED;
    e->imports = uvec(CowlObjectPtr);
    e->annots = uvec(CowlObjectPtr);
    e->axioms = uvec(CowlObjectPtr);
}

static cowl_ret encoder_init(CowlPRTEncoder *e) {
    encoder_init_ex(e, NULL);
    return e->state = cowl_prt_index_init(&e->index, true);
}

static void encoder_deinit(CowlPRTEncoder *e) {
    cowl_prt_index_deinit(&e->index);
    cowl_release(e->iri);
    cowl_release(e->version);
    uvec_foreach (CowlObjectPtr, &e->imports, import) {
        cowl_release(*import.item);
    }
    uvec_foreach (CowlObjectPtr, &e->annots, annot) {
        cowl_release(*annot.item);
    }
    uvec_foreach (CowlObjectPtr, &e->axioms, axiom) {
        cowl_release(*axiom.item);
    }
    uvec_deinit(CowlObjectPtr, &e->imports);
    uvec_deinit(CowlObjectPtr, &e->annots);
    uvec_deinit(CowlObjectPtr, &e->axioms);
    *e = (CowlPRTEncoder){ 0 };
}

static cowl_ret encoder_reset(CowlPRTEncoder *e, bool prefixes) {
    cowl_ret ret = COWL_OK;

    // Save state.
    bool const encode_anon = e->encode_anon;
    ulib_uint const index_size = e->index_size;
    UOStream *const stream = e->stream;

    CowlPRTIndex index;

    if (!prefixes) {
        index = e->index;
        e->index = (CowlPRTIndex){ 0 };
        if ((ret = cowl_prt_index_reset_ids(&index))) return ret;
    }

    // Reset and restore state.
    encoder_deinit(e);

    if (prefixes) {
        if ((ret = encoder_init(e))) return ret;
    } else {
        encoder_init_ex(e, &index);
    }

    e->stream = stream;
    e->encode_anon = encode_anon;
    e->index_size = index_size;

    return ret;
}

static inline bool encoder_error(CowlPRTEncoder *e) {
    return e->state || e->stream->state;
}

static inline bool encoder_ok(CowlPRTEncoder *e) {
    return !encoder_error(e);
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

static bool for_each_primitive(void *ctx, CowlAnyPrimitive *primitive) {
    return encoder_add_primitive(ctx, primitive) == COWL_OK;
}

static cowl_ret populate_index(CowlPRTEncoder *e, CowlOntology *onto) {
    ulib_uint const primitive_count = cowl_ontology_primitives_count(onto, COWL_PF_ALL, false);
    if (cowl_prt_index_reserve_ids(&e->index, primitive_count)) goto err;

    CowlSymTable *st = cowl_ontology_get_sym_table(onto);
    CowlTable *prefix_ns_map = cowl_sym_table_get_prefix_ns_map(st, false);

    cowl_table_foreach (prefix_ns_map, entry) {
        if (encoder_add_prefix(e, *entry.val, *entry.key)) goto err;
    }

    CowlIRI *iri = cowl_ontology_get_iri(onto);
    if (iri && encoder_add_primitive(e, iri)) goto err;

    iri = cowl_ontology_get_version(onto);
    if (iri && encoder_add_primitive(e, iri)) goto err;

    CowlIterator iter = { e, for_each_primitive };
    if (!cowl_ontology_iterate_primitives(onto, COWL_PF_ALL, &iter, false)) goto err;
    if (!cowl_ontology_iterate_import_iris(onto, &iter, false)) goto err;

    return COWL_OK;

err:
    cowl_prt_index_deinit(&e->index);
    return COWL_ERR_MEM;
}

static void write_bytes(CowlPRTEncoder *e, void const *data, ulib_uint length) {
    uostream_write(e->stream, data, length, NULL);
}

static void write_varint(CowlPRTEncoder *e, ulib_uint value) {
    uostream_write_varint(e->stream, value, NULL);
}

static void encode_object(CowlPRTEncoder *e, CowlAny *obj);

static void encode_cstring(CowlPRTEncoder *e, char const *string, ulib_uint length) {
    write_varint(e, length);
    if (length) write_bytes(e, string, length);
}

static void encode_ustring(CowlPRTEncoder *e, UString const *string) {
    encode_cstring(e, ustring_data(*string), ustring_length(*string));
}

static void encode_string(CowlPRTEncoder *e, CowlString *string) {
    encode_ustring(e, cowl_string_get_raw(string));
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

static CowlPRTLiteralType literal_type(CowlDatatype *dt, CowlString *lang) {
    if (lang) return COWL_OLT_STRING_LITERAL_LANGUAGE;
    if (dt == cowl_xsd_vocab()->dt.string) return COWL_OLT_STRING_LITERAL;
    return COWL_OLT_TYPED_LITERAL;
}

static void encode_literal(CowlPRTEncoder *e, CowlLiteral *literal) {
    CowlDatatype *dt = cowl_literal_get_datatype(literal);
    CowlString *value = cowl_literal_get_value(literal);
    CowlString *lang = cowl_literal_get_lang(literal);

    CowlPRTLiteralType const type = literal_type(dt, lang);
    ulib_byte const header = (ulib_byte)type;
    write_bytes(e, &header, sizeof(header));

    encode_string(e, value);
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
    if (cowl_annot_value_get_type(value) != COWL_AVT_LITERAL) {
        encode_id_offset(e, value, 1);
        return;
    }
    // Literal.
    write_varint(e, 0);
    encode_literal(e, value);
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

    CowlAny *opt = cowl_get_opt_field(restr);
    ulib_uint card = (cowl_get_uint_field(restr) << 1) | !!opt;
    write_varint(e, card);

    unsigned count;
    CowlAny **fields = cowl_get_fields(restr, &count);

    for (unsigned i = 0; i < count; ++i) {
        encode_object(e, fields[i]);
    }

    if (opt) encode_object(e, opt);
}

static void encode_decl_axiom(CowlPRTEncoder *e, CowlDeclAxiom *axiom) {
    CowlAnyEntity *entity = cowl_decl_axiom_get_entity(axiom);
    CowlVector *annot = cowl_axiom_get_annot(axiom);

    ulib_byte header = (ulib_byte)(COWL_AT_DECL + cowl_entity_get_type(entity));
    if (annot) header |= COWL_PRT_AXIOM_ANNOT_BITMASK;

    write_bytes(e, &header, sizeof(header));
    encode_id(e, cowl_entity_get_iri(entity));
    if (annot) encode_vector(e, annot);
}

ulib_byte axiom_header(CowlObjectType type, bool annot, bool utility) {
    ulib_byte header = (type - COWL_OT_FIRST_A) + COWL_ET_COUNT - 1;
    header |= utility << COWL_PRT_AXIOM_UTLITY_OFFSET;
    header |= annot << COWL_PRT_AXIOM_ANNOT_OFFSET;
    return header;
}

ulib_byte cls_exp_header(CowlObjectType type) {
    return (type - COWL_OT_FIRST_CE) - 1;
}

ulib_byte data_range_header(CowlObjectType type) {
    return (type - COWL_OT_FIRST_DR) - 1;
}

static void encode_construct_body(CowlPRTEncoder *e, CowlAny *obj) {
    unsigned count;
    CowlAny **fields = cowl_get_fields(obj, &count);

    for (unsigned i = 0; i < count; i++) {
        encode_object(e, fields[i]);
    }

    CowlAny *opt = cowl_get_opt_field(obj);
    if (opt) encode_object(e, opt);
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

static void
encode_prefix_declarations(CowlPRTEncoder *e, ulib_uint count, UVec(CowlObjectPtr) *ns) {
    ulib_byte const header = COWL_PRT_PREFIX_DECLS_FRAME | COWL_PRT_PREFIX_DECL_IS_PREFIX_BITMASK;
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

static void encode_ns_declarations(CowlPRTEncoder *e, ulib_uint count, UVec(CowlObjectPtr) *ns) {
    ulib_byte const header = COWL_PRT_PREFIX_DECLS_FRAME;
    write_bytes(e, &header, sizeof(header));
    write_varint(e, count);
    uvec_foreach (CowlObjectPtr, ns, i) {
        encode_string(e, *i.item);
    }
}

static cowl_ret encode_prefix_decls(CowlPRTEncoder *e) {
    UVec(CowlObjectPtr) prefix_view;
    UVec(CowlObjectPtr) ns_view;
    cowl_prt_index_unencoded_prefixes(&e->index, &prefix_view, &ns_view);

    ulib_uint count = uvec_count(CowlObjectPtr, &prefix_view);
    if (count) encode_prefix_declarations(e, count, &prefix_view);
    count = uvec_count(CowlObjectPtr, &ns_view);
    if (count) encode_ns_declarations(e, count, &ns_view);

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

static cowl_ret encode_onto_iri_version(CowlPRTEncoder *e, CowlOntology *onto) {
    return encode_iri_version(e, cowl_ontology_get_iri(onto), cowl_ontology_get_version(onto));
}

static void annotation_item(CowlPRTEncoder *e, CowlAny *annot) {
    encode_annotation(e, annot);
}

static cowl_ret encode_annotations(CowlPRTEncoder *e, UVec(CowlObjectPtr) const *annot) {
    if (!uvec_count(CowlObjectPtr, annot)) return COWL_OK;
    ulib_byte const header = COWL_PRT_ANNOTATIONS_FRAME;
    write_bytes(e, &header, sizeof(header));
    encode_uvec(e, annot, annotation_item);
    return encoder_state(e);
}

static cowl_ret encode_onto_annotations(CowlPRTEncoder *e, CowlOntology *onto) {
    return encode_annotations(e, cowl_vector_get_data(cowl_ontology_get_annot(onto)));
}

static cowl_ret encode_imports(CowlPRTEncoder *e, UVec(CowlObjectPtr) const *imports) {
    if (!uvec_count(CowlObjectPtr, imports)) return COWL_OK;
    ulib_byte const header = COWL_PRT_IMPORTS_FRAME;
    write_bytes(e, &header, sizeof(header));
    encode_uvec(e, imports, encode_id);
    return encoder_state(e);
}

static bool encode_import(void *ctx, CowlAny *iri) {
    CowlPRTEncoder *e = ctx;
    encode_id(e, iri);
    return encoder_ok(e);
}

static cowl_ret encode_onto_imports(CowlPRTEncoder *e, CowlOntology *onto) {
    ulib_uint count = cowl_ontology_imports_count(onto, false);
    if (!count) return COWL_OK;
    ulib_byte const header = COWL_PRT_IMPORTS_FRAME;
    write_bytes(e, &header, sizeof(header));
    write_varint(e, count);
    CowlIterator iter = { e, encode_import };
    cowl_ontology_iterate_import_iris(onto, &iter, false);
    return encoder_state(e);
}

static cowl_ret encode_axioms(CowlPRTEncoder *e, UVec(CowlObjectPtr) const *axioms) {
    cowl_ret ret = COWL_OK;
    uvec_foreach (CowlObjectPtr, axioms, axiom) {
        encode_object(e, *axiom.item);
        if ((ret = encoder_state(e))) break;
    }
    return ret;
}

static bool encode_axiom(void *ctx, CowlAnyAxiom *axiom) {
    CowlPRTEncoder *e = ctx;
    encode_object(e, axiom);
    return encoder_ok(e);
}

static cowl_ret encode_onto_axioms(CowlPRTEncoder *e, CowlOntology *onto) {
    CowlIterator iter = { e, encode_axiom };
    cowl_ontology_iterate_axioms(onto, &iter, false);
    return encoder_state(e);
}

static cowl_ret write_ontology(void *ctx, UOStream *stream, CowlOntology *onto) {
    CowlPRTEncoder *e = ctx;
    if (!e) return COWL_ERR_MEM;

    cowl_ret ret;
    if (encoder_reset(e, true) || populate_index(e, onto)) goto end;
    e->stream = stream;

    if (encode_protocol_version(e)) goto end;
    if (encode_prefix_decls(e)) goto end;
    if (encode_id_decls(e)) goto end;
    if (encode_onto_iri_version(e, onto)) goto end;
    if (encode_onto_imports(e, onto)) goto end;
    if (encode_onto_annotations(e, onto)) goto end;
    if (encode_onto_axioms(e, onto)) goto end;

end:
    ret = encoder_state(e);
    encoder_deinit(e);
    return ret;
}

static cowl_ret stream_encoder_flush(CowlPRTEncoder *e) {
    if (encode_prefix_decls(e)) goto end;
    if (encode_id_decls(e)) goto end;
    if (encode_iri_version(e, e->iri, e->version)) goto end;
    if (encode_imports(e, &e->imports)) goto end;
    if (encode_annotations(e, &e->annots)) goto end;
    if (encode_axioms(e, &e->axioms)) goto end;
end:
    return encoder_state(e);
}

static void stream_encode_reset_frame(CowlPRTEncoder *e, bool prefixes, bool ids) {
    ulib_byte header = COWL_PRT_RESET_FRAME;
    header |= (!!prefixes << COWL_PRT_RESET_PREFIXES_OFFSET);
    header |= (!!ids << COWL_PRT_RESET_IDS_OFFSET);
    write_bytes(e, &header, sizeof(header));
}

static cowl_ret stream_encoder_flush_if_full(CowlPRTEncoder *e) {
    ulib_uint const prefix_count = cowl_prt_index_prefix_count(&e->index) -
                                   COWL_PRT_STANDARD_PREFIX_COUNT;
    ulib_uint const id_count = cowl_prt_index_id_count(&e->index);
    if (prefix_count + id_count <= e->index_size) return COWL_OK;
    bool const reset_prefixes = prefix_count > (e->index_size >> 2);
    if (stream_encoder_flush(e)) goto end;
    if (encoder_reset(e, reset_prefixes)) goto end;
    stream_encode_reset_frame(e, reset_prefixes, true);
end:
    return encoder_state(e);
}

static cowl_ret
stream_encoder_add_to_vec(CowlPRTEncoder *e, CowlAny *obj, UVec(CowlObjectPtr) *vec) {
    CowlIterator iter = { e, for_each_primitive };
    if (!cowl_iterate_primitives(obj, COWL_PF_ALL, &iter)) return e->state;
    if (uvec_push(CowlObjectPtr, vec, obj)) return (e->state = COWL_ERR_MEM);
    cowl_retain(obj);
    return stream_encoder_flush_if_full(e);
}

static cowl_ret stream_encode_prefixes(CowlPRTEncoder *e, CowlSymTable *st) {
    CowlTable *prefixes = cowl_sym_table_get_prefix_ns_map(st, false);
    cowl_table_foreach (prefixes, p) {
        if (encoder_add_prefix(e, *p.val, *p.key) || stream_encoder_flush_if_full(e)) break;
    }
    return encoder_state(e);
}

static cowl_ret stream_encode_iri_version(CowlPRTEncoder *e, CowlIRI *iri, CowlIRI *version) {
    e->iri = cowl_retain(iri);
    if (encoder_add_primitive(e, iri)) goto end;
    if (!version) goto end;
    e->version = cowl_retain(version);
    if (encoder_add_primitive(e, version)) goto end;
end:
    return stream_encoder_flush_if_full(e);
}

static cowl_ret stream_encode_imports(CowlPRTEncoder *e, UVec(CowlObjectPtr) const *imports) {
    cowl_ret ret = COWL_OK;
    uvec_foreach (CowlObjectPtr, imports, import) {
        if ((ret = stream_encoder_add_to_vec(e, *import.item, &e->imports))) break;
    }
    return ret;
}

static cowl_ret
stream_encode_annotations(CowlPRTEncoder *e, UVec(CowlObjectPtr) const *annotations) {
    cowl_ret ret = COWL_OK;
    uvec_foreach (CowlObjectPtr, annotations, annot) {
        if ((ret = stream_encoder_add_to_vec(e, *annot.item, &e->annots))) break;
    }
    return ret;
}

static cowl_ret write_header(CowlStreamState state, UOStream *stream, CowlOntologyHeader header) {
    CowlPRTEncoder *e = state.ctx;
    if (!e) return COWL_ERR_MEM;

    if (encoder_reset(e, true)) goto end;
    e->stream = stream;

    if (encode_protocol_version(e)) goto end;
    if (stream_encode_prefixes(e, state.st)) goto end;
    if (stream_encode_iri_version(e, header.iri, header.version)) goto end;
    if (stream_encode_imports(e, header.imports)) goto end;
    if (stream_encode_annotations(e, header.annotations)) goto end;

end:
    return encoder_state(e);
}

static cowl_ret write_axiom(CowlStreamState state, UOStream *stream, CowlAnyAxiom *axiom) {
    CowlPRTEncoder *e = state.ctx;
    if (!e) return COWL_ERR_MEM;
    e->stream = stream;
    return stream_encoder_add_to_vec(e, axiom, &e->axioms);
}

static cowl_ret write_footer(CowlStreamState state, UOStream *stream) {
    CowlPRTEncoder *e = state.ctx;
    if (!e) return COWL_ERR_MEM;
    e->stream = stream;
    cowl_ret ret = stream_encoder_flush(e);
    encoder_deinit(e);
    return ret;
}

static void free_ctx(void *ctx) {
    encoder_deinit(ctx);
    ulib_free(ctx);
}

CowlWriter cowl_writer_protocowl(void) {
    CowlPRTEncoder *e = ulib_alloc(e);
    if (e) encoder_init(e);
    return (CowlWriter){
        .name = "ProtocOWL",
        .ctx = e,
        .free = free_ctx,
        .write_ontology = write_ontology,
        .stream = {
            .write_axiom = write_axiom,
            .write_header = write_header,
            .write_footer = write_footer,
        },
    };
}

void cowl_writer_protocowl_set_index_size(CowlWriter *writer, ulib_uint index_size) {
    CowlPRTEncoder *e = writer->ctx;
    if (!e) return;
    if (!index_size) index_size = COWL_PROTOCOWL_INDEX_SIZE_UNBOUNDED;
    e->index_size = index_size;
    if (index_size == COWL_PROTOCOWL_INDEX_SIZE_UNBOUNDED) {
        writer->write_ontology = write_ontology;
    } else {
        writer->write_ontology = NULL;
    }
}

void cowl_writer_protocowl_set_encode_anon(CowlWriter *writer, bool encode_anon) {
    CowlPRTEncoder *e = writer->ctx;
    if (e) e->encode_anon = encode_anon;
}
