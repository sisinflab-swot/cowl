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

#include "cowl_node_id.h"
#include "cowl_raw_string.h"
#include "cowl_std.h"
#include "cowl_types.h"

COWL_BEGIN_DECLS

typedef char CowlChar;
UVEC_DECL(CowlChar)

typedef cowl_struct(CowlStrBuf) {
    cowl_ret ret;
    UVec(CowlChar) storage;
} CowlStrBuf;

#define cowl_str_buf_init ((CowlStrBuf){ .ret = 0, .storage = uvec_init(CowlChar) })
#define cowl_str_buf_deinit(buf) uvec_deinit((buf)->storage)

// Strings

cowl_ret cowl_str_buf_append_cstring(CowlStrBuf *buf, char const *string, cowl_uint length);
cowl_ret cowl_str_buf_append_raw_string(CowlStrBuf *buf, CowlRawString string);
cowl_ret cowl_str_buf_append_string(CowlStrBuf *buf, CowlString *string);
cowl_ret cowl_str_buf_append_format(CowlStrBuf *buf, char const *format, ...);
cowl_ret cowl_str_buf_append_format_list(CowlStrBuf *buf, char const *format, va_list args);

#define cowl_str_buf_append_static(BUF, STRING) \
    cowl_str_buf_append_cstring(BUF, STRING, sizeof(STRING) - 1)

// Misc

cowl_ret cowl_str_buf_append_object(CowlStrBuf *buf, CowlObject *obj);
cowl_ret cowl_str_buf_append_iri(CowlStrBuf *buf, CowlIRI *iri);
cowl_ret cowl_str_buf_append_iri_no_brackets(CowlStrBuf *buf, CowlIRI *iri);
cowl_ret cowl_str_buf_append_ontology_id(CowlStrBuf *buf, CowlOntologyID *id);
cowl_ret cowl_str_buf_append_literal(CowlStrBuf *buf, CowlLiteral *literal);
cowl_ret cowl_str_buf_append_facet_restr(CowlStrBuf *buf, CowlFacetRestr *restr);
cowl_ret cowl_str_buf_append_node_id(CowlStrBuf *buf, CowlNodeID id);
cowl_ret cowl_str_buf_append_annotation(CowlStrBuf *buf, CowlAnnotation *annotation);
cowl_ret cowl_str_buf_append_annot_value(CowlStrBuf *buf, CowlAnnotValue *value);
cowl_ret cowl_str_buf_append_uint(CowlStrBuf *buf, cowl_uint uint);

// Entities and Primitives

cowl_ret cowl_str_buf_append_entity(CowlStrBuf *buf, CowlEntity *entity);
cowl_ret cowl_str_buf_append_primitive(CowlStrBuf *buf, CowlPrimitive *primitive);
cowl_ret cowl_str_buf_append_class(CowlStrBuf *buf, CowlClass *cls);
cowl_ret cowl_str_buf_append_datatype(CowlStrBuf *buf, CowlDatatype *dt);
cowl_ret cowl_str_buf_append_obj_prop(CowlStrBuf *buf, CowlObjProp *prop);
cowl_ret cowl_str_buf_append_data_prop(CowlStrBuf *buf, CowlDataProp *prop);
cowl_ret cowl_str_buf_append_annot_prop(CowlStrBuf *buf, CowlAnnotProp *prop);
cowl_ret cowl_str_buf_append_named_ind(CowlStrBuf *buf, CowlNamedInd *ind);
cowl_ret cowl_str_buf_append_anon_ind(CowlStrBuf *buf, CowlAnonInd *ind);
cowl_ret cowl_str_buf_append_individual(CowlStrBuf *buf, CowlIndividual *ind);

// Object property expressions

cowl_ret cowl_str_buf_append_obj_prop_exp(CowlStrBuf *buf, CowlObjPropExp *exp);
cowl_ret cowl_str_buf_append_inv_obj_prop(CowlStrBuf *buf, CowlInvObjProp *prop);

// Data property expressions

cowl_ret cowl_str_buf_append_data_prop_exp(CowlStrBuf *buf, CowlDataPropExp *exp);

// Class expressions

cowl_ret cowl_str_buf_append_cls_exp(CowlStrBuf *buf, CowlClsExp *exp);
cowl_ret cowl_str_buf_append_obj_quant(CowlStrBuf *buf, CowlObjQuant *restr);
cowl_ret cowl_str_buf_append_obj_card(CowlStrBuf *buf, CowlObjCard *restr);
cowl_ret cowl_str_buf_append_obj_has_value(CowlStrBuf *buf, CowlObjHasValue *restr);
cowl_ret cowl_str_buf_append_obj_has_self(CowlStrBuf *buf, CowlObjHasSelf *restr);
cowl_ret cowl_str_buf_append_data_quant(CowlStrBuf *buf, CowlDataQuant *restr);
cowl_ret cowl_str_buf_append_data_card(CowlStrBuf *buf, CowlDataCard *restr);
cowl_ret cowl_str_buf_append_data_has_value(CowlStrBuf *buf, CowlDataHasValue *restr);
cowl_ret cowl_str_buf_append_nary_bool(CowlStrBuf *buf, CowlNAryBool *exp);
cowl_ret cowl_str_buf_append_obj_compl(CowlStrBuf *buf, CowlObjCompl *exp);
cowl_ret cowl_str_buf_append_obj_one_of(CowlStrBuf *buf, CowlObjOneOf *restr);

