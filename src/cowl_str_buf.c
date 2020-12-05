/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_str_buf.h"
#include "cowl_private.h"

#include <stdio.h>

UVEC_IMPL(CowlChar)

#if COWL_UINT_MAX <= 0xffff
    #define COWL_UINT_MAX_DIGITS 5
#elif COWL_UINT_MAX <= 0xffffffff
    #define COWL_UINT_MAX_DIGITS 10
#else
    #define COWL_UINT_MAX_DIGITS 20
#endif

static char* cowl_str_buf_deinit_get_storage(CowlStrBuf *buf) {
    char *storage = buf->storage.storage;
    buf->storage.storage = NULL;
    cowl_str_buf_deinit(buf);
    return storage;
}

static cowl_uint cowl_cstring_length_of_formatted(char const *format, va_list argptr) {
    va_list args;
    va_copy(args, argptr);
    int res = vsnprintf(NULL, 0, format, args);
    va_end(args);
    return res > 0 ? (cowl_uint)res : 0;
}

cowl_ret cowl_str_buf_append_cstring(CowlStrBuf *buf, char const *string, cowl_uint length) {
    if (!buf->ret) {
        uvec_ret ret = uvec_append_array(CowlChar, &buf->storage, string, length);
        buf->ret = ret == UVEC_OK ? COWL_OK : COWL_ERR_MEM;
    }
    return buf->ret;
}

cowl_ret cowl_str_buf_append_raw_string(CowlStrBuf *buf, CowlRawString string) {
    return cowl_str_buf_append_cstring(buf, string.cstring, string.length);
}

cowl_ret cowl_str_buf_append_string(CowlStrBuf *buf, CowlString *string) {
    return cowl_str_buf_append_raw_string(buf, string->raw_string);
}

cowl_ret cowl_str_buf_append_format(CowlStrBuf *buf, char const *format, ...) {
    va_list args;
    va_start(args, format);
    cowl_ret ret = cowl_str_buf_append_format_list(buf, format, args);
    va_end(args);
    return ret;
}

cowl_ret cowl_str_buf_append_format_list(CowlStrBuf *buf, char const *format, va_list args) {
    if (buf->ret) goto end;

    cowl_uint length = cowl_cstring_length_of_formatted(format, args);
    size_t size = length + 1;

    if (uvec_expand(CowlChar, &buf->storage, (uvec_uint)size) != UVEC_OK) {
        buf->ret = COWL_ERR_MEM;
    } else {
        vsnprintf(buf->storage.storage + buf->storage.count, size, format, args);
        buf->storage.count += length;
    }

end:
    return buf->ret;
}

// Misc

cowl_ret cowl_str_buf_append_object(CowlStrBuf *buf, CowlObject *obj) {
    if (cowl_object_is_entity(obj)) {
        return cowl_str_buf_append_entity(buf, (CowlEntity *)obj);
    } else if (cowl_object_is_axiom(obj)) {
        return cowl_str_buf_append_axiom(buf, (CowlAxiom *)obj);
    } else if (cowl_object_is_cls_exp(obj)) {
        return cowl_str_buf_append_cls_exp(buf, (CowlClsExp *)obj);
    } else if (cowl_object_is_obj_prop_exp(obj)) {
        return cowl_str_buf_append_obj_prop_exp(buf, (CowlObjPropExp *)obj);
    } else if (cowl_object_is_data_prop_exp(obj)) {
        return cowl_str_buf_append_data_prop_exp(buf, (CowlDataPropExp *)obj);
    } else if (cowl_object_is_individual(obj)) {
        return cowl_str_buf_append_individual(buf, (CowlIndividual *)obj);
    } else if (cowl_object_is_data_range(obj)) {
        return cowl_str_buf_append_data_range(buf, (CowlDataRange *)obj);
    }
    switch (cowl_object_get_type(obj)) {
        case COWL_OT_STRING: return cowl_str_buf_append_string(buf, (CowlString *)obj);
        case COWL_OT_IRI: return cowl_str_buf_append_iri(buf, (CowlIRI *)obj);
        case COWL_OT_LITERAL: return cowl_str_buf_append_literal(buf, (CowlLiteral *)obj);
        case COWL_OT_FACET_RESTR: return cowl_str_buf_append_facet_restr(buf, (CowlFacetRestr *)obj);
        case COWL_OT_ANNOTATION: return cowl_str_buf_append_annotation(buf, (CowlAnnotation *)obj);
        default: return COWL_OK;
    }
}

