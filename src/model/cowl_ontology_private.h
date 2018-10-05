/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_PRIVATE_H
#define COWL_ONTOLOGY_PRIVATE_H

#include "cowl_ontology.h"
#include "cowl_axiom_type.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef khash_struct(CowlAxiomSet) khash_t(CowlAxiomSet);

KHASH_MAP_UTILS_DECL(CowlClassAxiomMap, CowlClass const*, khash_t(CowlAxiomSet)*);
KHASH_MAP_UTILS_DECL(CowlObjPropAxiomMap, CowlObjProp const*, khash_t(CowlAxiomSet)*);
KHASH_MAP_UTILS_DECL(CowlNamedIndAxiomMap, CowlNamedIndividual const*, khash_t(CowlAxiomSet)*);
KHASH_MAP_UTILS_DECL(CowlAnonIndAxiomMap, CowlAnonIndividual const*, khash_t(CowlAxiomSet)*);

typedef struct CowlOntology {
    CowlOntologyId const *id;
    khash_t(CowlAxiomSet) *axioms_by_type[CAT_COUNT];
    khash_t(CowlClassAxiomMap) *class_refs;
    khash_t(CowlObjPropAxiomMap) *obj_prop_refs;
    khash_t(CowlNamedIndAxiomMap) *named_ind_refs;
    khash_t(CowlAnonIndAxiomMap) *anon_ind_refs;
} CowlOntology;

bool cowl_ontology_add_axiom(CowlOntology *ontology, CowlAxiom const *axiom);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_PRIVATE_H
