/// @author Ivano Bilenchi

#include "cowl_axiom_set.h"
#include "cowl_axiom.h"

KHASH_SET_UTILS_IMPL(CowlAxiomSet, CowlAxiom*, cowl_axiom_hash, cowl_axiom_equals);

void cowl_axiom_set_free(CowlAxiomSet *set) {
    if (!set) return;
    kh_foreach_key(set, CowlAxiom *axiom, cowl_axiom_release(axiom));
    kh_destroy(CowlAxiomSet, set);
}
