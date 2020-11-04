/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_TYPES_H
#define COWL_TYPES_H

#include "cowl_std.h"
#include "cowl_annot_value_type.h"
#include "cowl_axiom_type.h"
#include "cowl_card_type.h"
#include "cowl_cls_exp_type.h"
#include "cowl_data_range_type.h"
#include "cowl_entity_type.h"
#include "cowl_facet.h"
#include "cowl_iterator_private.h"
#include "cowl_nary_type.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_node_id.h"
#include "cowl_ontology_id.h"
#include "cowl_quant_type.h"
#include "cowl_raw_string.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotAssertAxiom);
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlAnnotPropDomainAxiom);
cowl_struct_decl(CowlAnnotPropRangeAxiom);
cowl_struct_decl(CowlAnnotValue);
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlClsAssertAxiom);
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataCard);
cowl_struct_decl(CowlDataCompl);
cowl_struct_decl(CowlDataHasValue);
cowl_struct_decl(CowlDataOneOf);
cowl_struct_decl(CowlDataProp);
cowl_struct_decl(CowlDataPropAssertAxiom);
cowl_struct_decl(CowlDataPropDomainAxiom);
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlDataPropRangeAxiom);
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDataQuant);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlDatatypeDefAxiom);
cowl_struct_decl(CowlDatatypeRestr);
cowl_struct_decl(CowlDeclAxiom);
cowl_struct_decl(CowlDisjUnionAxiom);
cowl_struct_decl(CowlEntity);
cowl_struct_decl(CowlFacetRestr);
cowl_struct_decl(CowlFuncDataPropAxiom);
cowl_struct_decl(CowlHasKeyAxiom);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlInvObjProp);
cowl_struct_decl(CowlInvObjPropAxiom);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlLogger);
cowl_struct_decl(CowlNamedInd);
cowl_struct_decl(CowlNAryBool);
cowl_struct_decl(CowlNAryClsAxiom);
cowl_struct_decl(CowlNAryData);
cowl_struct_decl(CowlNAryDataPropAxiom);
cowl_struct_decl(CowlNAryIndAxiom);
cowl_struct_decl(CowlNAryObjPropAxiom);
cowl_struct_decl(CowlObjCard);
cowl_struct_decl(CowlObjCompl);
cowl_struct_decl(CowlObjHasSelf);
cowl_struct_decl(CowlObjHasValue);
cowl_struct_decl(CowlObjOneOf);
cowl_struct_decl(CowlObjProp);
cowl_struct_decl(CowlObjPropAssertAxiom);
cowl_struct_decl(CowlObjPropCharAxiom);
cowl_struct_decl(CowlObjPropDomainAxiom);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlObjPropRangeAxiom);
cowl_struct_decl(CowlObjQuant);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlParser);
cowl_struct_decl(CowlPrimitive);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlSubAnnotPropAxiom);
cowl_struct_decl(CowlSubClsAxiom);
cowl_struct_decl(CowlSubDataPropAxiom);
cowl_struct_decl(CowlSubObjPropAxiom);
cowl_struct_decl(CowlSubObjPropChainAxiom);

cowl_hash_decl(CowlClsExpSet);
cowl_hash_decl(CowlDataPropExpSet);
cowl_hash_decl(CowlDataRangeSet);
cowl_hash_decl(CowlFacetRestrSet);
cowl_hash_decl(CowlIndividualSet);
cowl_hash_decl(CowlLiteralSet);
cowl_hash_decl(CowlObjPropExpSet);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);
cowl_vector_decl(CowlObjPropExpPtr, CowlObjPropExpVec);
cowl_vector_decl(CowlOntologyPtr, CowlOntologyVec);

COWL_END_DECLS

#endif // COWL_TYPES_H
