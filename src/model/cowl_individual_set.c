/// @author Ivano Bilenchi

#include "cowl_individual_set.h"
#include "cowl_individual.h"

UHASH_SET_IMPL(CowlIndividualSet, CowlIndividual*, cowl_individual_hash, cowl_individual_equals)

void cowl_individual_set_free(CowlIndividualSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlIndividualSet, set, exp, cowl_individual_release(exp));
    uhash_free(CowlIndividualSet, (UHash(CowlIndividualSet) *)set);
}

bool cowl_individual_set_equals(CowlIndividualSet *lhs, CowlIndividualSet *rhs) {
    return uhset_equals(CowlIndividualSet, lhs, rhs);
}

cowl_uint_t cowl_individual_set_hash(CowlIndividualSet *set) {
    return uhset_hash(CowlIndividualSet, set);
}

bool cowl_individual_set_iterate_signature(CowlIndividualSet *set, CowlEntityIterator *iter) {
    uhash_foreach_key(CowlIndividualSet, set, ind, {
        if (!cowl_individual_iterate_signature(ind, iter)) return false;
    });
    return true;
}
