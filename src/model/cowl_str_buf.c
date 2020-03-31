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

VECTOR_IMPL(CowlChar)

Vector(CowlChar)* cowl_str_buf_alloc(void) {
    return vector_alloc(CowlChar);
}

static char* cowl_str_buf_free(Vector(CowlChar) *buf) {
    char *cstring = buf->storage;
    buf->storage = NULL;
    buf->allocated = buf->count = 0;
    vector_free(CowlChar, buf);
    return cstring;
}

static cowl_uint_t cowl_cstring_length_of_formatted(char const *format, va_list argptr) {
    va_list args;
    va_copy(args, argptr);
    int res = vsnprintf(NULL, 0, format, args);
    va_end(args);
    return (cowl_uint_t)res;
}

void cowl_str_buf_append_cstring(CowlStrBuf *buf, char const *string,
                                 cowl_uint_t length) {
    vector_append_array(CowlChar, buf, string, length);
}

void cowl_str_buf_append_raw_string(CowlStrBuf *buf, CowlRawString string) {
    cowl_str_buf_append_cstring(buf, string.cstring, string.length);
}

void cowl_str_buf_append_string(CowlStrBuf *buf, CowlString *string) {
    cowl_str_buf_append_raw_string(buf, string->raw_string);
}

void cowl_str_buf_append_format(CowlStrBuf *buf, char const *format, ...) {
    va_list args;
    va_start(args, format);
    cowl_str_buf_append_format_list(buf, format, args);
    va_end(args);
}

void cowl_str_buf_append_format_list(CowlStrBuf *buf, char const *format, va_list args) {
    cowl_uint_t length = cowl_cstring_length_of_formatted(format, args);
    size_t size = length + 1;
    vector_expand(CowlChar, buf, size);
    vsnprintf(buf->storage + buf->count, size, format, args);
    buf->count += length;
}

// Misc

void cowl_str_buf_append_iri(CowlStrBuf *buf, CowlIRI *iri) {
    cowl_str_buf_append_static(buf, "<");
    cowl_str_buf_append_iri_no_brackets(buf, iri);
    cowl_str_buf_append_static(buf, ">");
}

void cowl_str_buf_append_iri_no_brackets(CowlStrBuf *buf, CowlIRI *iri) {
    cowl_str_buf_append_string(buf, iri->ns);
    cowl_str_buf_append_string(buf, iri->rem);
}

void cowl_str_buf_append_ontology_id(CowlStrBuf *buf, CowlOntologyID *id) {
    if (id->onto_iri) {
        cowl_str_buf_append_iri(buf, id->onto_iri);
    }

    if (id->version_iri) {
        cowl_str_buf_append_static(buf, " ");
        cowl_str_buf_append_iri(buf, id->version_iri);
    }
}

void cowl_str_buf_append_literal(CowlStrBuf *buf, CowlLiteral *literal) {
    cowl_str_buf_append_static(buf, "\"");
    cowl_str_buf_append_string(buf, literal->value);
    cowl_str_buf_append_static(buf, "\"");

    if (cowl_string_get_length(literal->lang)) {
        cowl_str_buf_append_static(buf, "@");
        cowl_str_buf_append_string(buf, literal->lang);
    }

    cowl_str_buf_append_static(buf, "^^");
    cowl_str_buf_append_iri_no_brackets(buf, cowl_datatype_get_iri(literal->dt));
}

void cowl_str_buf_append_facet_restr(CowlStrBuf *buf, CowlFacetRestr *restr) {
    CowlIRI *iri = cowl_facet_get_iri(restr->facet);
    cowl_str_buf_append_iri(buf,iri);
    cowl_iri_release(iri);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_literal(buf, restr->value);
}

void cowl_str_buf_append_node_id(CowlStrBuf *buf, CowlNodeID id) {
    cowl_str_buf_append_format(buf, "_:id%" COWL_UINT_FMT, id);
}

