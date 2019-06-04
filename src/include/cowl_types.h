/// @author Ivano Bilenchi

#ifndef COWL_TYPES_H
#define COWL_TYPES_H

#include "cowl_std.h"
#include "cowl_axiom_type.h"
#include "cowl_card_type.h"
#include "cowl_cls_exp_type.h"
#include "cowl_data_range_type.h"
#include "cowl_entity.h"
#include "cowl_entity_type.h"
#include "cowl_facet.h"
#include "cowl_iterator.h"
#include "cowl_nary_type.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_quant_type.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlAnonIndividual);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlClsAssertAxiom);
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataCard);
cowl_struct_decl(CowlDataCompl);
cowl_struct_decl(CowlDataHasValue);
cowl_struct_decl(CowlDataOneOf);
cowl_struct_decl(CowlDataProp);
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
cowl_struct_decl(CowlFacetRestr);
cowl_struct_decl(CowlFuncDataPropAxiom);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlInvObjProp);
cowl_struct_decl(CowlInvObjPropAxiom);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlLogger);
cowl_struct_decl(CowlNamedIndividual);
cowl_struct_decl(CowlNAryBool);
cowl_struct_decl(CowlNAryClsAxiom);
cowl_struct_decl(CowlNAryDataPropAxiom);
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
cowl_struct_decl(CowlOntologyId);
cowl_struct_decl(CowlParser);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlSubClsAxiom);
cowl_struct_decl(CowlSubDataPropAxiom);
cowl_struct_decl(CowlSubObjPropAxiom);

cowl_hash_decl(CowlClsExpSet);
cowl_hash_decl(CowlDataPropExpSet);
cowl_hash_decl(CowlDataRangeSet);
cowl_hash_decl(CowlFacetRestrSet);
cowl_hash_decl(CowlIndividualSet);
cowl_hash_decl(CowlLiteralSet);
cowl_hash_decl(CowlObjPropExpSet);
cowl_hash_decl_mutable(CowlClsExpSet, CowlMutableClsExpSet);
cowl_hash_decl_mutable(CowlDataPropExpSet, CowlMutableDataPropExpSet);
cowl_hash_decl_mutable(CowlDataRangeSet, CowlMutableDataRangeSet);
cowl_hash_decl_mutable(CowlFacetRestrSet, CowlMutableFacetRestrSet);
cowl_hash_decl_mutable(CowlIndividualSet, CowlMutableIndividualSet);
cowl_hash_decl_mutable(CowlLiteralSet, CowlMutableLiteralSet);
cowl_hash_decl_mutable(CowlObjPropExpSet, CowlMutableObjPropExpSet);

COWL_END_DECLS

#endif // COWL_TYPES_H
