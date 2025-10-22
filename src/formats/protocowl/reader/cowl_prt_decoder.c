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
#include "cowl_string.h"
#include "cowl_string_private.h"
#include "cowl_vector_private.h"
#include "ulib.h"
#include "unumber.h"
#include "ustring.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct CowlPRTDecoder {
    CowlPRTIndex index;
    UIStream *stream;
    CowlChangeHandler *handler;
    CowlError *error;
    bool remove;
} CowlPRTDecoder;

static inline cowl_ret
decoder_init(CowlPRTDecoder *d, UIStream *stream, CowlChangeHandler *handler, CowlError *error) {
    d->stream = stream;
    d->handler = handler;
    d->error = error;
    d->remove = false;
    error->code = cowl_prt_index_init(&d->index, false);
    return error->code;
}

static inline void decoder_deinit(CowlPRTDecoder *d) {
    cowl_prt_index_deinit(&d->index);
}

#define decoder_ok(d)                                                                              \
    (ulib_likely(ulib_ret_is_ok((d)->stream->state) && cowl_ret_is_ok((d)->error->code)))

#define decoder_err(d)                                                                             \
    (ulib_unlikely(ulib_ret_is_err((d)->stream->state) || cowl_ret_is_err((d)->error->code)))

static inline cowl_ret decoder_state(CowlPRTDecoder *d) {
    return ulib_is_err(d->stream->state) ? cowl_ret_from_ulib(d->stream->state) : d->error->code;
}

static inline void decoder_set_error(CowlPRTDecoder *d, CowlError error) {
    cowl_error_deinit(d->error);
    *d->error = error;
}

#define decoder_handle_error(d, exp, ...)                                                          \
    do {                                                                                           \
        cowl_ret _decoder_handle_error_ret = (exp);                                                \
        if (cowl_is_err(d->error->code)) break;                                                    \
        CowlError error = cowl_error(_decoder_handle_error_ret, __VA_ARGS__);                      \
        decoder_set_error(d, error);                                                               \
    } while (0)

#define decoder_handle_error_code(d, exp) decoder_handle_error(d, exp, NULL)

static inline void decoder_handle_change(CowlPRTDecoder *d, cowl_part part, void *value) {
    CowlChange change = {
        .type = d->remove ? COWL_CHANGE_REMOVE : COWL_CHANGE_ADD,
        .part = part,
        .value = value,
    };
    decoder_handle_error_code(d, cowl_change_handler_handle(d->handler, change));
}

static inline cowl_ret read_bytes(CowlPRTDecoder *d, void *data, ulib_uint size) {
    if (!decoder_ok(d)) return decoder_state(d);
    size_t read;
    ulib_ret ret = uistream_read_all(d->stream, data, size, &read);
    if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);
    if (read != size) {
        decoder_handle_error(d, COWL_ERR_SYNTAX, "expected %zu bytes, got %zu", size, read);
        return COWL_ERR_SYNTAX;
    }
    return COWL_OK;
}

static inline bool read_varint(CowlPRTDecoder *d, ulib_uint *value) {
    if (!decoder_ok(d)) goto err;

    ulib_varint v;
    ulib_ret const ret = uistream_read_varint(d->stream, &v, NULL);

    if (ulib_is_ok(ret)) {
        *value = (ulib_uint)v;
        return false;
    }

    if (ret != ULIB_ERR_IO) decoder_handle_error(d, COWL_ERR_SYNTAX, "failed to read varint");

err:
    *value = 0;
    return true;
}

static inline cowl_ret read_svarint(CowlPRTDecoder *d, ulib_int *value) {
    *value = 0;
    if (!decoder_ok(d)) return decoder_state(d);

    ulib_svarint v;
    ulib_ret const ret = uistream_read_svarint(d->stream, &v, NULL);

    if (ulib_is_ok(ret)) {
        *value = (ulib_int)v;
        return COWL_OK;
    }

    if (ret == ULIB_ERR_IO) return COWL_ERR_IO;
    decoder_handle_error(d, COWL_ERR_SYNTAX, "failed to read svarint");
    return COWL_ERR_SYNTAX;
}

static CowlAnyClsExp *decode_cls_exp(CowlPRTDecoder *d);
static CowlAnyDataRange *decode_data_range(CowlPRTDecoder *d);
static CowlIndividual *decode_individual(CowlPRTDecoder *d);
static CowlObjPropExp *decode_obj_prop_exp(CowlPRTDecoder *d);
static CowlDataPropExp *decode_data_prop_exp(CowlPRTDecoder *d);
static CowlFacetRestr *decode_facet_restr(CowlPRTDecoder *d);
static CowlLiteral *decode_literal(CowlPRTDecoder *d);
static CowlAnnotation *decode_annotation(CowlPRTDecoder *d);

static inline void *handle_null(CowlPRTDecoder *d, void *obj) {
    if (!obj) decoder_handle_error_code(d, COWL_ERR_MEM);
    return obj;
}

static CowlAny *cls_exp_item(CowlPRTDecoder *d) {
    return decode_cls_exp(d);
}

static CowlAny *data_range_item(CowlPRTDecoder *d) {
    return decode_data_range(d);
}

static CowlAny *individual_item(CowlPRTDecoder *d) {
    return decode_individual(d);
}

static CowlAny *obj_prop_exp_item(CowlPRTDecoder *d) {
    return decode_obj_prop_exp(d);
}

static CowlAny *data_prop_exp_item(CowlPRTDecoder *d) {
    return decode_data_prop_exp(d);
}

static CowlAny *facet_restr_item(CowlPRTDecoder *d) {
    return decode_facet_restr(d);
}

static CowlAny *literal_item(CowlPRTDecoder *d) {
    return decode_literal(d);
}

static CowlAny *annotation_item(CowlPRTDecoder *d) {
    return decode_annotation(d);
}

static CowlVector *decode_vector(CowlPRTDecoder *d, CowlAny *(*decode_item)(CowlPRTDecoder *)) {
    ulib_uint length;
    if (read_varint(d, &length)) return NULL;

    CowlVector *vec = cowl_vector_empty();
    if (!vec) goto err;
    if (cowl_vector_reserve(vec, length)) goto err;

    for (ulib_uint i = 0; i < length; ++i) {
        CowlAny *item = decode_item(d);
        if (!item || cowl_vector_push(vec, item)) goto err;
    }
    if (cowl_vector_shrink(vec)) goto err;

    return vec;

err:
    decoder_handle_error_code(d, COWL_ERR_MEM);
    cowl_release(vec);
    return NULL;
}

static UString decode_ustring(CowlPRTDecoder *d) {
    ulib_uint length;
    if (read_varint(d, &length)) return ustring_null;

    UString string;
    char *data = ustring(&string, length);
    if (!handle_null(d, data)) return ustring_null;

    if (read_bytes(d, data, length)) {
        ustring_deinit(&string);
        return ustring_null;
    }

    return string;
}