cowl_ret cowl_str_buf_append_iri(CowlStrBuf *buf, CowlIRI *iri) {
    cowl_str_buf_append_static(buf, "<");
    cowl_str_buf_append_iri_no_brackets(buf, iri);
    cowl_str_buf_append_static(buf, ">");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_iri_no_brackets(CowlStrBuf *buf, CowlIRI *iri) {
    cowl_str_buf_append_string(buf, iri->ns);
    cowl_str_buf_append_string(buf, iri->rem);
    return buf->ret;
}

cowl_ret cowl_str_buf_append_ontology_id(CowlStrBuf *buf, CowlOntologyID *id) {
    if (id->ontology_iri) cowl_str_buf_append_iri(buf, id->ontology_iri);

    if (id->version_iri) {
        if (id->ontology_iri) cowl_str_buf_append_static(buf, " ");
        cowl_str_buf_append_iri(buf, id->version_iri);
    }

    return buf->ret;
}

cowl_ret cowl_str_buf_append_literal(CowlStrBuf *buf, CowlLiteral *literal) {
    cowl_str_buf_append_static(buf, "\"");
    cowl_str_buf_append_string(buf, literal->value);
    cowl_str_buf_append_static(buf, "\"");

    if (cowl_string_get_length(literal->lang)) {
        cowl_str_buf_append_static(buf, "@");
        cowl_str_buf_append_string(buf, literal->lang);
    }

    cowl_str_buf_append_static(buf, "^^");
    cowl_str_buf_append_iri_no_brackets(buf, cowl_datatype_get_iri(literal->dt));

    return buf->ret;
}

cowl_ret cowl_str_buf_append_facet_restr(CowlStrBuf *buf, CowlFacetRestr *restr) {
    CowlIRI *iri = cowl_facet_get_iri(restr->facet);
    cowl_str_buf_append_iri(buf, iri);
    cowl_iri_release(iri);

    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_literal(buf, restr->value);

    return buf->ret;
}

cowl_ret cowl_str_buf_append_node_id(CowlStrBuf *buf, CowlNodeID id) {
    cowl_str_buf_append_static(buf, "_:id");
    cowl_str_buf_append_uint(buf, id);
    return buf->ret;
}

cowl_ret cowl_str_buf_append_annotation(CowlStrBuf *buf, CowlAnnotation *annotation) {
    cowl_str_buf_append_static(buf, "Annotation");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, annotation->annot);
    cowl_str_buf_append_annot_prop(buf, annotation->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_annot_value(buf, annotation->value);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_annot_value(CowlStrBuf *buf, CowlAnnotValue *value) {
    switch (cowl_annot_value_get_type(value)) {
        case COWL_AVT_ANON_IND: return cowl_str_buf_append_anon_ind(buf, (CowlAnonInd *)value);
        case COWL_AVT_IRI: return cowl_str_buf_append_iri(buf, (CowlIRI *)value);
        case COWL_AVT_LITERAL: return cowl_str_buf_append_literal(buf, (CowlLiteral *)value);
        default: return COWL_ERR;
    }
}

cowl_ret cowl_str_buf_append_uint(CowlStrBuf *buf, cowl_uint uint) {
    if (uvec_expand(CowlChar, &buf->storage, (uvec_uint)(COWL_UINT_MAX_DIGITS + 1)) != UVEC_OK) {
        buf->ret = COWL_ERR_MEM;
    } else {
        size_t len = cowl_str_from_uint(uint, buf->storage.storage + buf->storage.count);
        buf->storage.count += (uvec_uint)len;
    }
    return buf->ret;;
}

// Entities and Primitives

cowl_ret cowl_str_buf_append_entity(CowlStrBuf *buf, CowlEntity *entity) {
    switch (cowl_entity_get_type(entity)) {
        case COWL_ET_CLASS: return cowl_str_buf_append_class(buf, (CowlClass *)entity);
        case COWL_ET_DATATYPE: return cowl_str_buf_append_datatype(buf, (CowlDatatype *)entity);
        case COWL_ET_OBJ_PROP: return cowl_str_buf_append_obj_prop(buf, (CowlObjProp *)entity);
        case COWL_ET_DATA_PROP: return cowl_str_buf_append_data_prop(buf, (CowlDataProp *)entity);
        case COWL_ET_ANNOT_PROP: return cowl_str_buf_append_annot_prop(buf, (CowlAnnotProp *)entity);
        case COWL_ET_NAMED_IND: return cowl_str_buf_append_named_ind(buf, (CowlNamedInd *)entity);
        default: return COWL_ERR;
    }
}

cowl_ret cowl_str_buf_append_primitive(CowlStrBuf *buf, CowlPrimitive *primitive) {
    switch (cowl_primitive_get_type(primitive)) {
        case COWL_PT_CLASS: return cowl_str_buf_append_class(buf, (CowlClass *)primitive);
        case COWL_PT_DATATYPE: return cowl_str_buf_append_datatype(buf, (CowlDatatype *)primitive);
        case COWL_PT_OBJ_PROP: return cowl_str_buf_append_obj_prop(buf, (CowlObjProp *)primitive);
        case COWL_PT_DATA_PROP: return cowl_str_buf_append_data_prop(buf, (CowlDataProp *)primitive);
        case COWL_PT_ANNOT_PROP: return cowl_str_buf_append_annot_prop(buf, (CowlAnnotProp *)primitive);
        case COWL_PT_NAMED_IND: return cowl_str_buf_append_named_ind(buf, (CowlNamedInd *)primitive);
        case COWL_PT_ANON_IND: return cowl_str_buf_append_anon_ind(buf, (CowlAnonInd *)primitive);
        default: return COWL_ERR;
    }
}

cowl_ret cowl_str_buf_append_class(CowlStrBuf *buf, CowlClass *cls) {
    cowl_str_buf_append_static(buf, "Class");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, cls->iri);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_datatype(CowlStrBuf *buf, CowlDatatype *dt) {
    cowl_str_buf_append_static(buf, "Datatype");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, dt->iri);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_prop(CowlStrBuf *buf, CowlObjProp *prop) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, prop->iri);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_data_prop(CowlStrBuf *buf, CowlDataProp *prop) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, prop->iri);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_annot_prop(CowlStrBuf *buf, CowlAnnotProp *prop) {
    cowl_str_buf_append_static(buf, "Annotation");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, prop->iri);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_named_ind(CowlStrBuf *buf, CowlNamedInd *ind) {
    cowl_str_buf_append_static(buf, "Named");
    cowl_str_buf_append_static(buf, "Individual");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, ind->iri);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_anon_ind(CowlStrBuf *buf, CowlAnonInd *ind) {
    cowl_str_buf_append_static(buf, "Anonymous");
    cowl_str_buf_append_static(buf, "Individual");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_node_id(buf, ind->id);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_individual(CowlStrBuf *buf, CowlIndividual *ind) {
    if (cowl_individual_is_named(ind)) {
        return cowl_str_buf_append_named_ind(buf, (CowlNamedInd *)ind);
    } else {
        return cowl_str_buf_append_anon_ind(buf, (CowlAnonInd *)ind);
    }
}

// Object property expressions

cowl_ret cowl_str_buf_append_obj_prop_exp(CowlStrBuf *buf, CowlObjPropExp *exp) {
    if (cowl_obj_prop_exp_is_inverse(exp)) {
        return cowl_str_buf_append_inv_obj_prop(buf, (CowlInvObjProp *)exp);
    } else {
        return cowl_str_buf_append_obj_prop(buf, (CowlObjProp *)exp);
    }
}

cowl_ret cowl_str_buf_append_inv_obj_prop(CowlStrBuf *buf, CowlInvObjProp *prop) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Inverse");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_obj_prop(buf, prop->prop);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

// Data property expressions

cowl_ret cowl_str_buf_append_data_prop_exp(CowlStrBuf *buf, CowlDataPropExp *exp) {
    return cowl_str_buf_append_data_prop(buf, (CowlDataProp *)exp);
}

// Class expressions

cowl_ret cowl_str_buf_append_cls_exp(CowlStrBuf *buf, CowlClsExp *exp) {
    switch (cowl_cls_exp_get_type(exp)) {

        case COWL_CET_CLASS:
            return cowl_str_buf_append_class(buf, (CowlClass *)exp);

        case COWL_CET_OBJ_SOME:
        case COWL_CET_OBJ_ALL:
            return cowl_str_buf_append_obj_quant(buf, (CowlObjQuant *)exp);

        case COWL_CET_OBJ_MIN_CARD:
        case COWL_CET_OBJ_MAX_CARD:
        case COWL_CET_OBJ_EXACT_CARD:
            return cowl_str_buf_append_obj_card(buf, (CowlObjCard *)exp);

        case COWL_CET_OBJ_HAS_VALUE:
            return cowl_str_buf_append_obj_has_value(buf, (CowlObjHasValue *)exp);

        case COWL_CET_OBJ_HAS_SELF:
            return cowl_str_buf_append_obj_has_self(buf, (CowlObjHasSelf *)exp);

        case COWL_CET_DATA_SOME:
        case COWL_CET_DATA_ALL:
            return cowl_str_buf_append_data_quant(buf, (CowlDataQuant *)exp);

        case COWL_CET_DATA_MIN_CARD:
        case COWL_CET_DATA_MAX_CARD:
        case COWL_CET_DATA_EXACT_CARD:
            return cowl_str_buf_append_data_card(buf, (CowlDataCard *)exp);

        case COWL_CET_DATA_HAS_VALUE:
            return cowl_str_buf_append_data_has_value(buf, (CowlDataHasValue *)exp);

        case COWL_CET_OBJ_INTERSECT:
        case COWL_CET_OBJ_UNION:
            return cowl_str_buf_append_nary_bool(buf, (CowlNAryBool *)exp);

        case COWL_CET_OBJ_COMPL:
            return cowl_str_buf_append_obj_compl(buf, (CowlObjCompl *)exp);

        case COWL_CET_OBJ_ONE_OF:
            return cowl_str_buf_append_obj_one_of(buf, (CowlObjOneOf *)exp);

        default:
            return COWL_ERR;
    }
}

cowl_ret cowl_str_buf_append_obj_quant(CowlStrBuf *buf, CowlObjQuant *restr) {
    cowl_str_buf_append_static(buf, "Object");

    if (cowl_obj_quant_get_type(restr) == COWL_QT_SOME) {
        cowl_str_buf_append_static(buf, "Some");
    } else {
        cowl_str_buf_append_static(buf, "All");
    }

    cowl_str_buf_append_static(buf, "ValuesFrom");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_obj_prop_exp(buf, restr->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp(buf, restr->filler);
    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_card(CowlStrBuf *buf, CowlObjCard *restr) {
    cowl_str_buf_append_static(buf, "Object");

    switch (cowl_obj_card_get_type(restr)) {
        case COWL_CT_MIN: cowl_str_buf_append_static(buf, "Min"); break;
        case COWL_CT_MAX: cowl_str_buf_append_static(buf, "Max"); break;
        default: cowl_str_buf_append_static(buf, "Exact"); break;
    }

    cowl_str_buf_append_static(buf, "Cardinality");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_uint(buf, restr->cardinality);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_obj_prop_exp(buf, restr->prop);

    if (restr->filler) {
        cowl_str_buf_append_static(buf, " ");
        cowl_str_buf_append_cls_exp(buf, restr->filler);
    }

    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_has_value(CowlStrBuf *buf, CowlObjHasValue *restr) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Has");
    cowl_str_buf_append_static(buf, "Value");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_obj_prop_exp(buf, restr->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_individual(buf, restr->ind);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_has_self(CowlStrBuf *buf, CowlObjHasSelf *restr) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Has");
    cowl_str_buf_append_static(buf, "Self");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_obj_prop_exp(buf, restr->prop);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_data_quant(CowlStrBuf *buf, CowlDataQuant *restr) {
    cowl_str_buf_append_static(buf, "Data");

    if (cowl_data_quant_get_type(restr) == COWL_QT_SOME) {
        cowl_str_buf_append_static(buf, "Some");
    } else {
        cowl_str_buf_append_static(buf, "All");
    }

    cowl_str_buf_append_static(buf, "ValuesFrom");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_data_prop_exp(buf, restr->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_data_range(buf, restr->range);
    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_data_card(CowlStrBuf *buf, CowlDataCard *restr) {
    cowl_str_buf_append_static(buf, "Data");

    switch (cowl_data_card_get_type(restr)) {
        case COWL_CT_MIN: cowl_str_buf_append_static(buf, "Min"); break;
        case COWL_CT_MAX: cowl_str_buf_append_static(buf, "Max"); break;
        default: cowl_str_buf_append_static(buf, "Exact"); break;
    }

    cowl_str_buf_append_static(buf, "Cardinality");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_uint(buf, restr->cardinality);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_data_prop_exp(buf, restr->prop);

    if (restr->range) {
        cowl_str_buf_append_static(buf, " ");
        cowl_str_buf_append_data_range(buf, restr->range);
    }

    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_data_has_value(CowlStrBuf *buf, CowlDataHasValue *restr) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Has");
    cowl_str_buf_append_static(buf, "Value");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_data_prop_exp(buf, restr->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_literal(buf, restr->value);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_nary_bool(CowlStrBuf *buf, CowlNAryBool *exp) {
    cowl_str_buf_append_static(buf, "Object");

    if (cowl_nary_bool_get_type(exp) == COWL_NT_INTERSECT) {
        cowl_str_buf_append_static(buf, "Intersection");
    } else {
        cowl_str_buf_append_static(buf, "Union");
    }

    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_cls_exp_set(buf, exp->operands);
    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_compl(CowlStrBuf *buf, CowlObjCompl *exp) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Complement");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_cls_exp(buf, exp->operand);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_one_of(CowlStrBuf *buf, CowlObjOneOf *restr) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "One");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_individual_set(buf, restr->inds);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

// Data ranges

cowl_ret cowl_str_buf_append_data_range(CowlStrBuf *buf, CowlDataRange *range) {
    switch (cowl_data_range_get_type(range)) {

        case COWL_DRT_DATATYPE:
            return cowl_str_buf_append_datatype(buf, (CowlDatatype *)range);

        case COWL_DRT_DATATYPE_RESTR:
            return cowl_str_buf_append_datatype_restr(buf, (CowlDatatypeRestr *)range);

        case COWL_DRT_DATA_INTERSECT:
        case COWL_DRT_DATA_UNION:
            return cowl_str_buf_append_nary_data(buf, (CowlNAryData *)range);

        case COWL_DRT_DATA_COMPL:
            return cowl_str_buf_append_data_compl(buf, (CowlDataCompl *)range);

        case COWL_DRT_DATA_ONE_OF:
            return cowl_str_buf_append_data_one_of(buf, (CowlDataOneOf *)range);

        default:
            return COWL_ERR;
    }
}

cowl_ret cowl_str_buf_append_datatype_restr(CowlStrBuf *buf, CowlDatatypeRestr *restr) {
    cowl_str_buf_append_static(buf, "Datatype");
    cowl_str_buf_append_static(buf, "Restriction");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, restr->datatype->iri);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_facet_restr_set(buf, restr->restrictions);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_nary_data(CowlStrBuf *buf, CowlNAryData *range) {
    cowl_str_buf_append_static(buf, "Data");

    if (cowl_nary_data_get_type(range) == COWL_NT_INTERSECT) {
        cowl_str_buf_append_static(buf, "Intersection");
    } else {
        cowl_str_buf_append_static(buf, "Union");
    }

    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_data_range_set(buf, range->operands);
    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_data_compl(CowlStrBuf *buf, CowlDataCompl *range) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Complement");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_data_range(buf, range->operand);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_data_one_of(CowlStrBuf *buf, CowlDataOneOf *restr) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "One");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_literal_set(buf, restr->values);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

// Axioms

cowl_ret cowl_str_buf_append_axiom(CowlStrBuf *buf, CowlAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_get_type(axiom);

    switch (type) {

        case COWL_AT_DECL:
            return cowl_str_buf_append_decl_axiom(buf, (CowlDeclAxiom *)axiom);

        case COWL_AT_DATATYPE_DEF:
            return cowl_str_buf_append_datatype_def_axiom(buf, (CowlDatatypeDefAxiom *)axiom);

        case COWL_AT_SUB_CLASS:
            return cowl_str_buf_append_sub_cls_axiom(buf, (CowlSubClsAxiom *)axiom);

        case COWL_AT_EQUIV_CLASSES:
        case COWL_AT_DISJ_CLASSES:
            return cowl_str_buf_append_nary_cls_axiom(buf, (CowlNAryClsAxiom *)axiom);

        case COWL_AT_DISJ_UNION:
            return cowl_str_buf_append_disj_union_axiom(buf, (CowlDisjUnionAxiom *)axiom);

        case COWL_AT_CLASS_ASSERT:
            return cowl_str_buf_append_cls_assert(buf, (CowlClsAssertAxiom *)axiom);

        case COWL_AT_SAME_IND:
        case COWL_AT_DIFF_IND:
            return cowl_str_buf_append_nary_ind_axiom(buf, (CowlNAryIndAxiom *)axiom);

        case COWL_AT_OBJ_PROP_ASSERT:
        case COWL_AT_NEG_OBJ_PROP_ASSERT:
            return cowl_str_buf_append_obj_prop_assert(buf, (CowlObjPropAssertAxiom *)axiom);

        case COWL_AT_DATA_PROP_ASSERT:
        case COWL_AT_NEG_DATA_PROP_ASSERT:
            return cowl_str_buf_append_data_prop_assert(buf, (CowlDataPropAssertAxiom *)axiom);

        case COWL_AT_SUB_OBJ_PROP:
            return cowl_str_buf_append_sub_obj_prop_axiom(buf, (CowlSubObjPropAxiom *)axiom);

        case COWL_AT_SUB_OBJ_PROP_CHAIN:
            return cowl_str_buf_append_sub_obj_prop_chain_axiom(buf, (CowlSubObjPropChainAxiom *)axiom);

        case COWL_AT_INV_OBJ_PROP:
            return cowl_str_buf_append_inv_obj_prop_axiom(buf, (CowlInvObjPropAxiom *)axiom);

        case COWL_AT_EQUIV_OBJ_PROP:
        case COWL_AT_DISJ_OBJ_PROP:
            return cowl_str_buf_append_nary_obj_prop_axiom(buf, (CowlNAryObjPropAxiom *)axiom);

        case COWL_AT_FUNC_OBJ_PROP:
        case COWL_AT_INV_FUNC_OBJ_PROP:
        case COWL_AT_SYMM_OBJ_PROP:
        case COWL_AT_ASYMM_OBJ_PROP:
        case COWL_AT_REFL_OBJ_PROP:
        case COWL_AT_IRREFL_OBJ_PROP:
        case COWL_AT_TRANS_OBJ_PROP:
            return cowl_str_buf_append_obj_prop_char(buf, (CowlObjPropCharAxiom *)axiom);

        case COWL_AT_OBJ_PROP_DOMAIN:
            return cowl_str_buf_append_obj_prop_domain(buf, (CowlObjPropDomainAxiom *)axiom);

        case COWL_AT_OBJ_PROP_RANGE:
            return cowl_str_buf_append_obj_prop_range(buf, (CowlObjPropRangeAxiom *)axiom);

        case COWL_AT_SUB_DATA_PROP:
            return cowl_str_buf_append_sub_data_prop_axiom(buf, (CowlSubDataPropAxiom *)axiom);

        case COWL_AT_EQUIV_DATA_PROP:
        case COWL_AT_DISJ_DATA_PROP:
            return cowl_str_buf_append_nary_data_prop_axiom(buf, (CowlNAryDataPropAxiom *)axiom);

        case COWL_AT_FUNC_DATA_PROP:
            return cowl_str_buf_append_func_data_prop_axiom(buf, (CowlFuncDataPropAxiom *)axiom);

        case COWL_AT_DATA_PROP_DOMAIN:
            return cowl_str_buf_append_data_prop_domain(buf, (CowlDataPropDomainAxiom *)axiom);

        case COWL_AT_DATA_PROP_RANGE:
            return cowl_str_buf_append_data_prop_range(buf, (CowlDataPropRangeAxiom *)axiom);

        case COWL_AT_HAS_KEY:
            return cowl_str_buf_append_has_key_axiom(buf, (CowlHasKeyAxiom *)axiom);

        case COWL_AT_ANNOT_ASSERT:
            return cowl_str_buf_append_annot_assert(buf, (CowlAnnotAssertAxiom *)axiom);

        case COWL_AT_SUB_ANNOT_PROP:
            return cowl_str_buf_append_sub_annot_prop_axiom(buf, (CowlSubAnnotPropAxiom *)axiom);

        case COWL_AT_ANNOT_PROP_DOMAIN:
            return cowl_str_buf_append_annot_prop_domain_axiom(buf, (CowlAnnotPropDomainAxiom *)axiom);

        case COWL_AT_ANNOT_PROP_RANGE:
            return cowl_str_buf_append_annot_prop_range_axiom(buf, (CowlAnnotPropRangeAxiom *)axiom);

        default:
            return COWL_ERR;
    }
}

cowl_ret cowl_str_buf_append_decl_axiom(CowlStrBuf *buf, CowlDeclAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Declaration");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_entity(buf, axiom->entity);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_datatype_def_axiom(CowlStrBuf *buf, CowlDatatypeDefAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Datatype");
    cowl_str_buf_append_static(buf, "Definition");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_entity(buf, (CowlEntity *)axiom->datatype);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_data_range(buf, axiom->range);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_sub_cls_axiom(CowlStrBuf *buf, CowlSubClsAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Sub");
    cowl_str_buf_append_static(buf, "Class");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_cls_exp(buf, axiom->sub_class);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp(buf, axiom->super_class);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_nary_cls_axiom(CowlStrBuf *buf, CowlNAryClsAxiom *axiom) {
    if (cowl_nary_cls_axiom_get_type(axiom) == COWL_NAT_EQUIV) {
        cowl_str_buf_append_static(buf, "Equivalent");
    } else {
        cowl_str_buf_append_static(buf, "Disjoint");
    }

    cowl_str_buf_append_static(buf, "Class");
    cowl_str_buf_append_static(buf, "es");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_cls_exp_set(buf, axiom->classes);
    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_disj_union_axiom(CowlStrBuf *buf, CowlDisjUnionAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Disjoint");
    cowl_str_buf_append_static(buf, "Union");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_cls_exp(buf, (CowlClsExp *)axiom->cls);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp_set(buf, axiom->disjoints);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_cls_assert(CowlStrBuf *buf, CowlClsAssertAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Class");
    cowl_str_buf_append_static(buf, "Assertion");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_individual(buf, axiom->ind);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp(buf, axiom->cls_exp);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_nary_ind_axiom(CowlStrBuf *buf, CowlNAryIndAxiom *axiom) {
    if (cowl_nary_ind_axiom_get_type(axiom) == COWL_NAT_SAME) {
        cowl_str_buf_append_static(buf, "Same");
        cowl_str_buf_append_static(buf, "Individual");
    } else {
        cowl_str_buf_append_static(buf, "Different");
        cowl_str_buf_append_static(buf, "Individual");
        cowl_str_buf_append_static(buf, "s");
    }

    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_individual_set(buf, axiom->individuals);
    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_prop_assert(CowlStrBuf *buf, CowlObjPropAssertAxiom *axiom) {
    if (cowl_obj_prop_assert_axiom_is_negative(axiom)) {
        cowl_str_buf_append_static(buf, "Negative");
    }

    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Assertion");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_individual(buf, axiom->subject);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_obj_prop_exp(buf, axiom->prop_exp);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_individual(buf, axiom->object);
    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_data_prop_assert(CowlStrBuf *buf, CowlDataPropAssertAxiom *axiom) {
    if (cowl_data_prop_assert_axiom_is_negative(axiom)) {
        cowl_str_buf_append_static(buf, "Negative");
    }

    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Assertion");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_individual(buf, axiom->subject);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_data_prop_exp(buf, axiom->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_literal(buf, axiom->object);
    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_sub_obj_prop_axiom(CowlStrBuf *buf, CowlSubObjPropAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Sub");
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_obj_prop_exp(buf, axiom->sub_prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_obj_prop_exp(buf, axiom->super_prop);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_sub_obj_prop_chain_axiom(CowlStrBuf *buf, CowlSubObjPropChainAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Sub");
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Chain");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_obj_prop_exp_vec(buf, axiom->sub_props);
    cowl_str_buf_append_static(buf, ") ");
    cowl_str_buf_append_obj_prop_exp(buf, axiom->super_prop);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_inv_obj_prop_axiom(CowlStrBuf *buf, CowlInvObjPropAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Inverse");
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Properties");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_obj_prop_exp(buf, axiom->first);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_obj_prop_exp(buf, axiom->second);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_nary_obj_prop_axiom(CowlStrBuf *buf, CowlNAryObjPropAxiom *axiom) {
    if (cowl_nary_obj_prop_axiom_get_type(axiom) == COWL_NAT_EQUIV) {
        cowl_str_buf_append_static(buf, "Equivalent");
    } else {
        cowl_str_buf_append_static(buf, "Disjoint");
    }

    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Properties");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_obj_prop_exp_set(buf, axiom->props);
    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_prop_char(CowlStrBuf *buf, CowlObjPropCharAxiom *axiom) {
    CowlCharAxiomType const type = cowl_obj_prop_char_axiom_get_type(axiom);

    switch (type) {
        case COWL_CAT_FUNC:
            cowl_str_buf_append_static(buf, "Functional");
            break;

        case COWL_CAT_INV_FUNC:
            cowl_str_buf_append_static(buf, "Inverse");
            cowl_str_buf_append_static(buf, "Functional");
            break;

        case COWL_CAT_SYMM:
            cowl_str_buf_append_static(buf, "Symmetric");
            break;

        case COWL_CAT_ASYMM:
            cowl_str_buf_append_static(buf, "Asymmetric");
            break;

        case COWL_CAT_REFL:
            cowl_str_buf_append_static(buf, "Reflexive");
            break;

        case COWL_CAT_IRREFL:
            cowl_str_buf_append_static(buf, "Irreflexive");
            break;

        default:
            cowl_str_buf_append_static(buf, "Transitive");
            break;
    }

    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_obj_prop_exp(buf, axiom->prop_exp);
    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_prop_domain(CowlStrBuf *buf, CowlObjPropDomainAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Domain");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_obj_prop_exp(buf, axiom->prop_exp);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp(buf, axiom->domain);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_prop_range(CowlStrBuf *buf, CowlObjPropRangeAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Range");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_obj_prop_exp(buf, axiom->prop_exp);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp(buf, axiom->range);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_sub_data_prop_axiom(CowlStrBuf *buf, CowlSubDataPropAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Sub");
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_data_prop_exp(buf, axiom->sub_prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_data_prop_exp(buf, axiom->super_prop);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_nary_data_prop_axiom(CowlStrBuf *buf, CowlNAryDataPropAxiom *axiom) {
    if (cowl_nary_data_prop_axiom_get_type(axiom) == COWL_NAT_EQUIV) {
        cowl_str_buf_append_static(buf, "Equivalent");
    } else {
        cowl_str_buf_append_static(buf, "Disjoint");
    }

    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Properties");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_data_prop_exp_set(buf, axiom->props);
    cowl_str_buf_append_static(buf, ")");

    return buf->ret;
}

cowl_ret cowl_str_buf_append_func_data_prop_axiom(CowlStrBuf *buf, CowlFuncDataPropAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Functional");
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_data_prop_exp(buf, axiom->prop);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_data_prop_domain(CowlStrBuf *buf, CowlDataPropDomainAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Domain");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_data_prop_exp(buf, axiom->prop_exp);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp(buf, axiom->domain);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_data_prop_range(CowlStrBuf *buf, CowlDataPropRangeAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Range");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_data_prop_exp(buf, axiom->prop_exp);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_data_range(buf, axiom->range);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_has_key_axiom(CowlStrBuf *buf, CowlHasKeyAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Has");
    cowl_str_buf_append_static(buf, "Key");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_cls_exp(buf, axiom->cls_exp);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_obj_prop_exp_set(buf, axiom->obj_props);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_data_prop_exp_set(buf, axiom->data_props);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_annot_assert(CowlStrBuf *buf, CowlAnnotAssertAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Annotation");
    cowl_str_buf_append_static(buf, "Assertion");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_annot_value(buf, axiom->subject);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_annot_prop(buf, axiom->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_annot_value(buf, axiom->value);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_sub_annot_prop_axiom(CowlStrBuf *buf, CowlSubAnnotPropAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Sub");
    cowl_str_buf_append_static(buf, "Annotation");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_annot_prop(buf, axiom->sub_prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_annot_prop(buf, axiom->super_prop);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_annot_prop_domain_axiom(CowlStrBuf *buf, CowlAnnotPropDomainAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Annotation");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Domain");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_annot_prop(buf, axiom->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_iri(buf, axiom->domain);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

cowl_ret cowl_str_buf_append_annot_prop_range_axiom(CowlStrBuf *buf, CowlAnnotPropRangeAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Annotation");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Range");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_annot_prop(buf, axiom->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_iri(buf, axiom->range);
    cowl_str_buf_append_static(buf, ")");
    return buf->ret;
}

// Collections

cowl_ret cowl_str_buf_append_cls_exp_set(CowlStrBuf *buf, CowlClsExpSet *set) {
    cowl_uint current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlClsExpSet, set, exp, {
        cowl_str_buf_append_cls_exp(buf, exp);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });

    return buf->ret;
}

cowl_ret cowl_str_buf_append_data_prop_exp_set(CowlStrBuf *buf, CowlDataPropExpSet *set) {
    cowl_uint current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlDataPropExpSet, set, prop, {
        cowl_str_buf_append_data_prop_exp(buf, prop);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });

    return buf->ret;
}

cowl_ret cowl_str_buf_append_data_range_set(CowlStrBuf *buf, CowlDataRangeSet *set) {
    cowl_uint current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlDataRangeSet, set, range, {
        cowl_str_buf_append_data_range(buf, range);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });

    return buf->ret;
}

cowl_ret cowl_str_buf_append_facet_restr_set(CowlStrBuf *buf, CowlFacetRestrSet *set) {
    cowl_uint current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlFacetRestrSet, set, restr, {
        cowl_str_buf_append_facet_restr(buf, restr);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });

    return buf->ret;
}

cowl_ret cowl_str_buf_append_individual_set(CowlStrBuf *buf, CowlIndividualSet *set) {
    cowl_uint current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlIndividualSet, set, ind, {
        cowl_str_buf_append_individual(buf, ind);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });

    return buf->ret;
}

cowl_ret cowl_str_buf_append_literal_set(CowlStrBuf *buf, CowlLiteralSet *set) {
    cowl_uint current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlLiteralSet, set, literal, {
        cowl_str_buf_append_literal(buf, literal);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });

    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_prop_exp_set(CowlStrBuf *buf, CowlObjPropExpSet *set) {
    cowl_uint current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlObjPropExpSet, set, prop, {
        cowl_str_buf_append_obj_prop_exp(buf, prop);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });

    return buf->ret;
}

cowl_ret cowl_str_buf_append_annotation_vec(CowlStrBuf *buf, CowlAnnotationVec *vec) {
    cowl_uint last = uvec_count(vec);

    uvec_iterate(CowlAnnotationPtr, vec, annot, idx, {
        cowl_str_buf_append_annotation(buf, annot);
        if (idx < last) cowl_str_buf_append_static(buf, " ");
    });

    return buf->ret;
}

cowl_ret cowl_str_buf_append_obj_prop_exp_vec(CowlStrBuf *buf, CowlObjPropExpVec *vec) {
    cowl_uint last = uvec_count(vec);

    uvec_iterate(CowlObjPropExpPtr, vec, prop, idx, {
        cowl_str_buf_append_obj_prop_exp(buf, prop);
        if (idx < last) cowl_str_buf_append_static(buf, " ");
    });

    return buf->ret;
}

// Output

CowlRawString cowl_str_buf_to_raw_string(CowlStrBuf *buf) {
    cowl_uint length = uvec_count(&buf->storage);

    if (buf->ret || !length) {
        cowl_str_buf_deinit(buf);
        return COWL_RAW_STRING_NULL;
    }

    char *buffer = cowl_str_buf_deinit_get_storage(buf);
    char *cstring = cowl_realloc(buffer, length + 1);

    if (cstring) {
        cstring[length] = '\0';
    } else {
        cowl_free(buffer);
        length = 0;
    }

    return cowl_raw_string_init(cstring, length, false);
}

CowlString* cowl_str_buf_to_string(CowlStrBuf *buf) {
    return cowl_string_alloc(cowl_str_buf_to_raw_string(buf));
}