void cowl_str_buf_append_annotation(CowlStrBuf *buf, CowlAnnotation *annotation) {
    cowl_str_buf_append_static(buf, "Annotation");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, annotation->annot);
    cowl_str_buf_append_annot_prop(buf, annotation->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_annot_value(buf, annotation->value);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_annot_value(CowlStrBuf *buf, CowlAnnotValue value) {
    switch (value.type) {
        case COWL_AVT_ANON_IND: cowl_str_buf_append_anon_ind(buf, value.anon_ind); break;
        case COWL_AVT_IRI: cowl_str_buf_append_iri(buf, value.iri); break;
        case COWL_AVT_LITERAL: cowl_str_buf_append_literal(buf, value.literal); break;
        default: break;
    }
}

// Entities

void cowl_str_buf_append_entity(CowlStrBuf *buf, CowlEntity entity) {
    switch (entity.type) {
        case COWL_ET_CLASS: cowl_str_buf_append_class(buf, entity.owl_class); break;
        case COWL_ET_DATATYPE: cowl_str_buf_append_datatype(buf, entity.datatype); break;
        case COWL_ET_OBJ_PROP: cowl_str_buf_append_obj_prop(buf, entity.obj_prop); break;
        case COWL_ET_DATA_PROP: cowl_str_buf_append_data_prop(buf, entity.data_prop); break;
        case COWL_ET_ANNOT_PROP: cowl_str_buf_append_annot_prop(buf, entity.annot_prop); break;
        case COWL_ET_NAMED_IND: cowl_str_buf_append_named_ind(buf, entity.named_ind); break;
        default: break;
    }
}

void cowl_str_buf_append_class(CowlStrBuf *buf, CowlClass *cls) {
    cowl_str_buf_append_static(buf, "Class");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, cls->iri);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_datatype(CowlStrBuf *buf, CowlDatatype *dt) {
    cowl_str_buf_append_static(buf, "Datatype");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, dt->iri);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_obj_prop(CowlStrBuf *buf, CowlObjProp *prop) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, prop->iri);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_data_prop(CowlStrBuf *buf, CowlDataProp *prop) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, prop->iri);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_annot_prop(CowlStrBuf *buf, CowlAnnotProp *prop) {
    cowl_str_buf_append_static(buf, "Annotation");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, prop->iri);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_named_ind(CowlStrBuf *buf, CowlNamedInd *ind) {
    cowl_str_buf_append_static(buf, "Named");
    cowl_str_buf_append_static(buf, "Individual");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, ind->iri);
    cowl_str_buf_append_static(buf, ")");
}

// Individuals

void cowl_str_buf_append_individual(CowlStrBuf *buf, CowlIndividual *ind) {
    if (ind->is_named) {
        cowl_str_buf_append_named_ind(buf, (CowlNamedInd *)ind);
    } else {
        cowl_str_buf_append_anon_ind(buf, (CowlAnonInd *)ind);
    }
}

void cowl_str_buf_append_anon_ind(CowlStrBuf *buf, CowlAnonInd *ind) {
    cowl_str_buf_append_static(buf, "Anonymous");
    cowl_str_buf_append_static(buf, "Individual");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_node_id(buf, ind->id);
    cowl_str_buf_append_static(buf, ")");
}

// Object property expressions

void cowl_str_buf_append_obj_prop_exp(CowlStrBuf *buf, CowlObjPropExp *exp) {
    if (exp->is_inverse) {
        cowl_str_buf_append_inv_obj_prop(buf, (CowlInvObjProp *)exp);
    } else {
        cowl_str_buf_append_obj_prop(buf, (CowlObjProp *)exp);
    }
}

void cowl_str_buf_append_inv_obj_prop(CowlStrBuf *buf, CowlInvObjProp *prop) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Inverse");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_obj_prop(buf, prop->prop);
    cowl_str_buf_append_static(buf, ")");
}

// Data property expressions

void cowl_str_buf_append_data_prop_exp(CowlStrBuf *buf, CowlDataPropExp *exp) {
    cowl_str_buf_append_data_prop(buf, (CowlDataProp *)exp);
}