static CowlString *decode_string(CowlPRTDecoder *d) {
    UString ustring = decode_ustring(d);
    if (ustring_is_null(ustring)) return NULL;
    return handle_null(d, cowl_string(ustring));
}

static CowlString *decode_string_intern(CowlPRTDecoder *d) {
    UString ustring = decode_ustring(d);
    if (ustring_is_null(ustring)) return NULL;
    return handle_null(d, cowl_string_opt(ustring, COWL_SO_INTERN));
}

static CowlIRIOrAnonInd *get_id(CowlPRTDecoder *d, ulib_uint offset) {
    cowl_ret ret;
    CowlIRIOrAnonInd *id = cowl_prt_index_get_id(&d->index, offset, &ret);
    if (cowl_is_err(ret)) {
        if (ret == COWL_ERR_BOUNDS) {
            decoder_handle_error(d, COWL_ERR_SYNTAX, "unknown id %" ULIB_UINT_FMT, offset);
        } else {
            decoder_handle_error_code(d, ret);
        }
    }
    return id;
}

static CowlIRI *get_id_iri(CowlPRTDecoder *d, ulib_uint offset) {
    CowlIRIOrAnonInd *id = get_id(d, offset);
    if (id && cowl_get_type(id) != COWL_OT_IRI) {
        decoder_handle_error(d, COWL_ERR_SYNTAX, "expected IRI for id %" ULIB_UINT_FMT, offset);
        return NULL;
    }
    return id;
}

static CowlIRIOrAnonInd *get_iri_or_anon(CowlPRTDecoder *d, ulib_uint offset) {
    CowlIRIOrAnonInd *id = get_id(d, offset);
    return id ? cowl_retain(id) : NULL;
}

static inline CowlIRI *get_iri(CowlPRTDecoder *d, ulib_uint offset) {
    CowlIRI *iri = get_id_iri(d, offset);
    return iri ? cowl_retain(iri) : NULL;
}

static CowlClass *get_class(CowlPRTDecoder *d, ulib_uint offset) {
    CowlIRIOrAnonInd *id = get_id_iri(d, offset);
    if (!id) return NULL;
    return handle_null(d, cowl_class(id));
}

static CowlDatatype *get_datatype(CowlPRTDecoder *d, ulib_uint offset) {
    CowlIRIOrAnonInd *iri = get_id_iri(d, offset);
    if (!iri) return NULL;
    return handle_null(d, cowl_datatype(iri));
}

static CowlNamedInd *get_named_ind(CowlPRTDecoder *d, ulib_uint offset) {
    CowlIRIOrAnonInd *iri = get_id_iri(d, offset);
    if (!iri) return NULL;
    return handle_null(d, cowl_named_ind(iri));
}

static CowlObjProp *get_obj_prop(CowlPRTDecoder *d, ulib_uint offset) {
    CowlIRIOrAnonInd *iri = get_id_iri(d, offset);
    if (!iri) return NULL;
    return handle_null(d, cowl_obj_prop(iri));
}

static CowlDataProp *get_data_prop(CowlPRTDecoder *d, ulib_uint offset) {
    CowlIRIOrAnonInd *iri = get_id_iri(d, offset);
    if (!iri) return NULL;
    return handle_null(d, cowl_data_prop(iri));
}

static CowlAnnotProp *get_annot_prop(CowlPRTDecoder *d, ulib_uint offset) {
    CowlIRIOrAnonInd *iri = get_id_iri(d, offset);
    if (!iri) return NULL;
    return handle_null(d, cowl_annot_prop(iri));
}

static CowlIndividual *get_individual(CowlPRTDecoder *d, ulib_uint offset) {
    CowlAny *id = get_id(d, offset);
    if (!id) return NULL;
    return cowl_is_individual(id) ? cowl_retain(id) : handle_null(d, cowl_named_ind(id));
}

static CowlIRI *decode_iri(CowlPRTDecoder *d) {
    ulib_uint offset;
    if (read_varint(d, &offset)) return NULL;
    return get_iri(d, offset);
}

static CowlIRIOrAnonInd *decode_iri_or_anon(CowlPRTDecoder *d) {
    ulib_uint offset;
    if (read_varint(d, &offset)) return NULL;
    return get_iri_or_anon(d, offset);
}

static CowlAnyEntity *decode_entity(CowlPRTDecoder *d, CowlEntityType type) {
    ulib_uint offset;
    if (read_varint(d, &offset)) return NULL;
    switch (type) {
        case COWL_ET_CLASS: return get_class(d, offset);
        case COWL_ET_ANNOT_PROP: return get_annot_prop(d, offset);
        case COWL_ET_DATA_PROP: return get_data_prop(d, offset);
        case COWL_ET_DATATYPE: return get_datatype(d, offset);
        case COWL_ET_NAMED_IND: return get_named_ind(d, offset);
        case COWL_ET_OBJ_PROP: return get_obj_prop(d, offset);
        default: break;
    }
    return NULL;
}

static CowlLiteral *decode_literal_typed(CowlPRTDecoder *d, CowlString *value) {
    CowlIRI *iri = decode_iri(d);
    if (!iri) return NULL;

    CowlLiteral *literal = NULL;
    CowlDatatype *dt = cowl_datatype(iri);
    if (dt) literal = handle_null(d, cowl_literal(value, dt));

    cowl_release_all(iri, dt);
    return literal;
}

static CowlLiteral *decode_literal_string(CowlPRTDecoder *d, CowlString *value) {
    return handle_null(d, cowl_literal(value, NULL));
}

static CowlLiteral *decode_literal_lang(CowlPRTDecoder *d, CowlString *value) {
    CowlString *lang = decode_string(d);
    if (!lang) return NULL;
    CowlLiteral *literal = handle_null(d, cowl_literal(value, lang));
    cowl_release(lang);
    return literal;
}

static CowlString *decode_literal_bool(CowlPRTDecoder *d) {
    ulib_byte b;
    if (read_bytes(d, &b, 1)) return NULL;
    switch ((CowlPRTLiteralBool)b) {
        case COWL_LB_FALSE: return cowl_string_from_literal(COWL_PRT_BOOL_FALSE);
        case COWL_LB_TRUE: return cowl_string_from_literal(COWL_PRT_BOOL_TRUE);
        default: return NULL;
    }
}

static CowlString *decode_literal_int(CowlPRTDecoder *d) {
    ulib_int v;
    if (read_svarint(d, &v)) return NULL;
    return cowl_string_with_format("%" ULIB_INT_FMT, v);
}

static CowlString *decode_literal_uint(CowlPRTDecoder *d) {
    ulib_uint v;
    if (read_varint(d, &v)) return NULL;
    return cowl_string_with_format("%" ULIB_UINT_FMT, v);
}

static ulib_ret buf_append_fixed_point(UStrBuf *buf, ulib_int whole, ulib_uint frac) {
    if (ustrbuf_append_format(buf, "%" ULIB_INT_FMT ".", whole)) return ULIB_ERR_MEM;
    ulib_uint const whole_len = ustrbuf_length(buf);
    if (ustrbuf_append_format(buf, "%" ULIB_UINT_FMT, frac)) return ULIB_ERR_MEM;
    ulib_str_reverse(ustrbuf_data(buf) + whole_len, ustrbuf_length(buf) - whole_len);
    return ULIB_OK;
}

