/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STREAM_H
#define COWL_STREAM_H

#include "cowl_std.h"
#include "cowl_types.h"

COWL_BEGIN_DECLS

// Misc

#define cowl_stream_write_static(stream, literal) uostream_write_literal(stream, literal, NULL)

ustream_ret cowl_stream_write_object(UOStream *s, CowlObject *obj);
ustream_ret cowl_stream_write_object_debug(UOStream *s, CowlObject *obj);
ustream_ret cowl_stream_write_string(UOStream *stream, CowlString *string);
ustream_ret cowl_stream_write_ustring(UOStream *stream, UString string);
ustream_ret cowl_stream_write_iri(UOStream *s, CowlIRI *iri);
ustream_ret cowl_stream_write_iri_no_brackets(UOStream *s, CowlIRI *iri);
ustream_ret cowl_stream_write_ontology(UOStream *s, CowlOntology *onto);
ustream_ret cowl_stream_write_ontology_id(UOStream *s, CowlOntologyId *id);
ustream_ret cowl_stream_write_literal(UOStream *s, CowlLiteral *literal);
ustream_ret cowl_stream_write_facet_restr(UOStream *s, CowlFacetRestr *restr);
ustream_ret cowl_stream_write_node_id(UOStream *s, CowlNodeId id);
ustream_ret cowl_stream_write_annotation(UOStream *s, CowlAnnotation *annotation);
ustream_ret cowl_stream_write_annot_value(UOStream *s, CowlAnnotValue *value);
ustream_ret cowl_stream_write_uint(UOStream *s, uint64_t uint);
ustream_ret cowl_stream_write_error(UOStream *s, CowlError const *error);

// Entities and Primitives

ustream_ret cowl_stream_write_entity(UOStream *s, CowlEntity *entity);
ustream_ret cowl_stream_write_primitive(UOStream *s, CowlPrimitive *primitive);
ustream_ret cowl_stream_write_class(UOStream *s, CowlClass *cls);
ustream_ret cowl_stream_write_datatype(UOStream *s, CowlDatatype *dt);
ustream_ret cowl_stream_write_obj_prop(UOStream *s, CowlObjProp *prop);
ustream_ret cowl_stream_write_data_prop(UOStream *s, CowlDataProp *prop);
ustream_ret cowl_stream_write_annot_prop(UOStream *s, CowlAnnotProp *prop);
ustream_ret cowl_stream_write_named_ind(UOStream *s, CowlNamedInd *ind);
ustream_ret cowl_stream_write_anon_ind(UOStream *s, CowlAnonInd *ind);
ustream_ret cowl_stream_write_individual(UOStream *s, CowlIndividual *ind);

// Object property expressions

ustream_ret cowl_stream_write_obj_prop_exp(UOStream *s, CowlObjPropExp *exp);
ustream_ret cowl_stream_write_inv_obj_prop(UOStream *s, CowlInvObjProp *prop);

// Data property expressions

ustream_ret cowl_stream_write_data_prop_exp(UOStream *s, CowlDataPropExp *exp);

// Class expressions

ustream_ret cowl_stream_write_cls_exp(UOStream *s, CowlClsExp *exp);
ustream_ret cowl_stream_write_obj_quant(UOStream *s, CowlObjQuant *restr);
ustream_ret cowl_stream_write_obj_card(UOStream *s, CowlObjCard *restr);
ustream_ret cowl_stream_write_obj_has_value(UOStream *s, CowlObjHasValue *restr);
ustream_ret cowl_stream_write_obj_has_self(UOStream *s, CowlObjHasSelf *restr);
ustream_ret cowl_stream_write_data_quant(UOStream *s, CowlDataQuant *restr);
ustream_ret cowl_stream_write_data_card(UOStream *s, CowlDataCard *restr);
ustream_ret cowl_stream_write_data_has_value(UOStream *s, CowlDataHasValue *restr);
ustream_ret cowl_stream_write_nary_bool(UOStream *s, CowlNAryBool *exp);
ustream_ret cowl_stream_write_obj_compl(UOStream *s, CowlObjCompl *exp);
ustream_ret cowl_stream_write_obj_one_of(UOStream *s, CowlObjOneOf *restr);

// Data ranges

