/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STR_BUF_H
#define COWL_STR_BUF_H

#include "cowl_annot_value.h"
#include "cowl_entity.h"
#include "cowl_node_id.h"
#include "cowl_raw_string.h"
#include "cowl_std.h"
#include "cowl_types.h"

COWL_BEGIN_DECLS

typedef char CowlChar;
VECTOR_DECL(CowlChar)
typedef vector_struct(CowlChar) CowlStrBuf;

CowlStrBuf* cowl_str_buf_alloc(void);

// Strings

void cowl_str_buf_append_cstring(CowlStrBuf *buf, char const *string, cowl_uint_t length);
void cowl_str_buf_append_raw_string(CowlStrBuf *buf, CowlRawString string);
void cowl_str_buf_append_string(CowlStrBuf *buf, CowlString *string);
void cowl_str_buf_append_format(CowlStrBuf *buf, char const *format, ...);
void cowl_str_buf_append_format_list(CowlStrBuf *buf, char const *format, va_list args);

#define cowl_str_buf_append_static(BUF, STRING) \
    cowl_str_buf_append_cstring(BUF, STRING, sizeof(STRING) - 1)

// Misc

void cowl_str_buf_append_iri(CowlStrBuf *buf, CowlIRI *iri);
void cowl_str_buf_append_iri_no_brackets(CowlStrBuf *buf, CowlIRI *iri);
void cowl_str_buf_append_ontology_id(CowlStrBuf *buf, CowlOntologyID *id);
void cowl_str_buf_append_literal(CowlStrBuf *buf, CowlLiteral *literal);
void cowl_str_buf_append_facet_restr(CowlStrBuf *buf, CowlFacetRestr *restr);
void cowl_str_buf_append_node_id(CowlStrBuf *buf, CowlNodeID id);
void cowl_str_buf_append_annotation(CowlStrBuf *buf, CowlAnnotation *annotation);
void cowl_str_buf_append_annot_value(CowlStrBuf *buf, CowlAnnotValue value);

// Entities

void cowl_str_buf_append_entity(CowlStrBuf *buf, CowlEntity entity);
void cowl_str_buf_append_class(CowlStrBuf *buf, CowlClass *cls);
void cowl_str_buf_append_datatype(CowlStrBuf *buf, CowlDatatype *dt);
void cowl_str_buf_append_obj_prop(CowlStrBuf *buf, CowlObjProp *prop);
void cowl_str_buf_append_data_prop(CowlStrBuf *buf, CowlDataProp *prop);
void cowl_str_buf_append_annot_prop(CowlStrBuf *buf, CowlAnnotProp *prop);
void cowl_str_buf_append_named_ind(CowlStrBuf *buf, CowlNamedInd *ind);

// Individuals

void cowl_str_buf_append_individual(CowlStrBuf *buf, CowlIndividual *ind);
void cowl_str_buf_append_anon_ind(CowlStrBuf *buf, CowlAnonInd *ind);

// Object property expressions

void cowl_str_buf_append_obj_prop_exp(CowlStrBuf *buf, CowlObjPropExp *exp);
void cowl_str_buf_append_inv_obj_prop(CowlStrBuf *buf, CowlInvObjProp *prop);

// Data property expressions

void cowl_str_buf_append_data_prop_exp(CowlStrBuf *buf, CowlDataPropExp *exp);

// Class expressions

void cowl_str_buf_append_cls_exp(CowlStrBuf *buf, CowlClsExp *exp);
void cowl_str_buf_append_obj_quant(CowlStrBuf *buf, CowlObjQuant *restr);
void cowl_str_buf_append_obj_card(CowlStrBuf *buf, CowlObjCard *restr);
void cowl_str_buf_append_obj_has_value(CowlStrBuf *buf, CowlObjHasValue *restr);
void cowl_str_buf_append_obj_has_self(CowlStrBuf *buf, CowlObjHasSelf *restr);
void cowl_str_buf_append_data_quant(CowlStrBuf *buf, CowlDataQuant *restr);
void cowl_str_buf_append_data_card(CowlStrBuf *buf, CowlDataCard *restr);
void cowl_str_buf_append_data_has_value(CowlStrBuf *buf, CowlDataHasValue *restr);
void cowl_str_buf_append_nary_bool(CowlStrBuf *buf, CowlNAryBool *exp);
void cowl_str_buf_append_obj_compl(CowlStrBuf *buf, CowlObjCompl *exp);
void cowl_str_buf_append_obj_one_of(CowlStrBuf *buf, CowlObjOneOf *restr);

// Data ranges

void cowl_str_buf_append_data_range(CowlStrBuf *buf, CowlDataRange *range);
void cowl_str_buf_append_datatype_restr(CowlStrBuf *buf, CowlDatatypeRestr *restr);
void cowl_str_buf_append_nary_data(CowlStrBuf *buf, CowlNAryData *range);
void cowl_str_buf_append_data_compl(CowlStrBuf *buf, CowlDataCompl *range);
void cowl_str_buf_append_data_one_of(CowlStrBuf *buf, CowlDataOneOf *restr);

