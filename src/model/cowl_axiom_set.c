/// @author Ivano Bilenchi

#include "cowl_axiom_set.h"
#include "cowl_axiom.h"

KHASH_SET_UTILS_IMPL(CowlAxiomSet, CowlAxiom const*, cowl_axiom_hash, cowl_axiom_equals);

bool cowl_axiom_set_add(khash_t(CowlAxiomSet) *set, CowlAxiom const *axiom) {
    bool inserted = kh_insert(CowlAxiomSet, set, axiom);
    cowl_axiom_retain(axiom);
    return inserted;
}

void cowl_axiom_set_free(khash_t(CowlAxiomSet) const *set) {
    if (!set) return;
    kh_foreach_key(set, CowlAxiom const *axiom, cowl_axiom_release(axiom));
    kh_destroy(CowlAxiomSet, (khash_t(CowlAxiomSet) *)set);
}
