/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_H
#define COWL_ONTOLOGY_H

#include "cowl_axiom_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"


COWL_BEGIN_DECLS

typedef struct CowlAnonIndividual CowlAnonIndividual;
typedef struct CowlAxiom CowlAxiom;
typedef struct CowlClass CowlClass;
typedef struct CowlClsExp CowlClsExp;
typedef struct CowlIndividual CowlIndividual;
typedef struct CowlNamedIndividual CowlNamedIndividual;
typedef struct CowlObjProp CowlObjProp;
typedef struct CowlOntologyId CowlOntologyId;

typedef struct CowlOntology CowlOntology;

CowlOntologyId const* cowl_ontology_get_id(CowlOntology const *onto);

bool cowl_ontology_equals(CowlOntology const *lhs, CowlOntology const *rhs);
uint32_t cowl_ontology_hash(CowlOntology const *onto);

void cowl_ontology_enum_axioms(CowlOntology const *onto, void *ctx, CowlAxiomIterator iter);

void cowl_ontology_enum_axioms_of_type(CowlOntology const *onto, CowlAxiomType type,
                                       void *ctx, CowlAxiomIterator iter);

void cowl_ontology_enum_axioms_for_class(CowlOntology const *onto, CowlClass const *owl_class,
                                          void *ctx, CowlAxiomIterator iter);

void cowl_ontology_enum_axioms_for_obj_prop(CowlOntology const *onto, CowlObjProp const *obj_prop,
                                            void *ctx, CowlAxiomIterator iter);

void cowl_ontology_enum_axioms_for_named_individual(CowlOntology const *onto,
                                                    CowlNamedIndividual const *individual,
                                                    void *ctx, CowlAxiomIterator iter);

void cowl_ontology_enum_axioms_for_anon_individual(CowlOntology const *onto,
                                                   CowlAnonIndividual const *individual,
                                                   void *ctx, CowlAxiomIterator iter);

void cowl_ontology_enum_sub_classes(CowlOntology const *onto, CowlClass const *owl_class,
                                    void *ctx, CowlClsExpIterator iter);

void cowl_ontology_enum_super_classes(CowlOntology const *onto, CowlClass const *owl_class,
                                      void *ctx, CowlClsExpIterator iter);

void cowl_ontology_enum_eq_classes(CowlOntology const *onto, CowlClass const *owl_class,
                                   void *ctx, CowlClsExpIterator iter);

void cowl_ontology_enum_disjoint_classes(CowlOntology const *onto, CowlClass const *owl_class,
                                         void *ctx, CowlClsExpIterator iter);

void cowl_ontology_enum_types(CowlOntology const *onto, CowlIndividual const *individual,
                              void *ctx, CowlClsExpIterator iter);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_H