ustream_ret cowl_stream_write_data_range(UOStream *s, CowlDataRange *range);
ustream_ret cowl_stream_write_datatype_restr(UOStream *s, CowlDatatypeRestr *restr);
ustream_ret cowl_stream_write_nary_data(UOStream *s, CowlNAryData *range);
ustream_ret cowl_stream_write_data_compl(UOStream *s, CowlDataCompl *range);
ustream_ret cowl_stream_write_data_one_of(UOStream *s, CowlDataOneOf *restr);

// Axioms

ustream_ret cowl_stream_write_axiom(UOStream *s, CowlAxiom *axiom);
ustream_ret cowl_stream_write_decl_axiom(UOStream *s, CowlDeclAxiom *axiom);
ustream_ret cowl_stream_write_datatype_def_axiom(UOStream *s, CowlDatatypeDefAxiom *axiom);
ustream_ret cowl_stream_write_sub_cls_axiom(UOStream *s, CowlSubClsAxiom *axiom);
ustream_ret cowl_stream_write_nary_cls_axiom(UOStream *s, CowlNAryClsAxiom *axiom);
ustream_ret cowl_stream_write_disj_union_axiom(UOStream *s, CowlDisjUnionAxiom *axiom);
ustream_ret cowl_stream_write_cls_assert(UOStream *s, CowlClsAssertAxiom *axiom);
ustream_ret cowl_stream_write_nary_ind_axiom(UOStream *s, CowlNAryIndAxiom *axiom);
ustream_ret cowl_stream_write_obj_prop_assert(UOStream *s, CowlObjPropAssertAxiom *axiom);
ustream_ret cowl_stream_write_data_prop_assert(UOStream *s, CowlDataPropAssertAxiom *axiom);
ustream_ret cowl_stream_write_sub_obj_prop_axiom(UOStream *s, CowlSubObjPropAxiom *axiom);
ustream_ret cowl_stream_write_sub_obj_prop_chain_axiom(UOStream *s, CowlSubObjPropChainAxiom *axiom);
ustream_ret cowl_stream_write_inv_obj_prop_axiom(UOStream *s, CowlInvObjPropAxiom *axiom);
ustream_ret cowl_stream_write_nary_obj_prop_axiom(UOStream *s, CowlNAryObjPropAxiom *axiom);
ustream_ret cowl_stream_write_obj_prop_char(UOStream *s, CowlObjPropCharAxiom *axiom);
ustream_ret cowl_stream_write_obj_prop_domain(UOStream *s, CowlObjPropDomainAxiom *axiom);
ustream_ret cowl_stream_write_obj_prop_range(UOStream *s, CowlObjPropRangeAxiom *axiom);
ustream_ret cowl_stream_write_sub_data_prop_axiom(UOStream *s, CowlSubDataPropAxiom *axiom);
ustream_ret cowl_stream_write_nary_data_prop_axiom(UOStream *s, CowlNAryDataPropAxiom *axiom);
ustream_ret cowl_stream_write_func_data_prop_axiom(UOStream *s, CowlFuncDataPropAxiom *axiom);
ustream_ret cowl_stream_write_data_prop_domain(UOStream *s, CowlDataPropDomainAxiom *axiom);
ustream_ret cowl_stream_write_data_prop_range(UOStream *s, CowlDataPropRangeAxiom *axiom);
ustream_ret cowl_stream_write_has_key_axiom(UOStream *s, CowlHasKeyAxiom *axiom);
ustream_ret cowl_stream_write_annot_assert(UOStream *s, CowlAnnotAssertAxiom *axiom);
ustream_ret cowl_stream_write_sub_annot_prop_axiom(UOStream *s, CowlSubAnnotPropAxiom *axiom);
ustream_ret cowl_stream_write_annot_prop_domain_axiom(UOStream *s, CowlAnnotPropDomainAxiom *axiom);
ustream_ret cowl_stream_write_annot_prop_range_axiom(UOStream *s, CowlAnnotPropRangeAxiom *axiom);

// Collections

ustream_ret cowl_stream_write_object_set(UOStream *s, CowlObjectTable *set);
ustream_ret cowl_stream_write_object_vec(UOStream *s, CowlObjectVec *vec);

COWL_END_DECLS

#endif // COWL_STREAM_H