// Class expressions

void cowl_str_buf_append_cls_exp(CowlStrBuf *buf, CowlClsExp *exp) {
    switch (exp->type) {

        case COWL_CET_CLASS:
            cowl_str_buf_append_class(buf, (CowlClass *)exp);
            break;

        case COWL_CET_OBJ_SOME:
        case COWL_CET_OBJ_ALL:
            cowl_str_buf_append_obj_quant(buf, (CowlObjQuant *)exp);
            break;

        case COWL_CET_OBJ_MIN_CARD:
        case COWL_CET_OBJ_MAX_CARD:
        case COWL_CET_OBJ_EXACT_CARD:
            cowl_str_buf_append_obj_card(buf, (CowlObjCard *)exp);
            break;

        case COWL_CET_OBJ_HAS_VALUE:
            cowl_str_buf_append_obj_has_value(buf, (CowlObjHasValue *)exp);
            break;

        case COWL_CET_OBJ_HAS_SELF:
            cowl_str_buf_append_obj_has_self(buf, (CowlObjHasSelf *)exp);
            break;

        case COWL_CET_DATA_SOME:
        case COWL_CET_DATA_ALL:
            cowl_str_buf_append_data_quant(buf, (CowlDataQuant *)exp);
            break;

        case COWL_CET_DATA_MIN_CARD:
        case COWL_CET_DATA_MAX_CARD:
        case COWL_CET_DATA_EXACT_CARD:
            cowl_str_buf_append_data_card(buf, (CowlDataCard *)exp);
            break;

        case COWL_CET_DATA_HAS_VALUE:
            cowl_str_buf_append_data_has_value(buf, (CowlDataHasValue *)exp);
            break;

        case COWL_CET_OBJ_INTERSECT:
        case COWL_CET_OBJ_UNION:
            cowl_str_buf_append_nary_bool(buf, (CowlNAryBool *)exp);
            break;

        case COWL_CET_OBJ_COMPL:
            cowl_str_buf_append_obj_compl(buf, (CowlObjCompl *)exp);
            break;

        case COWL_CET_OBJ_ONE_OF:
            cowl_str_buf_append_obj_one_of(buf, (CowlObjOneOf *)exp);
            break;

        default:
            break;
    }
}