static CowlString *decode_literal_fixed_point(CowlPRTDecoder *d) {
    ulib_int whole;
    ulib_uint frac;
    if (read_svarint(d, &whole) || read_varint(d, &frac)) return NULL;
    UStrBuf buf = ustrbuf();
    if (buf_append_fixed_point(&buf, whole, frac)) goto err;
    return cowl_string(ustrbuf_to_string(&buf));

err:
    ustrbuf_deinit(&buf);
    decoder_handle_error_code(d, COWL_ERR_MEM);
    return NULL;
}

static CowlString *decode_literal_e_notation(CowlPRTDecoder *d) {
    ulib_int whole;
    ulib_uint frac;
    ulib_int exp;
    if (read_svarint(d, &whole) || read_varint(d, &frac) || read_svarint(d, &exp)) return NULL;
    UStrBuf buf = ustrbuf();
    if (buf_append_fixed_point(&buf, whole, frac)) goto err;
    if (ustrbuf_append_format(&buf, "E%" ULIB_INT_FMT, exp)) goto err;
    return cowl_string(ustrbuf_to_string(&buf));

err:
    ustrbuf_deinit(&buf);
    decoder_handle_error_code(d, COWL_ERR_MEM);
    return NULL;
}

static CowlString *decode_literal_value(CowlPRTDecoder *d, CowlPRTLiteralValueFormat v) {
    switch (v) {
        case COWL_LVF_STRING: return decode_string(d);
        case COWL_LVF_BOOL: return decode_literal_bool(d);
        case COWL_LVF_INT: return decode_literal_int(d);
        case COWL_LVF_UINT: return decode_literal_uint(d);
        case COWL_LVF_FIXED_POINT: return decode_literal_fixed_point(d);
        case COWL_LVF_E_NOTATION: return decode_literal_e_notation(d);
        case COWL_LVF_COMP_STRING: // TO-DO: decompression.
        default: return NULL;
    }
}

static CowlLiteral *decode_literal(CowlPRTDecoder *d) {
    ulib_byte header;
    if (read_bytes(d, &header, sizeof(header))) return NULL;
    CowlPRTLiteralType const type = (CowlPRTLiteralType)(header & COWL_PRT_LITERAL_TYPE_BITMASK);
    CowlPRTLiteralValueFormat const v_type =
        (CowlPRTLiteralValueFormat)((header & COWL_PRT_VALUE_FORMAT_BITMASK) >>
                                    COWL_PRT_VALUE_FORMAT_OFFSET);

    CowlString *value = handle_null(d, decode_literal_value(d, v_type));
    CowlLiteral *literal = NULL;
    switch (type) {
        case COWL_OLT_STRING_LITERAL: literal = decode_literal_string(d, value); break;
        case COWL_OLT_STRING_LITERAL_LANGUAGE: literal = decode_literal_lang(d, value); break;
        case COWL_OLT_TYPED_LITERAL: literal = decode_literal_typed(d, value); break;
        default: break;
    }

    cowl_release(value);
    return literal;
}

static CowlAnnotProp *decode_annot_prop(CowlPRTDecoder *d) {
    ulib_uint offset;
    if (read_varint(d, &offset)) return NULL;
    return get_annot_prop(d, offset);
}

static CowlAnnotValue *decode_annot_value(CowlPRTDecoder *d) {
    ulib_uint value;
    if (read_varint(d, &value)) return NULL;
    return value ? get_iri_or_anon(d, value - 1) : decode_literal(d);
}

static CowlAnnotation *decode_annotation(CowlPRTDecoder *d) {
    CowlIRI *iri = NULL;
    CowlAnnotProp *prop = NULL;
    CowlAnnotValue *value = NULL;
    CowlVector *annots = NULL;
    CowlAnnotation *annot = NULL;

    ulib_uint has_no_annot;
    if (read_varint(d, &has_no_annot)) return NULL;
    iri = has_no_annot ? get_iri(d, has_no_annot - 1) : decode_iri(d);
    if (!iri) goto end;
    if (!(prop = cowl_annot_prop(iri))) goto end;
    if (!(value = decode_annot_value(d))) goto end;
    if (!has_no_annot && !(annots = decode_vector(d, annotation_item))) goto end;
    annot = cowl_annotation(prop, value, annots);

end:
    cowl_release_all(iri, prop, value, annots);
    return handle_null(d, annot);
}

static CowlIndividual *decode_individual(CowlPRTDecoder *d) {
    ulib_uint offset;
    if (read_varint(d, &offset)) return NULL;
    return get_individual(d, offset);
}

static CowlObjProp *decode_obj_prop(CowlPRTDecoder *d) {
    ulib_uint offset;
    if (read_varint(d, &offset)) return NULL;
    return get_obj_prop(d, offset);
}

static CowlInvObjProp *decode_inv_obj_prop(CowlPRTDecoder *d) {
    CowlObjProp *prop = decode_obj_prop(d);
    if (!prop) return NULL;
    CowlInvObjProp *inv = handle_null(d, cowl_inv_obj_prop(prop));
    cowl_release(prop);
    return inv;
}

static CowlObjPropExp *decode_obj_prop_exp(CowlPRTDecoder *d) {
    ulib_uint offset;
    if (read_varint(d, &offset)) return NULL;
    if (offset == 0) return (CowlObjPropExp *)decode_inv_obj_prop(d);
    return (CowlObjPropExp *)get_obj_prop(d, offset - 1);
}

static CowlDataPropExp *decode_data_prop_exp(CowlPRTDecoder *d) {
    ulib_uint offset;
    if (read_varint(d, &offset)) return NULL;
    return (CowlDataPropExp *)get_data_prop(d, offset);
}

static CowlFacetRestr *decode_facet_restr(CowlPRTDecoder *d) {
    CowlFacetRestr *restr = NULL;
    CowlIRI *iri = decode_iri(d);
    CowlAny *literal = decode_literal(d);
    if (iri && literal) restr = handle_null(d, cowl_facet_restr(iri, literal));
    cowl_release_all(iri, literal);
    return restr;
}

static CowlClass *decode_class(CowlPRTDecoder *d) {
    ulib_uint offset;
    if (read_varint(d, &offset)) return NULL;
    return get_class(d, offset);
}

static CowlObjQuant *decode_obj_quant(CowlPRTDecoder *d, CowlQuantType type) {
    CowlObjQuant *ce = NULL;
    CowlObjPropExp *prop = decode_obj_prop_exp(d);
    CowlClsExp *filler = decode_cls_exp(d);
    if (decoder_ok(d)) ce = handle_null(d, cowl_obj_quant(type, prop, filler));
    cowl_release_all(prop, filler);
    return ce;
}

