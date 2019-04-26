/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_PRIVATE_H
#define COWL_ONTOLOGY_PRIVATE_H

#include "cowl_ontology.h"
#include "cowl_axiom_type.h"

COWL_BEGIN_DECLS

typedef struct UHash(CowlAxiomSet) UHash(CowlAxiomSet);

UHASH_MAP_DECL(CowlClassAxiomMap, CowlClass*, UHash(CowlAxiomSet)*)
UHASH_MAP_DECL(CowlObjPropAxiomMap, CowlObjProp*, UHash(CowlAxiomSet)*)
UHASH_MAP_DECL(CowlNamedIndAxiomMap, CowlNamedIndividual*, UHash(CowlAxiomSet)*)
UHASH_MAP_DECL(CowlAnonIndAxiomMap, CowlAnonIndividual*, UHash(CowlAxiomSet)*)

struct CowlOntology {
    cowl_uint_t ref_count;
    CowlOntologyId *id;
    UHash(CowlAxiomSet) *axioms_by_type[CAT_COUNT];
    UHash(CowlClassAxiomMap) *class_refs;
    UHash(CowlObjPropAxiomMap) *obj_prop_refs;
    UHash(CowlNamedIndAxiomMap) *named_ind_refs;
    UHash(CowlAnonIndAxiomMap) *anon_ind_refs;
};

typedef struct CowlOntology CowlMutableOntology;

#define COWL_ONTOLOGY_INIT {                                                                        \
    .ref_count = 1,                                                                                 \
    .id = NULL,                                                                                     \
    .class_refs = uhash_alloc(CowlClassAxiomMap),                                                   \
    .obj_prop_refs = uhash_alloc(CowlObjPropAxiomMap),                                              \
    .named_ind_refs = uhash_alloc(CowlNamedIndAxiomMap),                                            \
    .anon_ind_refs = uhash_alloc(CowlAnonIndAxiomMap)                                               \
}

#define cowl_ontology_ref_get(o) (((CowlMutableOntology *)(o))->ref_count)
#define cowl_ontology_ref_incr(o) (++cowl_ontology_ref_get(o), (o))
#define cowl_ontology_ref_decr(o) (--cowl_ontology_ref_get(o))

CowlMutableOntology* cowl_ontology_get(void);

void cowl_ontology_set_id(CowlMutableOntology *ontology, CowlOntologyId *id);
void cowl_ontology_add_axiom(CowlMutableOntology *ontology, CowlAxiom *axiom);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_PRIVATE_H
