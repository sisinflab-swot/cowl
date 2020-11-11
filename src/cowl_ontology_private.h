/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_PRIVATE_H
#define COWL_ONTOLOGY_PRIVATE_H

#include "cowl_ontology.h"
#include "cowl_axiom_type.h"
#include "cowl_object_private.h"
#include "cowl_ontology_id_private.h"

COWL_BEGIN_DECLS

typedef uhash_struct(CowlAxiomSet) UHash(CowlAxiomSet);
typedef uvec_struct(CowlAnnotationPtr) UVec(CowlAnnotationPtr);
typedef uvec_struct(CowlAxiomPtr) UVec(CowlAxiomPtr);
typedef uvec_struct(CowlOntologyPtr) UVec(CowlOntologyPtr);

UHASH_DECL(CowlAnnotPropAxiomMap, CowlAnnotProp*, UVec(CowlAxiomPtr)*)
UHASH_DECL(CowlClassAxiomMap, CowlClass*, UVec(CowlAxiomPtr)*)
UHASH_DECL(CowlDataPropAxiomMap, CowlDataProp*, UVec(CowlAxiomPtr)*)
UHASH_DECL(CowlDatatypeAxiomMap, CowlDatatype*, UVec(CowlAxiomPtr)*)
UHASH_DECL(CowlObjPropAxiomMap, CowlObjProp*, UVec(CowlAxiomPtr)*)
UHASH_DECL(CowlNamedIndAxiomMap, CowlNamedInd*, UVec(CowlAxiomPtr)*)
UHASH_DECL(CowlAnonIndAxiomMap, CowlAnonInd*, UVec(CowlAxiomPtr)*)

cowl_struct(CowlOntology) {
    CowlObject super;
    UVec(CowlOntologyPtr) *imports;
    UVec(CowlAnnotationPtr) *annotations;
    UHash(CowlAxiomSet) *axioms_by_type[COWL_AT_COUNT];
    UHash(CowlAnnotPropAxiomMap) *annot_prop_refs;
    UHash(CowlClassAxiomMap) *class_refs;
    UHash(CowlDataPropAxiomMap) *data_prop_refs;
    UHash(CowlDatatypeAxiomMap) *datatype_refs;
    UHash(CowlObjPropAxiomMap) *obj_prop_refs;
    UHash(CowlNamedIndAxiomMap) *named_ind_refs;
    UHash(CowlAnonIndAxiomMap) *anon_ind_refs;
    CowlOntologyID id;
};

#define COWL_ONTOLOGY_INIT ((CowlOntology) {                                                        \
    .super = COWL_OBJECT_INIT(COWL_OT_ONTOLOGY),                                                    \
    .id = COWL_ONTOLOGY_ID_ANONYMOUS,                                                               \
    .imports = NULL,                                                                                \
    .annotations = NULL,                                                                            \
    .annot_prop_refs = uhmap_alloc(CowlAnnotPropAxiomMap),                                          \
    .class_refs = uhmap_alloc(CowlClassAxiomMap),                                                   \
    .data_prop_refs = uhmap_alloc(CowlDataPropAxiomMap),                                            \
    .datatype_refs = uhmap_alloc(CowlDatatypeAxiomMap),                                             \
    .obj_prop_refs = uhmap_alloc(CowlObjPropAxiomMap),                                              \
    .named_ind_refs = uhmap_alloc(CowlNamedIndAxiomMap),                                            \
    .anon_ind_refs = uhmap_alloc(CowlAnonIndAxiomMap),                                              \
})

cowl_struct(CowlOntology)* cowl_ontology_get(void);

void cowl_ontology_set_id(CowlOntology *onto, CowlOntologyID id);
cowl_ret cowl_ontology_set_imports(CowlOntology *onto, UVec(CowlOntologyPtr) *imports);
cowl_ret cowl_ontology_set_annot(CowlOntology *onto, UVec(CowlAnnotationPtr) *annot);
cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAxiom *axiom);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_PRIVATE_H