static CowlObjCard *decode_obj_card(CowlPRTDecoder *d, CowlCardType type) {
    CowlObjCard *ce = NULL;
    ulib_uint cardinality;
    if (read_varint(d, &cardinality)) return NULL;

    CowlObjPropExp *prop = decode_obj_prop_exp(d);
    CowlClsExp *filler = NULL;
    bool has_filler = cardinality & 0x01;
    cardinality >>= 1;
    if (has_filler) filler = decode_cls_exp(d);

    if (decoder_ok(d)) ce = handle_null(d, cowl_obj_card(type, prop, filler, cardinality));
    cowl_release_all(prop, filler);
    return ce;
}

static CowlObjHasValue *decode_obj_has_value(CowlPRTDecoder *d) {
    CowlObjHasValue *ce = NULL;
    CowlObjPropExp *prop = decode_obj_prop_exp(d);
    CowlIndividual *ind = decode_individual(d);
    if (decoder_ok(d)) ce = handle_null(d, cowl_obj_has_value(prop, ind));
    cowl_release_all(prop, ind);
    return ce;
}

static CowlObjHasSelf *decode_obj_has_self(CowlPRTDecoder *d) {
    CowlObjHasSelf *ce = NULL;
    CowlObjPropExp *prop = decode_obj_prop_exp(d);
    if (decoder_ok(d)) ce = handle_null(d, cowl_obj_has_self(prop));
    cowl_release(prop);
    return ce;
}

static CowlDataQuant *decode_data_quant(CowlPRTDecoder *d, CowlQuantType type) {
    CowlDataQuant *ce = NULL;
    CowlDataPropExp *prop = decode_data_prop_exp(d);
    CowlDataRange *filler = decode_data_range(d);
    if (decoder_ok(d)) ce = handle_null(d, cowl_data_quant(type, prop, filler));
    cowl_release_all(prop, filler);
    return ce;
}

static CowlDataCard *decode_data_card(CowlPRTDecoder *d, CowlCardType type) {
    CowlDataCard *ce = NULL;
    ulib_uint cardinality;
    if (read_varint(d, &cardinality)) return NULL;

    CowlDataPropExp *prop = decode_data_prop_exp(d);
    CowlDataRange *filler = NULL;
    bool has_filler = cardinality & 0x01;
    cardinality >>= 1;
    if (has_filler) filler = decode_data_range(d);

    if (decoder_ok(d)) ce = handle_null(d, cowl_data_card(type, prop, filler, cardinality));
    cowl_release_all(prop, filler);
    return ce;
}

static CowlDataHasValue *decode_data_has_value(CowlPRTDecoder *d) {
    CowlDataHasValue *ce = NULL;
    CowlDataPropExp *prop = decode_data_prop_exp(d);
    CowlAny *literal = decode_literal(d);
    if (decoder_ok(d)) ce = handle_null(d, cowl_data_has_value(prop, literal));
    cowl_release_all(prop, literal);
    return ce;
}

static CowlNAryBool *decode_nary_cls_exp(CowlPRTDecoder *d, CowlNAryType cls_exp_type) {
    CowlNAryBool *ce = NULL;
    CowlVector *operands = decode_vector(d, cls_exp_item);
    if (decoder_ok(d)) ce = handle_null(d, cowl_nary_bool(cls_exp_type, operands));
    cowl_release(operands);
    return ce;
}

static CowlObjCompl *decode_obj_compl(CowlPRTDecoder *d) {
    CowlObjCompl *ce = NULL;
    CowlClsExp *operand = decode_cls_exp(d);
    if (decoder_ok(d)) ce = handle_null(d, cowl_obj_compl(operand));
    cowl_release(operand);
    return ce;
}

static CowlObjOneOf *decode_obj_one_of(CowlPRTDecoder *d) {
    CowlObjOneOf *ce = NULL;
    CowlVector *inds = decode_vector(d, individual_item);
    if (decoder_ok(d)) ce = handle_null(d, cowl_obj_one_of(inds));
    cowl_release(inds);
    return ce;
}

static CowlAnyClsExp *decode_cls_exp(CowlPRTDecoder *d) {
    ulib_uint type;
    if (read_varint(d, &type)) return NULL;

    if (type >= COWL_CET_COUNT - 1) {
        return get_class(d, type - COWL_CET_COUNT + 1);
    }

    switch ((CowlClsExpType)(type + 1)) {
        case COWL_CET_OBJ_SOME: return decode_obj_quant(d, COWL_QT_SOME);
        case COWL_CET_OBJ_ALL: return decode_obj_quant(d, COWL_QT_ALL);
        case COWL_CET_OBJ_MIN_CARD: return decode_obj_card(d, COWL_CT_MIN);
        case COWL_CET_OBJ_MAX_CARD: return decode_obj_card(d, COWL_CT_MAX);
        case COWL_CET_OBJ_EXACT_CARD: return decode_obj_card(d, COWL_CT_EXACT);
        case COWL_CET_OBJ_HAS_VALUE: return decode_obj_has_value(d);
        case COWL_CET_OBJ_HAS_SELF: return decode_obj_has_self(d);
        case COWL_CET_DATA_SOME: return decode_data_quant(d, COWL_QT_SOME);
        case COWL_CET_DATA_ALL: return decode_data_quant(d, COWL_QT_ALL);
        case COWL_CET_DATA_MIN_CARD: return decode_data_card(d, COWL_CT_MIN);
        case COWL_CET_DATA_MAX_CARD: return decode_data_card(d, COWL_CT_MAX);
        case COWL_CET_DATA_EXACT_CARD: return decode_data_card(d, COWL_CT_EXACT);
        case COWL_CET_DATA_HAS_VALUE: return decode_data_has_value(d);
        case COWL_CET_OBJ_INTERSECT: return decode_nary_cls_exp(d, COWL_NT_INTERSECT);
        case COWL_CET_OBJ_UNION: return decode_nary_cls_exp(d, COWL_NT_UNION);
        case COWL_CET_OBJ_COMPL: return decode_obj_compl(d);
        case COWL_CET_OBJ_ONE_OF: return decode_obj_one_of(d);
        default: break;
    }

    decoder_handle_error(d, COWL_ERR_SYNTAX, "invalid class expression type %" ULIB_UINT_FMT, type);
    return NULL;
}

static CowlDatatype *decode_datatype(CowlPRTDecoder *d) {
    ulib_uint offset;
    if (read_varint(d, &offset)) return NULL;
    return get_datatype(d, offset);
}

static CowlNAryData *decode_nary_data(CowlPRTDecoder *d, CowlNAryType type) {
    CowlNAryData *dr = NULL;
    CowlVector *operands = decode_vector(d, data_range_item);
    if (decoder_ok(d)) dr = handle_null(d, cowl_nary_data(type, operands));
    cowl_release(operands);
    return dr;
}

static CowlDataCompl *decode_data_compl(CowlPRTDecoder *d) {
    CowlDataCompl *dr = NULL;
    CowlDataRange *operand = decode_data_range(d);
    if (decoder_ok(d)) dr = handle_null(d, cowl_data_compl(operand));
    cowl_release(operand);
    return dr;
}

