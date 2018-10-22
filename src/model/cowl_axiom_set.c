/// @author Ivano Bilenchi

#include "cowl_axiom_set.h"
#include "cowl_axiom.h"

KHASH_SET_UTILS_IMPL(CowlAxiomSet, CowlAxiom*, cowl_axiom_hash, cowl_axiom_equals);

bool cowl_axiom_set_add(khash_t(CowlAxiomSet) *set, CowlAxiom *axiom) {
    return kh_insert(CowlAxiomSet, set, cowl_axiom_retain(axiom));
}

void cowl_axiom_set_free(khash_t(CowlAxiomSet) const *set) {
    if (!set) return;
    kh_foreach_key(set, CowlAxiom *axiom, cowl_axiom_release(axiom));
    kh_destroy(CowlAxiomSet, (khash_t(CowlAxiomSet) *)set);
}