void cowl_str_buf_append_obj_quant(CowlStrBuf *buf, CowlObjQuant *restr) {
    cowl_str_buf_append_static(buf, "Object");
    if (restr->super.type == COWL_CET_OBJ_SOME) {
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
}

void cowl_str_buf_append_obj_card(CowlStrBuf *buf, CowlObjCard *restr) {
    cowl_str_buf_append_static(buf, "Object");
    switch (restr->super.type) {
        case COWL_CET_OBJ_MIN_CARD:
            cowl_str_buf_append_static(buf, "Min"); break;
        case COWL_CET_OBJ_MAX_CARD:
            cowl_str_buf_append_static(buf, "Max"); break;
        default:
            cowl_str_buf_append_static(buf, "Exact"); break;
    }
    cowl_str_buf_append_static(buf, "Cardinality");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_format(buf, "%" COWL_UINT_FMT " ", restr->cardinality);
    cowl_str_buf_append_obj_prop_exp(buf, restr->prop);

    if (restr->filler) {
        cowl_str_buf_append_static(buf, " ");
        cowl_str_buf_append_cls_exp(buf, restr->filler);
    }

    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_obj_has_value(CowlStrBuf *buf, CowlObjHasValue *restr) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Has");
    cowl_str_buf_append_static(buf, "Value");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_obj_prop_exp(buf, restr->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_individual(buf, restr->ind);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_obj_has_self(CowlStrBuf *buf, CowlObjHasSelf *restr) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Has");
    cowl_str_buf_append_static(buf, "Self");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_obj_prop_exp(buf, restr->prop);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_data_quant(CowlStrBuf *buf, CowlDataQuant *restr) {
    cowl_str_buf_append_static(buf, "Data");
    if (restr->super.type == COWL_CET_DATA_SOME) {
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
}

void cowl_str_buf_append_data_card(CowlStrBuf *buf, CowlDataCard *restr) {
    cowl_str_buf_append_static(buf, "Data");

    switch (restr->super.type) {
        case COWL_CET_DATA_MIN_CARD:
            cowl_str_buf_append_static(buf, "Min"); break;
        case COWL_CET_DATA_MAX_CARD:
            cowl_str_buf_append_static(buf, "Max"); break;
        default:
            cowl_str_buf_append_static(buf, "Exact"); break;
    }

    cowl_str_buf_append_static(buf, "Cardinality");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_format(buf, "%" COWL_UINT_FMT " ", restr->cardinality);
    cowl_str_buf_append_data_prop_exp(buf, restr->prop);

    if (restr->range) {
        cowl_str_buf_append_static(buf, " ");
        cowl_str_buf_append_data_range(buf, restr->range);
    }

    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_data_has_value(CowlStrBuf *buf, CowlDataHasValue *restr) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Has");
    cowl_str_buf_append_static(buf, "Value");
    cowl_str_buf_append_static(buf, "(");

    cowl_str_buf_append_data_prop_exp(buf, restr->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_literal(buf, restr->value);

    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_nary_bool(CowlStrBuf *buf, CowlNAryBool *exp) {
    cowl_str_buf_append_static(buf, "Object");
    if (exp->super.type == COWL_CET_OBJ_INTERSECT) {
        cowl_str_buf_append_static(buf, "Intersection");
    } else {
        cowl_str_buf_append_static(buf, "Union");
    }
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_cls_exp_set(buf, exp->operands);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_obj_compl(CowlStrBuf *buf, CowlObjCompl *exp) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Complement");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_cls_exp(buf, exp->operand);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_obj_one_of(CowlStrBuf *buf, CowlObjOneOf *restr) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "One");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_individual_set(buf, restr->inds);
    cowl_str_buf_append_static(buf, ")");
}

// Data ranges

void cowl_str_buf_append_data_range(CowlStrBuf *buf, CowlDataRange *range) {
    switch (range->type) {

        case COWL_DRT_DATATYPE:
            cowl_str_buf_append_datatype(buf, (CowlDatatype *)range);
            break;

        case COWL_DRT_DATATYPE_RESTR:
            cowl_str_buf_append_datatype_restr(buf, (CowlDatatypeRestr *)range);
            break;

        case COWL_DRT_DATA_INTERSECT:
        case COWL_DRT_DATA_UNION:
            cowl_str_buf_append_nary_data(buf, (CowlNAryData *)range);
            break;

        case COWL_DRT_DATA_COMPL:
            cowl_str_buf_append_data_compl(buf, (CowlDataCompl *)range);
            break;

        case COWL_DRT_DATA_ONE_OF:
            cowl_str_buf_append_data_one_of(buf, (CowlDataOneOf *)range);
            break;

        default:
            break;
    }
}

void cowl_str_buf_append_datatype_restr(CowlStrBuf *buf, CowlDatatypeRestr *restr) {
    cowl_str_buf_append_static(buf, "Datatype");
    cowl_str_buf_append_static(buf, "Restriction");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_iri(buf, restr->datatype->iri);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_facet_restr_set(buf, restr->restrictions);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_nary_data(CowlStrBuf *buf, CowlNAryData *range) {
    cowl_str_buf_append_static(buf, "Data");

    if (range->super.type == COWL_DRT_DATA_INTERSECT) {
        cowl_str_buf_append_static(buf, "Intersection");
    } else {
        cowl_str_buf_append_static(buf, "Union");
    }
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_data_range_set(buf, range->operands);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_data_compl(CowlStrBuf *buf, CowlDataCompl *range) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Complement");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_data_range(buf, range->operand);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_data_one_of(CowlStrBuf *buf, CowlDataOneOf *restr) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "One");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_literal_set(buf, restr->values);
    cowl_str_buf_append_static(buf, ")");
}

// Axioms

void cowl_str_buf_append_axiom(CowlStrBuf *buf, CowlAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_get_type(axiom);

    switch (type) {

        case COWL_AT_DECL:
            cowl_str_buf_append_decl_axiom(buf, (CowlDeclAxiom *)axiom);
            break;

        case COWL_AT_DATATYPE_DEF:
            cowl_str_buf_append_datatype_def_axiom(buf, (CowlDatatypeDefAxiom *)axiom);
            break;

        case COWL_AT_SUB_CLASS:
            cowl_str_buf_append_sub_cls_axiom(buf, (CowlSubClsAxiom *)axiom);
            break;

        case COWL_AT_EQUIV_CLASSES:
        case COWL_AT_DISJ_CLASSES:
            cowl_str_buf_append_nary_cls_axiom(buf, (CowlNAryClsAxiom *)axiom);
            break;

        case COWL_AT_DISJ_UNION:
            cowl_str_buf_append_disj_union_axiom(buf, (CowlDisjUnionAxiom *)axiom);
            break;

        case COWL_AT_CLASS_ASSERT:
            cowl_str_buf_append_cls_assert(buf, (CowlClsAssertAxiom *)axiom);
            break;

        case COWL_AT_SAME_IND:
        case COWL_AT_DIFF_IND:
            cowl_str_buf_append_nary_ind_axiom(buf, (CowlNAryIndAxiom *)axiom);
            break;

        case COWL_AT_OBJ_PROP_ASSERT:
        case COWL_AT_NEG_OBJ_PROP_ASSERT:
            cowl_str_buf_append_obj_prop_assert(buf, (CowlObjPropAssertAxiom *)axiom);
            break;

        case COWL_AT_DATA_PROP_ASSERT:
        case COWL_AT_NEG_DATA_PROP_ASSERT:
            cowl_str_buf_append_data_prop_assert(buf, (CowlDataPropAssertAxiom *)axiom);
            break;

        case COWL_AT_SUB_OBJ_PROP:
            cowl_str_buf_append_sub_obj_prop_axiom(buf, (CowlSubObjPropAxiom *)axiom);
            break;

        case COWL_AT_SUB_OBJ_PROP_CHAIN:
            cowl_str_buf_append_sub_obj_prop_chain_axiom(buf, (CowlSubObjPropChainAxiom *)axiom);
            break;

        case COWL_AT_INV_OBJ_PROP:
            cowl_str_buf_append_inv_obj_prop_axiom(buf, (CowlInvObjPropAxiom *)axiom);
            break;

        case COWL_AT_EQUIV_OBJ_PROP:
        case COWL_AT_DISJ_OBJ_PROP:
            cowl_str_buf_append_nary_obj_prop_axiom(buf, (CowlNAryObjPropAxiom *)axiom);
            break;

        case COWL_AT_FUNC_OBJ_PROP:
        case COWL_AT_INV_FUNC_OBJ_PROP:
        case COWL_AT_SYMM_OBJ_PROP:
        case COWL_AT_ASYMM_OBJ_PROP:
        case COWL_AT_REFL_OBJ_PROP:
        case COWL_AT_IRREFL_OBJ_PROP:
        case COWL_AT_TRANS_OBJ_PROP:
            cowl_str_buf_append_obj_prop_char(buf, (CowlObjPropCharAxiom *)axiom);
            break;

        case COWL_AT_OBJ_PROP_DOMAIN:
            cowl_str_buf_append_obj_prop_domain(buf, (CowlObjPropDomainAxiom *)axiom);
            break;

        case COWL_AT_OBJ_PROP_RANGE:
            cowl_str_buf_append_obj_prop_range(buf, (CowlObjPropRangeAxiom *)axiom);
            break;

        case COWL_AT_SUB_DATA_PROP:
            cowl_str_buf_append_sub_data_prop_axiom(buf, (CowlSubDataPropAxiom *)axiom);
            break;

        case COWL_AT_EQUIV_DATA_PROP:
        case COWL_AT_DISJ_DATA_PROP:
            cowl_str_buf_append_nary_data_prop_axiom(buf, (CowlNAryDataPropAxiom *)axiom);
            break;

        case COWL_AT_FUNC_DATA_PROP:
            cowl_str_buf_append_func_data_prop_axiom(buf, (CowlFuncDataPropAxiom *)axiom);
            break;

        case COWL_AT_DATA_PROP_DOMAIN:
            cowl_str_buf_append_data_prop_domain(buf, (CowlDataPropDomainAxiom *)axiom);
            break;

        case COWL_AT_DATA_PROP_RANGE:
            cowl_str_buf_append_data_prop_range(buf, (CowlDataPropRangeAxiom *)axiom);
            break;

        case COWL_AT_HAS_KEY:
            cowl_str_buf_append_has_key_axiom(buf, (CowlHasKeyAxiom *)axiom);
            break;

        case COWL_AT_ANNOT_ASSERT:
            cowl_str_buf_append_annot_assert(buf, (CowlAnnotAssertAxiom *)axiom);
            break;

        case COWL_AT_SUB_ANNOT_PROP:
            cowl_str_buf_append_sub_annot_prop_axiom(buf, (CowlSubAnnotPropAxiom *)axiom);
            break;

        case COWL_AT_ANNOT_PROP_DOMAIN:
            cowl_str_buf_append_annot_prop_domain_axiom(buf, (CowlAnnotPropDomainAxiom *)axiom);
            break;

        case COWL_AT_ANNOT_PROP_RANGE:
            cowl_str_buf_append_annot_prop_range_axiom(buf, (CowlAnnotPropRangeAxiom *)axiom);
            break;

        default:
            break;
    }
}

void cowl_str_buf_append_decl_axiom(CowlStrBuf *buf, CowlDeclAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Declaration");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_entity(buf, axiom->entity);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_datatype_def_axiom(CowlStrBuf *buf, CowlDatatypeDefAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Datatype");
    cowl_str_buf_append_static(buf, "Definition");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_entity(buf, cowl_entity_wrap_datatype(axiom->datatype));
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_data_range(buf, axiom->range);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_sub_cls_axiom(CowlStrBuf *buf, CowlSubClsAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Sub");
    cowl_str_buf_append_static(buf, "Class");
    cowl_str_buf_append_static(buf, "Of");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_cls_exp(buf, axiom->sub_class);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp(buf, axiom->super_class);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_nary_cls_axiom(CowlStrBuf *buf, CowlNAryClsAxiom *axiom) {
    if (cowl_axiom_flags_get_type(axiom->super.flags) == COWL_AT_EQUIV_CLASSES) {
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
}

void cowl_str_buf_append_disj_union_axiom(CowlStrBuf *buf, CowlDisjUnionAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Disjoint");
    cowl_str_buf_append_static(buf, "Union");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_cls_exp(buf, (CowlClsExp *)axiom->cls);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp_set(buf, axiom->disjoints);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_cls_assert(CowlStrBuf *buf, CowlClsAssertAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Class");
    cowl_str_buf_append_static(buf, "Assertion");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_individual(buf, axiom->ind);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp(buf, axiom->cls_exp);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_nary_ind_axiom(CowlStrBuf *buf, CowlNAryIndAxiom *axiom) {
    if (cowl_axiom_flags_get_type(axiom->super.flags) == COWL_AT_SAME_IND) {
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
}

void cowl_str_buf_append_obj_prop_assert(CowlStrBuf *buf, CowlObjPropAssertAxiom *axiom) {
    if (cowl_axiom_flags_get_type(axiom->super.flags) == COWL_AT_NEG_OBJ_PROP_ASSERT) {
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
}

void cowl_str_buf_append_data_prop_assert(CowlStrBuf *buf, CowlDataPropAssertAxiom *axiom) {
    if (cowl_axiom_flags_get_type(axiom->super.flags) == COWL_AT_NEG_DATA_PROP_ASSERT) {
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
}

void cowl_str_buf_append_sub_obj_prop_axiom(CowlStrBuf *buf, CowlSubObjPropAxiom *axiom) {
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
}

void cowl_str_buf_append_sub_obj_prop_chain_axiom(CowlStrBuf *buf,
                                                     CowlSubObjPropChainAxiom *axiom) {
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
}

void cowl_str_buf_append_inv_obj_prop_axiom(CowlStrBuf *buf, CowlInvObjPropAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Inverse");
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Properties");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_obj_prop_exp(buf, axiom->first);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_obj_prop_exp(buf, axiom->second);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_nary_obj_prop_axiom(CowlStrBuf *buf, CowlNAryObjPropAxiom *axiom) {
    if (cowl_axiom_flags_get_type(axiom->super.flags) == COWL_AT_EQUIV_CLASSES) {
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
}

void cowl_str_buf_append_obj_prop_char(CowlStrBuf *buf, CowlObjPropCharAxiom *axiom) {
    CowlAxiomType const type = cowl_axiom_flags_get_type(axiom->super.flags);
    switch (type) {

        case COWL_AT_FUNC_OBJ_PROP:
            cowl_str_buf_append_static(buf, "Functional");
            break;

        case COWL_AT_INV_FUNC_OBJ_PROP:
            cowl_str_buf_append_static(buf, "Inverse");
            cowl_str_buf_append_static(buf, "Functional");
            break;

        case COWL_AT_SYMM_OBJ_PROP:
            cowl_str_buf_append_static(buf, "Symmetric");
            break;

        case COWL_AT_ASYMM_OBJ_PROP:
            cowl_str_buf_append_static(buf, "Asymmetric");
            break;

        case COWL_AT_REFL_OBJ_PROP:
            cowl_str_buf_append_static(buf, "Reflexive");
            break;

        case COWL_AT_IRREFL_OBJ_PROP:
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
}

void cowl_str_buf_append_obj_prop_domain(CowlStrBuf *buf, CowlObjPropDomainAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Domain");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_obj_prop_exp(buf, axiom->prop_exp);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp(buf, axiom->domain);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_obj_prop_range(CowlStrBuf *buf, CowlObjPropRangeAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Object");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Range");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_obj_prop_exp(buf, axiom->prop_exp);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp(buf, axiom->range);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_sub_data_prop_axiom(CowlStrBuf *buf, CowlSubDataPropAxiom *axiom) {
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
}

void cowl_str_buf_append_nary_data_prop_axiom(CowlStrBuf *buf, CowlNAryDataPropAxiom *axiom) {
    if (cowl_axiom_flags_get_type(axiom->super.flags) == COWL_AT_EQUIV_DATA_PROP) {
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
}

void cowl_str_buf_append_func_data_prop_axiom(CowlStrBuf *buf, CowlFuncDataPropAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Functional");
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_data_prop_exp(buf, axiom->prop);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_data_prop_domain(CowlStrBuf *buf, CowlDataPropDomainAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Domain");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_data_prop_exp(buf, axiom->prop_exp);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_cls_exp(buf, axiom->domain);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_data_prop_range(CowlStrBuf *buf, CowlDataPropRangeAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Data");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Range");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_data_prop_exp(buf, axiom->prop_exp);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_data_range(buf, axiom->range);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_has_key_axiom(CowlStrBuf *buf, CowlHasKeyAxiom *axiom) {
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
}

void cowl_str_buf_append_annot_assert(CowlStrBuf *buf, CowlAnnotAssertAxiom *axiom) {
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
}

void cowl_str_buf_append_sub_annot_prop_axiom(CowlStrBuf *buf, CowlSubAnnotPropAxiom *axiom) {
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
}

void cowl_str_buf_append_annot_prop_domain_axiom(CowlStrBuf *buf,
                                                    CowlAnnotPropDomainAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Annotation");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Domain");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_annot_prop(buf, axiom->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_iri(buf, axiom->domain);
    cowl_str_buf_append_static(buf, ")");
}

void cowl_str_buf_append_annot_prop_range_axiom(CowlStrBuf *buf,
                                                   CowlAnnotPropRangeAxiom *axiom) {
    cowl_str_buf_append_static(buf, "Annotation");
    cowl_str_buf_append_static(buf, "Property");
    cowl_str_buf_append_static(buf, "Range");
    cowl_str_buf_append_static(buf, "(");
    cowl_str_buf_append_annotation_vec(buf, cowl_axiom_get_annot(axiom));
    cowl_str_buf_append_annot_prop(buf, axiom->prop);
    cowl_str_buf_append_static(buf, " ");
    cowl_str_buf_append_iri(buf, axiom->range);
    cowl_str_buf_append_static(buf, ")");
}

// Collections

void cowl_str_buf_append_cls_exp_set(CowlStrBuf *buf, CowlClsExpSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlClsExpSet, set, exp, {
        cowl_str_buf_append_cls_exp(buf, exp);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });
}

void cowl_str_buf_append_data_prop_exp_set(CowlStrBuf *buf, CowlDataPropExpSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlDataPropExpSet, set, prop, {
        cowl_str_buf_append_data_prop_exp(buf, prop);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });
}

void cowl_str_buf_append_data_range_set(CowlStrBuf *buf, CowlDataRangeSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlDataRangeSet, set, range, {
        cowl_str_buf_append_data_range(buf, range);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });
}

void cowl_str_buf_append_facet_restr_set(CowlStrBuf *buf, CowlFacetRestrSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlFacetRestrSet, set, restr, {
        cowl_str_buf_append_facet_restr(buf, restr);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });
}

void cowl_str_buf_append_individual_set(CowlStrBuf *buf, CowlIndividualSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlIndividualSet, set, ind, {
        cowl_str_buf_append_individual(buf, ind);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });
}

void cowl_str_buf_append_literal_set(CowlStrBuf *buf, CowlLiteralSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlLiteralSet, set, literal, {
        cowl_str_buf_append_literal(buf, literal);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });
}

void cowl_str_buf_append_obj_prop_exp_set(CowlStrBuf *buf, CowlObjPropExpSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlObjPropExpSet, set, prop, {
        cowl_str_buf_append_obj_prop_exp(buf, prop);
        if (current++ < last) cowl_str_buf_append_static(buf, " ");
    });
}

void cowl_str_buf_append_annotation_vec(CowlStrBuf *buf, CowlAnnotationVec *vec) {
    cowl_uint_t last = vector_count(vec);

    vector_iterate(CowlAnnotationPtr, vec, annot, idx, {
        cowl_str_buf_append_annotation(buf, annot);
        if (idx < last) cowl_str_buf_append_static(buf, " ");
    });
}

void cowl_str_buf_append_obj_prop_exp_vec(CowlStrBuf *buf, CowlObjPropExpVec *vec) {
    cowl_uint_t last = vector_count(vec);

    vector_iterate(CowlObjPropExpPtr, vec, prop, idx, {
        cowl_str_buf_append_obj_prop_exp(buf, prop);
        if (idx < last) cowl_str_buf_append_static(buf, " ");
    });
}

// Output

CowlRawString cowl_str_buf_to_raw_string(CowlStrBuf *buf) {
    cowl_uint_t length = vector_count(buf);
    if (!(buf && length)) return (CowlRawString) { .cstring = NULL, .length = 0 };

    char *cstring = cowl_realloc(cowl_str_buf_free(buf), length + 1);
    cstring[length] = '\0';

    return cowl_raw_string_init(cstring, length, false);
}

CowlString* cowl_str_buf_to_string(CowlStrBuf *buf) {
    return cowl_string_alloc(cowl_str_buf_to_raw_string(buf));
}