static CowlDataOneOf *decode_data_one_of(CowlPRTDecoder *d) {
    CowlDataOneOf *dr = NULL;
    CowlVector *operands = decode_vector(d, literal_item);
    if (decoder_ok(d)) dr = handle_null(d, cowl_data_one_of(operands));
    cowl_release(operands);
    return dr;
}

static CowlDatatypeRestr *decode_datatype_restr(CowlPRTDecoder *d) {
    CowlDatatypeRestr *dr = NULL;
    CowlDatatype *dt = decode_datatype(d);
    CowlVector *restrs = decode_vector(d, facet_restr_item);
    if (decoder_ok(d)) dr = handle_null(d, cowl_datatype_restr(dt, restrs));
    cowl_release_all(dt, restrs);
    return dr;
}

static CowlAnyDataRange *decode_data_range(CowlPRTDecoder *d) {
    ulib_uint type;
    if (read_varint(d, &type)) return NULL;

    if (type >= COWL_DRT_COUNT - 1) {
        return get_datatype(d, type - COWL_DRT_COUNT + 1);
    }

    switch ((CowlDataRangeType)type + 1) {
        case COWL_DRT_DATATYPE_RESTR: return decode_datatype_restr(d);
        case COWL_DRT_DATA_INTERSECT: return decode_nary_data(d, COWL_NT_INTERSECT);
        case COWL_DRT_DATA_UNION: return decode_nary_data(d, COWL_NT_UNION);
        case COWL_DRT_DATA_COMPL: return decode_data_compl(d);
        case COWL_DRT_DATA_ONE_OF: return decode_data_one_of(d);
        default: break;
    }

    decoder_handle_error(d, COWL_ERR_SYNTAX, "invalid data range type %" ULIB_UINT_FMT, type);
    return NULL;
}

static CowlDeclAxiom *
decode_declaration_axiom(CowlPRTDecoder *d, CowlEntityType entity_type, bool has_annot) {
    CowlDeclAxiom *axiom = NULL;
    CowlAnyEntity *entity = decode_entity(d, entity_type);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_decl_axiom(entity, annot));
    cowl_release_all(entity, annot);
    return axiom;
}

static CowlNAryClsAxiom *
decode_nary_class_axiom(CowlPRTDecoder *d, CowlNAryAxiomType type, bool has_annot) {
    CowlNAryClsAxiom *axiom = NULL;
    CowlVector *op = decode_vector(d, cls_exp_item);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_nary_cls_axiom(type, op, annot));
    cowl_release_all(op, annot);
    return axiom;
}

static CowlDisjUnionAxiom *decode_disj_union_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlDisjUnionAxiom *axiom = NULL;
    CowlClass *cls = decode_class(d);
    CowlVector *disj = decode_vector(d, cls_exp_item);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_disj_union_axiom(cls, disj, annot));
    cowl_release_all(cls, disj, annot);
    return axiom;
}

static CowlSubClsAxiom *decode_sub_cls_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlSubClsAxiom *axiom = NULL;
    CowlClsExp *sub = decode_cls_exp(d);
    CowlClsExp *sup = decode_cls_exp(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_sub_cls_axiom(sub, sup, annot));
    cowl_release_all(sub, sup, annot);
    return axiom;
}

static CowlClsAssertAxiom *decode_cls_assert_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlClsAssertAxiom *axiom = NULL;
    CowlClsExp *ce = decode_cls_exp(d);
    CowlIndividual *ind = decode_individual(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_cls_assert_axiom(ce, ind, annot));
    cowl_release_all(ce, ind, annot);
    return axiom;
}

static CowlNAryIndAxiom *
decode_nary_ind_axiom(CowlPRTDecoder *d, CowlNAryAxiomType type, bool has_annot) {
    CowlNAryIndAxiom *axiom = NULL;
    CowlVector *inds = decode_vector(d, individual_item);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_nary_ind_axiom(type, inds, annot));
    cowl_release_all(inds, annot);
    return axiom;
}

static CowlNAryObjPropAxiom *
decode_nary_obj_prop_axiom(CowlPRTDecoder *d, CowlNAryAxiomType type, bool has_annot) {
    CowlNAryObjPropAxiom *axiom = NULL;
    CowlVector *props = decode_vector(d, obj_prop_exp_item);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_nary_obj_prop_axiom(type, props, annot));
    cowl_release_all(props, annot);
    return axiom;
}

static CowlObjPropCharAxiom *
decode_obj_prop_char_axiom(CowlPRTDecoder *d, CowlCharAxiomType type, bool has_annot) {
    CowlObjPropCharAxiom *axiom = NULL;
    CowlObjPropExp *prop = decode_obj_prop_exp(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_obj_prop_char_axiom(type, prop, annot));
    cowl_release_all(prop, annot);
    return axiom;
}

static CowlObjPropDomainAxiom *decode_obj_prop_domain_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlObjPropDomainAxiom *axiom = NULL;
    CowlObjPropExp *prop = decode_obj_prop_exp(d);
    CowlClsExp *domain = decode_cls_exp(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_obj_prop_domain_axiom(prop, domain, annot));
    cowl_release_all(prop, domain, annot);
    return axiom;
}

static CowlObjPropRangeAxiom *decode_obj_prop_range_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlObjPropRangeAxiom *axiom = NULL;
    CowlObjPropExp *prop = decode_obj_prop_exp(d);
    CowlClsExp *range = decode_cls_exp(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_obj_prop_range_axiom(prop, range, annot));
    cowl_release_all(prop, range, annot);
    return axiom;
}

static CowlSubDataPropAxiom *decode_sub_data_prop_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlSubDataPropAxiom *axiom = NULL;
    CowlDataPropExp *sub = decode_data_prop_exp(d);
    CowlDataPropExp *sup = decode_data_prop_exp(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_sub_data_prop_axiom(sub, sup, annot));
    cowl_release_all(sub, sup, annot);
    return axiom;
}

static CowlNAryDataPropAxiom *
decode_nary_data_prop_axiom(CowlPRTDecoder *d, CowlNAryAxiomType type, bool has_annot) {
    CowlNAryDataPropAxiom *axiom = NULL;
    CowlVector *props = decode_vector(d, data_prop_exp_item);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_nary_data_prop_axiom(type, props, annot));
    cowl_release_all(props, annot);
    return axiom;
}

static CowlFuncDataPropAxiom *decode_func_data_prop_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlFuncDataPropAxiom *axiom = NULL;
    CowlDataPropExp *prop = decode_data_prop_exp(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_func_data_prop_axiom(prop, annot));
    cowl_release_all(prop, annot);
    return axiom;
}

static CowlDataPropDomainAxiom *decode_data_prop_domain_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlDataPropDomainAxiom *axiom = NULL;
    CowlDataPropExp *prop = decode_data_prop_exp(d);
    CowlClsExp *domain = decode_cls_exp(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_data_prop_domain_axiom(prop, domain, annot));
    cowl_release_all(prop, domain, annot);
    return axiom;
}

