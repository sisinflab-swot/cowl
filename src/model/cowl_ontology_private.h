/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_PRIVATE_H
#define COWL_ONTOLOGY_PRIVATE_H

#include "cowl_ontology.h"
#include "cowl_axiom_type.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef khash_struct(CowlAxiomSet) khash_t(CowlAxiomSet);

KHASH_MAP_UTILS_DECL(CowlClassAxiomMap, CowlClass*, khash_t(CowlAxiomSet)*);
KHASH_MAP_UTILS_DECL(CowlObjPropAxiomMap, CowlObjProp*, khash_t(CowlAxiomSet)*);
KHASH_MAP_UTILS_DECL(CowlNamedIndAxiomMap, CowlNamedIndividual*, khash_t(CowlAxiomSet)*);
KHASH_MAP_UTILS_DECL(CowlAnonIndAxiomMap, CowlAnonIndividual*, khash_t(CowlAxiomSet)*);

struct CowlOntology {
    CowlOntologyId *id;
    khash_t(CowlAxiomSet) *axioms_by_type[CAT_COUNT];
    khash_t(CowlClassAxiomMap) *class_refs;
    khash_t(CowlObjPropAxiomMap) *obj_prop_refs;
    khash_t(CowlNamedIndAxiomMap) *named_ind_refs;
    khash_t(CowlAnonIndAxiomMap) *anon_ind_refs;
};

typedef struct CowlOntology CowlMutableOntology;

CowlMutableOntology* cowl_ontology_alloc(CowlOntologyId *id);
void cowl_ontology_free(CowlOntology *ontology);

void cowl_ontology_add_axiom(CowlMutableOntology *ontology, CowlAxiom *axiom);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_PRIVATE_H
