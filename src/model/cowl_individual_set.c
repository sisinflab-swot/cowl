/// @author Ivano Bilenchi

#include "cowl_individual_set.h"
#include "cowl_individual.h"

KHASH_SET_UTILS_IMPL(CowlIndividualSet, CowlIndividual*,
                     cowl_individual_hash, cowl_individual_equals);

bool cowl_individual_set_insert(CowlMutableIndividualSet *set, CowlIndividual *exp) {
    return kh_insert(CowlIndividualSet, set, cowl_individual_retain(exp));
}

void cowl_individual_set_free(CowlIndividualSet *set) {
    if (!set) return;
    kh_foreach_key(set, CowlIndividual *exp, cowl_individual_release(exp));
    kh_destroy(CowlIndividualSet, (khash_t(CowlIndividualSet) *)set);
}