static CowlObjPropAssertAxiom *decode_neg_obj_prop_assert_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlObjPropAssertAxiom *axiom = NULL;
    CowlObjPropExp *prop = decode_obj_prop_exp(d);
    CowlIndividual *subject = decode_individual(d);
    CowlIndividual *object = decode_individual(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d))
        axiom = handle_null(d, cowl_neg_obj_prop_assert_axiom(prop, subject, object, annot));
    cowl_release_all(prop, subject, object, annot);
    return axiom;
}

static CowlDataPropAssertAxiom *decode_data_prop_assert_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlDataPropAssertAxiom *axiom = NULL;
    CowlDataPropExp *prop = decode_data_prop_exp(d);
    CowlIndividual *subj = decode_individual(d);
    CowlLiteral *obj = decode_literal(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_data_prop_assert_axiom(prop, subj, obj, annot));
    cowl_release_all(prop, obj, subj, annot);
    return axiom;
}

static CowlDataPropAssertAxiom *
decode_neg_data_prop_assert_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlDataPropAssertAxiom *axiom = NULL;
    CowlDataPropExp *prop = decode_data_prop_exp(d);
    CowlIndividual *subj = decode_individual(d);
    CowlLiteral *obj = decode_literal(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d))
        axiom = handle_null(d, cowl_neg_data_prop_assert_axiom(prop, subj, obj, annot));
    cowl_release_all(prop, subj, obj, annot);
    return axiom;
}

static CowlSubObjPropAxiom *
decode_sub_obj_prop_axiom(CowlPRTDecoder *d, bool has_u_bit, bool has_annot) {
    CowlAny *sub = NULL;
    CowlObjPropExp *sup = NULL;
    CowlVector *annot = NULL;
    CowlSubObjPropAxiom *axiom = NULL;
    if (has_u_bit) {
        sub = decode_vector(d, obj_prop_exp_item);
        sup = decode_obj_prop_exp(d);
        if (has_annot) annot = decode_vector(d, annotation_item);
        axiom = cowl_sub_obj_prop_chain_axiom(sub, sup, annot);
    } else {
        sub = decode_obj_prop_exp(d);
        sup = decode_obj_prop_exp(d);
        if (has_annot) annot = decode_vector(d, annotation_item);
        axiom = cowl_sub_obj_prop_axiom(sub, sup, annot);
    }
    if (decoder_ok(d)) axiom = handle_null(d, axiom);
    cowl_release_all(sub, sup, annot);
    return axiom;
}

static CowlInvObjPropAxiom *decode_inv_obj_prop_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlInvObjPropAxiom *axiom = NULL;
    CowlObjPropExp *first = decode_obj_prop_exp(d);
    CowlObjPropExp *second = decode_obj_prop_exp(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_inv_obj_prop_axiom(first, second, annot));
    cowl_release_all(first, second, annot);
    return axiom;
}

static CowlObjPropAssertAxiom *decode_obj_prop_assert_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlObjPropAssertAxiom *axiom = NULL;
    CowlObjPropExp *prop = decode_obj_prop_exp(d);
    CowlIndividual *subj = decode_individual(d);
    CowlIndividual *obj = decode_individual(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_obj_prop_assert_axiom(prop, subj, obj, annot));
    cowl_release_all(prop, subj, obj, annot);
    return axiom;
}

static CowlDataPropRangeAxiom *decode_data_prop_range_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlDataPropRangeAxiom *axiom = NULL;
    CowlDataPropExp *prop = decode_data_prop_exp(d);
    CowlDataRange *dr = decode_data_range(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_data_prop_range_axiom(prop, dr, annot));
    cowl_release_all(prop, dr, annot);
    return axiom;
}

static CowlHasKeyAxiom *decode_has_key_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlHasKeyAxiom *axiom = NULL;
    CowlClsExp *ce = decode_cls_exp(d);
    CowlVector *op = decode_vector(d, obj_prop_exp_item);
    CowlVector *dp = decode_vector(d, data_prop_exp_item);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_has_key_axiom(ce, op, dp, annot));
    cowl_release_all(ce, op, dp, annot);
    return axiom;
}

static CowlAnnotAssertAxiom *decode_annot_assert_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlAnnotAssertAxiom *axiom = NULL;
    CowlAnnotProp *prop = decode_annot_prop(d);
    CowlIRIOrAnonInd *subj = decode_iri_or_anon(d);
    CowlAnyAnnotValue *value = decode_annot_value(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_annot_assert_axiom(prop, subj, value, annot));
    cowl_release_all(prop, value, subj, annot);
    return axiom;
}

static CowlSubAnnotPropAxiom *decode_sub_annot_prop_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlSubAnnotPropAxiom *axiom = NULL;
    CowlAnnotProp *sub = decode_annot_prop(d);
    CowlAnnotProp *sup = decode_annot_prop(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_sub_annot_prop_axiom(sub, sup, annot));
    cowl_release_all(sub, sup, annot);
    return axiom;
}

static CowlAnnotPropDomainAxiom *decode_annot_prop_domain_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlAnnotPropDomainAxiom *axiom = NULL;
    CowlAnnotProp *prop = decode_annot_prop(d);
    CowlIRI *domain = decode_iri(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_annot_prop_domain_axiom(prop, domain, annot));
    cowl_release_all(prop, domain, annot);
    return axiom;
}

static CowlAnnotPropRangeAxiom *decode_annot_prop_range_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlAnnotPropRangeAxiom *axiom = NULL;
    CowlAnnotProp *prop = decode_annot_prop(d);
    CowlIRI *range = decode_iri(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_annot_prop_range_axiom(prop, range, annot));
    cowl_release_all(prop, range, annot);
    return axiom;
}

static CowlDatatypeDefAxiom *decode_datatype_def_axiom(CowlPRTDecoder *d, bool has_annot) {
    CowlDatatypeDefAxiom *axiom = NULL;
    CowlDatatype *dt = decode_datatype(d);
    CowlDataRange *dr = decode_data_range(d);
    CowlVector *annot = has_annot ? decode_vector(d, annotation_item) : NULL;
    if (decoder_ok(d)) axiom = handle_null(d, cowl_datatype_def_axiom(dt, dr, annot));
    cowl_release_all(dt, dr, annot);
    return axiom;
}

