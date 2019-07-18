/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_PRIVATE_H
#define COWL_ONTOLOGY_PRIVATE_H

#include "cowl_ontology.h"
#include "cowl_axiom_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

typedef uhash_struct(CowlAxiomSet) UHash(CowlAxiomSet);
typedef vector_struct(CowlAnnotationPtr) Vector(CowlAnnotationPtr);
typedef vector_struct(CowlOntologyPtr) Vector(CowlOntologyPtr);

UHASH_DECL(CowlAnnotPropAxiomMap, CowlAnnotProp*, UHash(CowlAxiomSet)*)
UHASH_DECL(CowlClassAxiomMap, CowlClass*, UHash(CowlAxiomSet)*)
UHASH_DECL(CowlDataPropAxiomMap, CowlDataProp*, UHash(CowlAxiomSet)*)
UHASH_DECL(CowlDatatypeAxiomMap, CowlDatatype*, UHash(CowlAxiomSet)*)
UHASH_DECL(CowlObjPropAxiomMap, CowlObjProp*, UHash(CowlAxiomSet)*)
UHASH_DECL(CowlNamedIndAxiomMap, CowlNamedInd*, UHash(CowlAxiomSet)*)
UHASH_DECL(CowlAnonIndAxiomMap, CowlAnonInd*, UHash(CowlAxiomSet)*)

cowl_struct(CowlOntology) {
    CowlObject super;
    CowlOntologyID *id;
    Vector(CowlOntologyPtr) *imports;
    Vector(CowlAnnotationPtr) *annotations;
    UHash(CowlAxiomSet) *axioms_by_type[COWL_AT_COUNT];
    UHash(CowlAnnotPropAxiomMap) *annot_prop_refs;
    UHash(CowlClassAxiomMap) *class_refs;
    UHash(CowlDataPropAxiomMap) *data_prop_refs;
    UHash(CowlDatatypeAxiomMap) *datatype_refs;
    UHash(CowlObjPropAxiomMap) *obj_prop_refs;
    UHash(CowlNamedIndAxiomMap) *named_ind_refs;
    UHash(CowlAnonIndAxiomMap) *anon_ind_refs;
};

#define COWL_ONTOLOGY_INIT {                                                                        \
    .super = COWL_OBJECT_INIT,                                                                      \
    .id = NULL,                                                                                     \
    .imports = NULL,                                                                                \
    .annotations = NULL,                                                                            \
    .annot_prop_refs = uhmap_alloc(CowlAnnotPropAxiomMap),                                          \
    .class_refs = uhmap_alloc(CowlClassAxiomMap),                                                   \
    .data_prop_refs = uhmap_alloc(CowlDataPropAxiomMap),                                            \
    .datatype_refs = uhmap_alloc(CowlDatatypeAxiomMap),                                             \
    .obj_prop_refs = uhmap_alloc(CowlObjPropAxiomMap),                                              \
    .named_ind_refs = uhmap_alloc(CowlNamedIndAxiomMap),                                            \
    .anon_ind_refs = NULL,                                                                          \
}

cowl_struct(CowlOntology)* cowl_ontology_get(void);

void cowl_ontology_set_id(cowl_struct(CowlOntology) *onto, CowlOntologyID *id);
void cowl_ontology_set_imports(cowl_struct(CowlOntology) *onto, Vector(CowlOntologyPtr) *imports);
void cowl_ontology_set_annot(cowl_struct(CowlOntology) *onto, Vector(CowlAnnotationPtr) *annot);
void cowl_ontology_add_axiom(cowl_struct(CowlOntology) *onto, CowlAxiom *axiom);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_PRIVATE_H
