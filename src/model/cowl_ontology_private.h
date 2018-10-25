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
    uint32_t ref_count;
    CowlOntologyId *id;
    khash_t(CowlAxiomSet) *axioms_by_type[CAT_COUNT];
    khash_t(CowlClassAxiomMap) *class_refs;
    khash_t(CowlObjPropAxiomMap) *obj_prop_refs;
    khash_t(CowlNamedIndAxiomMap) *named_ind_refs;
    khash_t(CowlAnonIndAxiomMap) *anon_ind_refs;
};

typedef struct CowlOntology CowlMutableOntology;

#define COWL_ONTOLOGY_INIT {                                                                        \
    .ref_count = 1,                                                                                 \
    .id = NULL,                                                                                     \
    .class_refs = kh_init(CowlClassAxiomMap),                                                       \
    .obj_prop_refs = kh_init(CowlObjPropAxiomMap),                                                  \
    .named_ind_refs = kh_init(CowlNamedIndAxiomMap),                                                \
    .anon_ind_refs = kh_init(CowlAnonIndAxiomMap)                                                   \
}

#define cowl_ontology_ref_get(o) (((CowlMutableOntology *)(o))->ref_count)
#define cowl_ontology_ref_incr(o) (++cowl_ontology_ref_get(o), (o))
#define cowl_ontology_ref_decr(o) (--cowl_ontology_ref_get(o))

CowlMutableOntology* cowl_ontology_get(void);

void cowl_ontology_set_id(CowlMutableOntology *ontology, CowlOntologyId *id);
void cowl_ontology_add_axiom(CowlMutableOntology *ontology, CowlAxiom *axiom);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_PRIVATE_H