static CowlAnyAxiom *decode_axiom(CowlPRTDecoder *d, ulib_byte header) {
    ulib_byte type = (header & COWL_PRT_AXIOM_TYPE_BITMASK) - COWL_PRT_FIRST_AXIOM_FRAME;
    ulib_byte has_annot = header & COWL_PRT_AXIOM_ANNOT_BITMASK;
    ulib_byte has_u_bit = header & COWL_PRT_AXIOM_UTILITY_BITMASK;

    if (type < COWL_ET_COUNT) {
        CowlEntityType entity_type = (CowlEntityType)type;
        return decode_declaration_axiom(d, entity_type, has_annot);
    }

    switch ((CowlAxiomType)(type - COWL_ET_COUNT + 1)) {
        case COWL_AT_DATATYPE_DEF: return decode_datatype_def_axiom(d, has_annot);
        case COWL_AT_SUB_CLASS: return decode_sub_cls_axiom(d, has_annot);
        case COWL_AT_EQUIV_CLASSES: return decode_nary_class_axiom(d, COWL_NAT_EQUIV, has_annot);
        case COWL_AT_DISJ_CLASSES: return decode_nary_class_axiom(d, COWL_NAT_DISJ, has_annot);
        case COWL_AT_DISJ_UNION: return decode_disj_union_axiom(d, has_annot);
        case COWL_AT_CLASS_ASSERT: return decode_cls_assert_axiom(d, has_annot);
        case COWL_AT_SAME_IND: return decode_nary_ind_axiom(d, COWL_NAT_SAME, has_annot);
        case COWL_AT_DIFF_IND: return decode_nary_ind_axiom(d, COWL_NAT_DIFF, has_annot);
        case COWL_AT_OBJ_PROP_ASSERT: return decode_obj_prop_assert_axiom(d, has_annot);
        case COWL_AT_NEG_OBJ_PROP_ASSERT: return decode_neg_obj_prop_assert_axiom(d, has_annot);
        case COWL_AT_DATA_PROP_ASSERT: return decode_data_prop_assert_axiom(d, has_annot);
        case COWL_AT_NEG_DATA_PROP_ASSERT: return decode_neg_data_prop_assert_axiom(d, has_annot);
        case COWL_AT_SUB_OBJ_PROP: return decode_sub_obj_prop_axiom(d, has_u_bit, has_annot);
        case COWL_AT_INV_OBJ_PROP: return decode_inv_obj_prop_axiom(d, has_annot);
        case COWL_AT_EQUIV_OBJ_PROP:
            return decode_nary_obj_prop_axiom(d, COWL_NAT_EQUIV, has_annot);
        case COWL_AT_DISJ_OBJ_PROP: return decode_nary_obj_prop_axiom(d, COWL_NAT_DISJ, has_annot);
        case COWL_AT_FUNC_OBJ_PROP: return decode_obj_prop_char_axiom(d, COWL_CAT_FUNC, has_annot);
        case COWL_AT_INV_FUNC_OBJ_PROP:
            return decode_obj_prop_char_axiom(d, COWL_CAT_INV_FUNC, has_annot);
        case COWL_AT_SYMM_OBJ_PROP: return decode_obj_prop_char_axiom(d, COWL_CAT_SYMM, has_annot);
        case COWL_AT_ASYMM_OBJ_PROP:
            return decode_obj_prop_char_axiom(d, COWL_CAT_ASYMM, has_annot);
        case COWL_AT_TRANS_OBJ_PROP:
            return decode_obj_prop_char_axiom(d, COWL_CAT_TRANS, has_annot);
        case COWL_AT_REFL_OBJ_PROP: return decode_obj_prop_char_axiom(d, COWL_CAT_REFL, has_annot);
        case COWL_AT_IRREFL_OBJ_PROP:
            return decode_obj_prop_char_axiom(d, COWL_CAT_IRREFL, has_annot);
        case COWL_AT_OBJ_PROP_DOMAIN: return decode_obj_prop_domain_axiom(d, has_annot);
        case COWL_AT_OBJ_PROP_RANGE: return decode_obj_prop_range_axiom(d, has_annot);
        case COWL_AT_SUB_DATA_PROP: return decode_sub_data_prop_axiom(d, has_annot);
        case COWL_AT_EQUIV_DATA_PROP:
            return decode_nary_data_prop_axiom(d, COWL_NAT_EQUIV, has_annot);
        case COWL_AT_DISJ_DATA_PROP:
            return decode_nary_data_prop_axiom(d, COWL_NAT_DISJ, has_annot);
        case COWL_AT_FUNC_DATA_PROP: return decode_func_data_prop_axiom(d, has_annot);
        case COWL_AT_DATA_PROP_DOMAIN: return decode_data_prop_domain_axiom(d, has_annot);
        case COWL_AT_DATA_PROP_RANGE: return decode_data_prop_range_axiom(d, has_annot);
        case COWL_AT_HAS_KEY: return decode_has_key_axiom(d, has_annot);
        case COWL_AT_ANNOT_ASSERT: return decode_annot_assert_axiom(d, has_annot);
        case COWL_AT_SUB_ANNOT_PROP: return decode_sub_annot_prop_axiom(d, has_annot);
        case COWL_AT_ANNOT_PROP_DOMAIN: return decode_annot_prop_domain_axiom(d, has_annot);
        case COWL_AT_ANNOT_PROP_RANGE: return decode_annot_prop_range_axiom(d, has_annot);
        default: break;
    }

    decoder_handle_error(d, COWL_ERR_SYNTAX, "invalid axiom type %" ULIB_UINT_FMT, type);
    return NULL;
}

static void decode_axiom_frame(CowlPRTDecoder *d, ulib_byte header) {
    CowlAxiom *axiom;
    if (decoder_ok(d) && (axiom = decode_axiom(d, header))) {
        decoder_handle_change(d, COWL_PART_AXIOM, axiom);
        cowl_release(axiom);
    }
}

static void register_prefix_decl(CowlPRTDecoder *d, CowlString *prefix, CowlString *ns) {
    cowl_ret ret = cowl_prt_index_add_prefix(&d->index, ns, prefix);
    if (cowl_is_err(ret)) {
        decoder_handle_error_code(d, ret);
        return;
    }
    CowlPrefixDecl decl = { .prefix = prefix, .ns = ns };
    decoder_handle_change(d, COWL_PART_PREFIX_DECL, &decl);
}

static void decode_prefix_decl(CowlPRTDecoder *d) {
    CowlString *prefix = decode_string(d);
    CowlString *ns = decode_string_intern(d);
    if (prefix && ns) register_prefix_decl(d, prefix, ns);
    cowl_release_all(prefix, ns);
}

static void decode_prefix_decls(CowlPRTDecoder *d) {
    ulib_uint length;
    if (read_varint(d, &length)) return;
    for (ulib_uint i = 0; decoder_ok(d) && i < length; ++i) {
        decode_prefix_decl(d);
    }
}

static void decode_ns_decls(CowlPRTDecoder *d) {
    ulib_uint length;
    if (read_varint(d, &length)) return;
    for (ulib_uint i = 0; decoder_ok(d) && i < length; ++i) {
        CowlString *ns = decode_string(d);
        if (ns) decoder_handle_error_code(d, cowl_prt_index_add_prefix(&d->index, ns, NULL));
        cowl_release(ns);
    }
}

static void decode_ns_decls_frame(CowlPRTDecoder *d, bool is_prefix) {
    if (is_prefix) {
        decode_prefix_decls(d);
    } else {
        decode_ns_decls(d);
    }
}

