/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_H
#define COWL_ONTOLOGY_H

#include "cowl_axiom_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlAnonIndividual const CowlAnonIndividual;
typedef struct CowlAxiom const CowlAxiom;
typedef struct CowlClass const CowlClass;
typedef struct CowlClsExp const CowlClsExp;
typedef struct CowlIndividual const CowlIndividual;
typedef struct CowlNamedIndividual const CowlNamedIndividual;
typedef struct CowlObjProp const CowlObjProp;
typedef struct CowlOntologyId const CowlOntologyId;

typedef struct CowlOntology const CowlOntology;

CowlOntology* cowl_ontology_retain(CowlOntology *onto);
void cowl_ontology_release(CowlOntology *onto);

CowlOntologyId* cowl_ontology_get_id(CowlOntology *onto);

bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs);
uint32_t cowl_ontology_hash(CowlOntology *onto);

void cowl_ontology_iterate_signature(CowlOntology *onto, void *ctx, CowlEntityIterator iter);

void cowl_ontology_iterate_classes(CowlOntology *onto, void *ctx, CowlClassIterator iter);

void cowl_ontology_iterate_obj_prop(CowlOntology *onto, void *ctx, CowlObjPropIterator iter);

void cowl_ontology_iterate_named_individuals(CowlOntology *onto, void *ctx,
                                             CowlNamedIndividualIterator iter);

void cowl_ontology_iterate_anon_individuals(CowlOntology *onto, void *ctx,
                                            CowlAnonIndividualIterator iter);

void cowl_ontology_iterate_axioms(CowlOntology *onto, void *ctx, CowlAxiomIterator iter);

void cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          void *ctx, CowlAxiomIterator iter);

void cowl_ontology_iterate_axioms_for_class(CowlOntology *onto, CowlClass *owl_class,
                                            void *ctx, CowlAxiomIterator iter);

void cowl_ontology_iterate_axioms_for_obj_prop(CowlOntology *onto, CowlObjProp *obj_prop,
                                               void *ctx, CowlAxiomIterator iter);

void cowl_ontology_iterate_axioms_for_named_individual(CowlOntology *onto,
                                                       CowlNamedIndividual *individual,
                                                       void *ctx, CowlAxiomIterator iter);

void cowl_ontology_iterate_axioms_for_anon_individual(CowlOntology *onto,
                                                      CowlAnonIndividual *individual,
                                                      void *ctx, CowlAxiomIterator iter);

void cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       void *ctx, CowlClsExpIterator iter);

void cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         void *ctx, CowlClsExpIterator iter);

void cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      void *ctx, CowlClsExpIterator iter);

void cowl_ontology_iterate_disjoint_classes(CowlOntology *onto, CowlClass *owl_class,
                                            void *ctx, CowlClsExpIterator iter);

void cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *individual,
                                 void *ctx, CowlClsExpIterator iter);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_H