// Axioms

void cowl_str_buf_append_axiom(CowlStrBuf *buf, CowlAxiom *axiom);
void cowl_str_buf_append_decl_axiom(CowlStrBuf *buf, CowlDeclAxiom *axiom);
void cowl_str_buf_append_datatype_def_axiom(CowlStrBuf *buf, CowlDatatypeDefAxiom *axiom);
void cowl_str_buf_append_sub_cls_axiom(CowlStrBuf *buf, CowlSubClsAxiom *axiom);
void cowl_str_buf_append_nary_cls_axiom(CowlStrBuf *buf, CowlNAryClsAxiom *axiom);
void cowl_str_buf_append_disj_union_axiom(CowlStrBuf *buf, CowlDisjUnionAxiom *axiom);
void cowl_str_buf_append_cls_assert(CowlStrBuf *buf, CowlClsAssertAxiom *axiom);
void cowl_str_buf_append_nary_ind_axiom(CowlStrBuf *buf, CowlNAryIndAxiom *axiom);
void cowl_str_buf_append_obj_prop_assert(CowlStrBuf *buf, CowlObjPropAssertAxiom *axiom);
void cowl_str_buf_append_data_prop_assert(CowlStrBuf *buf, CowlDataPropAssertAxiom *axiom);
void cowl_str_buf_append_sub_obj_prop_axiom(CowlStrBuf *buf, CowlSubObjPropAxiom *axiom);
void cowl_str_buf_append_sub_obj_prop_chain_axiom(CowlStrBuf *buf, CowlSubObjPropChainAxiom *axiom);
void cowl_str_buf_append_inv_obj_prop_axiom(CowlStrBuf *buf, CowlInvObjPropAxiom *axiom);
void cowl_str_buf_append_nary_obj_prop_axiom(CowlStrBuf *buf, CowlNAryObjPropAxiom *axiom);
void cowl_str_buf_append_obj_prop_char(CowlStrBuf *buf, CowlObjPropCharAxiom *axiom);
void cowl_str_buf_append_obj_prop_domain(CowlStrBuf *buf, CowlObjPropDomainAxiom *axiom);
void cowl_str_buf_append_obj_prop_range(CowlStrBuf *buf, CowlObjPropRangeAxiom *axiom);
void cowl_str_buf_append_sub_data_prop_axiom(CowlStrBuf *buf, CowlSubDataPropAxiom *axiom);
void cowl_str_buf_append_nary_data_prop_axiom(CowlStrBuf *buf, CowlNAryDataPropAxiom *axiom);
void cowl_str_buf_append_func_data_prop_axiom(CowlStrBuf *buf, CowlFuncDataPropAxiom *axiom);
void cowl_str_buf_append_data_prop_domain(CowlStrBuf *buf, CowlDataPropDomainAxiom *axiom);
void cowl_str_buf_append_data_prop_range(CowlStrBuf *buf, CowlDataPropRangeAxiom *axiom);
void cowl_str_buf_append_has_key_axiom(CowlStrBuf *buf, CowlHasKeyAxiom *axiom);
void cowl_str_buf_append_annot_assert(CowlStrBuf *buf, CowlAnnotAssertAxiom *axiom);
void cowl_str_buf_append_sub_annot_prop_axiom(CowlStrBuf *buf, CowlSubAnnotPropAxiom *axiom);
void cowl_str_buf_append_annot_prop_domain_axiom(CowlStrBuf *buf, CowlAnnotPropDomainAxiom *axiom);
void cowl_str_buf_append_annot_prop_range_axiom(CowlStrBuf *buf, CowlAnnotPropRangeAxiom *axiom);

// Collections

void cowl_str_buf_append_cls_exp_set(CowlStrBuf *buf, CowlClsExpSet *set);
void cowl_str_buf_append_data_prop_exp_set(CowlStrBuf *buf, CowlDataPropExpSet *set);
void cowl_str_buf_append_data_range_set(CowlStrBuf *buf, CowlDataRangeSet *set);
void cowl_str_buf_append_facet_restr_set(CowlStrBuf *buf, CowlFacetRestrSet *set);
void cowl_str_buf_append_individual_set(CowlStrBuf *buf, CowlIndividualSet *set);
void cowl_str_buf_append_literal_set(CowlStrBuf *buf, CowlLiteralSet *set);
void cowl_str_buf_append_obj_prop_exp_set(CowlStrBuf *buf, CowlObjPropExpSet *set);
void cowl_str_buf_append_annotation_vec(CowlStrBuf *buf, CowlAnnotationVec *vec);
void cowl_str_buf_append_obj_prop_exp_vec(CowlStrBuf *buf, CowlObjPropExpVec *vec);

// Output

CowlRawString cowl_str_buf_to_raw_string(CowlStrBuf *buf);
CowlString* cowl_str_buf_to_string(CowlStrBuf *buf);

COWL_END_DECLS

#endif // COWL_STR_BUF_H