static void decode_iri_decl(CowlPRTDecoder *d) {
    ulib_uint prefix;
    if (read_varint(d, &prefix)) return;

    CowlIRI *id = NULL;
    CowlString *string = decode_string(d);
    if (!string) goto end;

    CowlString *ns = cowl_prt_index_get_ns(&d->index, prefix);
    if (!ns) {
        decoder_handle_error(d, COWL_ERR_SYNTAX, "prefix index %" ULIB_UINT_FMT " out of bounds",
                             prefix);
        goto end;
    }

    id = cowl_iri(ns, string);
    if (!id || cowl_prt_index_add_primitive(&d->index, id)) {
        decoder_handle_error_code(d, COWL_ERR_MEM);
    }

end:
    cowl_release_all(string, id);
}

static void decode_iri_decls(CowlPRTDecoder *d) {
    ulib_uint length;
    if (read_varint(d, &length)) return;
    for (ulib_uint i = 0; decoder_ok(d) && i < length; ++i) {
        decode_iri_decl(d);
    }
}

static void decode_anon_decl(CowlPRTDecoder *d) {
    CowlString *string = decode_string(d);
    if (!string) return;
    CowlAnonInd *id;
    id = cowl_anon_ind(string);
    if (!id || cowl_prt_index_add_primitive(&d->index, id)) {
        decoder_handle_error_code(d, COWL_ERR_MEM);
    }
    cowl_release_all(string, id);
}

static void decode_anon_decls(CowlPRTDecoder *d) {
    ulib_uint length;
    if (read_varint(d, &length)) return;
    for (ulib_uint i = 0; decoder_ok(d) && i < length; ++i) {
        decode_anon_decl(d);
    }
}

static void decode_id_decls_frame(CowlPRTDecoder *d, bool is_iri) {
    if (is_iri) {
        decode_iri_decls(d);
    } else {
        decode_anon_decls(d);
    }
}

static void decode_ontology_iri(CowlPRTDecoder *d) {
    CowlIRI *iri = decode_iri(d);
    if (!iri) return;
    decoder_handle_change(d, COWL_PART_IRI, iri);
    cowl_release(iri);
}

static void decode_version_iri(CowlPRTDecoder *d) {
    CowlIRI *version = decode_iri(d);
    if (!version) return;
    decoder_handle_change(d, COWL_PART_VERSION, version);
    cowl_release(version);
}

static void decode_iri_version_frame(CowlPRTDecoder *d, bool has_version) {
    decode_ontology_iri(d);
    if (has_version) decode_version_iri(d);
}

static void decode_annotations_frame(CowlPRTDecoder *d) {
    ulib_uint length;
    if (read_varint(d, &length)) return;
    for (ulib_uint i = 0; decoder_ok(d) && i < length; ++i) {
        CowlAnnotation *annot = decode_annotation(d);
        if (!annot) return;
        decoder_handle_change(d, COWL_PART_ANNOTATION, annot);
        cowl_release(annot);
    }
}

static void decode_imports_frame(CowlPRTDecoder *d) {
    ulib_uint length;
    if (read_varint(d, &length)) return;
    for (ulib_uint i = 0; decoder_ok(d) && i < length; ++i) {
        CowlIRI *import = decode_iri(d);
        if (!import) return;
        decoder_handle_change(d, COWL_PART_IMPORT, import);
        cowl_release(import);
    }
}

static inline void handle_add_frame(CowlPRTDecoder *d) {
    d->remove = false;
}

static inline void handle_remove_frame(CowlPRTDecoder *d) {
    d->remove = true;
}

static inline void handle_reset_frame(CowlPRTDecoder *d, bool prefixes, bool ids) {
    if (prefixes) {
        decoder_handle_error_code(d, cowl_prt_index_reset_prefixes(&d->index));
        if (!decoder_ok(d)) return;
    }
    if (ids) {
        decoder_handle_error_code(d, cowl_prt_index_reset_ids(&d->index));
        if (!decoder_ok(d)) return;
    }
}

static bool decode_frame(CowlPRTDecoder *d) {
    ulib_byte header;
    size_t read;
    if (uistream_read(d->stream, &header, sizeof(header), &read) || read == 0) return false;

    switch (header & COWL_PRT_FRAME_TYPE_BITMASK) {
        case COWL_PRT_ADD_FRAME: handle_add_frame(d); break;
        case COWL_PRT_REMOVE_FRAME: handle_remove_frame(d); break;
        case COWL_PRT_RESET_FRAME:
            handle_reset_frame(d, header & COWL_PRT_RESET_NS_BITMASK,
                               header & COWL_PRT_RESET_ID_BITMASK);
            break;
        case COWL_PRT_END_FRAME: return false;
        case COWL_PRT_NS_DECLS_FRAME:
            decode_ns_decls_frame(d, header & COWL_PRT_NS_DECL_IS_PREFIX_BITMASK);
            break;
        case COWL_PRT_ID_DECLS_FRAME:
            decode_id_decls_frame(d, header & COWL_PRT_ID_DECL_IS_IRI_BITMASK);
            break;
        case COWL_PRT_IRI_VERSION_FRAME:
            decode_iri_version_frame(d, header & COWL_PRT_VERSION_BITMASK);
            break;
        case COWL_PRT_IMPORTS_FRAME: decode_imports_frame(d); break;
        case COWL_PRT_ANNOTATIONS_FRAME: decode_annotations_frame(d); break;
        default: decode_axiom_frame(d, header); break;
    }

    return true;
}

static void decode_frames(CowlPRTDecoder *d) {
    while (decoder_ok(d) && decode_frame(d));
}

static void decode_header(CowlPRTDecoder *d) {
    ulib_byte header;
    if (read_bytes(d, &header, sizeof(header))) return;
    if (header == COWL_PRT_FORMAT_VERSION) return;
    decoder_handle_error(d, COWL_ERR_SYNTAX, "invalid format version %d", header);
}

static cowl_ret read_ontology(void *ctx, UIStream *stream, CowlChangeHandler handler) {
    cowl_ret ret = COWL_OK;
    CowlError *err = ctx;
    CowlPRTDecoder d = ulib_zero_init;

    if (decoder_init(&d, stream, &handler, err)) goto end;
    decode_header(&d);
    decode_frames(&d);

end:
    ret = decoder_state(&d);
    if (cowl_is_err(ret)) err->byte = (ulib_uint)stream->read_bytes;
    decoder_deinit(&d);
    return ret;
}

static CowlError const *last_error(void *ctx) {
    return ctx;
}

static void free_error(void *err) {
    cowl_error_deinit(err);
    ulib_free(err);
}

CowlReader *cowl_reader_protocowl(void) {
    CowlError *err = ulib_alloc(err);
    if (!err) return NULL;
    *err = cowl_error(COWL_OK, NULL);

    return cowl_reader((CowlReaderImpl){
        .name = "ProtocOWL",
        .ctx = err,
        .read = read_ontology,
        .last_error = last_error,
        .free = free_error,
    });
}