// Data ranges

cowl_ret cowl_str_buf_append_data_range(CowlStrBuf *buf, CowlDataRange *range);
cowl_ret cowl_str_buf_append_datatype_restr(CowlStrBuf *buf, CowlDatatypeRestr *restr);
cowl_ret cowl_str_buf_append_nary_data(CowlStrBuf *buf, CowlNAryData *range);
cowl_ret cowl_str_buf_append_data_compl(CowlStrBuf *buf, CowlDataCompl *range);
cowl_ret cowl_str_buf_append_data_one_of(CowlStrBuf *buf, CowlDataOneOf *restr);

// Axioms

cowl_ret cowl_str_buf_append_axiom(CowlStrBuf *buf, CowlAxiom *axiom);
cowl_ret cowl_str_buf_append_decl_axiom(CowlStrBuf *buf, CowlDeclAxiom *axiom);
cowl_ret cowl_str_buf_append_datatype_def_axiom(CowlStrBuf *buf, CowlDatatypeDefAxiom *axiom);
cowl_ret cowl_str_buf_append_sub_cls_axiom(CowlStrBuf *buf, CowlSubClsAxiom *axiom);
cowl_ret cowl_str_buf_append_nary_cls_axiom(CowlStrBuf *buf, CowlNAryClsAxiom *axiom);
cowl_ret cowl_str_buf_append_disj_union_axiom(CowlStrBuf *buf, CowlDisjUnionAxiom *axiom);
cowl_ret cowl_str_buf_append_cls_assert(CowlStrBuf *buf, CowlClsAssertAxiom *axiom);
cowl_ret cowl_str_buf_append_nary_ind_axiom(CowlStrBuf *buf, CowlNAryIndAxiom *axiom);
cowl_ret cowl_str_buf_append_obj_prop_assert(CowlStrBuf *buf, CowlObjPropAssertAxiom *axiom);
cowl_ret cowl_str_buf_append_data_prop_assert(CowlStrBuf *buf, CowlDataPropAssertAxiom *axiom);
cowl_ret cowl_str_buf_append_sub_obj_prop_axiom(CowlStrBuf *buf, CowlSubObjPropAxiom *axiom);
cowl_ret cowl_str_buf_append_sub_obj_prop_chain_axiom(CowlStrBuf *buf, CowlSubObjPropChainAxiom *axiom);
cowl_ret cowl_str_buf_append_inv_obj_prop_axiom(CowlStrBuf *buf, CowlInvObjPropAxiom *axiom);
cowl_ret cowl_str_buf_append_nary_obj_prop_axiom(CowlStrBuf *buf, CowlNAryObjPropAxiom *axiom);
cowl_ret cowl_str_buf_append_obj_prop_char(CowlStrBuf *buf, CowlObjPropCharAxiom *axiom);
cowl_ret cowl_str_buf_append_obj_prop_domain(CowlStrBuf *buf, CowlObjPropDomainAxiom *axiom);
cowl_ret cowl_str_buf_append_obj_prop_range(CowlStrBuf *buf, CowlObjPropRangeAxiom *axiom);
cowl_ret cowl_str_buf_append_sub_data_prop_axiom(CowlStrBuf *buf, CowlSubDataPropAxiom *axiom);
cowl_ret cowl_str_buf_append_nary_data_prop_axiom(CowlStrBuf *buf, CowlNAryDataPropAxiom *axiom);
cowl_ret cowl_str_buf_append_func_data_prop_axiom(CowlStrBuf *buf, CowlFuncDataPropAxiom *axiom);
cowl_ret cowl_str_buf_append_data_prop_domain(CowlStrBuf *buf, CowlDataPropDomainAxiom *axiom);
cowl_ret cowl_str_buf_append_data_prop_range(CowlStrBuf *buf, CowlDataPropRangeAxiom *axiom);
cowl_ret cowl_str_buf_append_has_key_axiom(CowlStrBuf *buf, CowlHasKeyAxiom *axiom);
cowl_ret cowl_str_buf_append_annot_assert(CowlStrBuf *buf, CowlAnnotAssertAxiom *axiom);
cowl_ret cowl_str_buf_append_sub_annot_prop_axiom(CowlStrBuf *buf, CowlSubAnnotPropAxiom *axiom);
cowl_ret cowl_str_buf_append_annot_prop_domain_axiom(CowlStrBuf *buf, CowlAnnotPropDomainAxiom *axiom);
cowl_ret cowl_str_buf_append_annot_prop_range_axiom(CowlStrBuf *buf, CowlAnnotPropRangeAxiom *axiom);

// Collections

cowl_ret cowl_str_buf_append_object_set(CowlStrBuf *buf, CowlObjectTable *set);
cowl_ret cowl_str_buf_append_object_vec(CowlStrBuf *buf, CowlObjectVec *vec);

// Output

CowlRawString cowl_str_buf_to_raw_string(CowlStrBuf *buf);
CowlString* cowl_str_buf_to_string(CowlStrBuf *buf);

COWL_END_DECLS

#endif // COWL_STR_BUF_H
