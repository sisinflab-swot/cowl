/// @author Ivano Bilenchi

#include "cowl_individual_set_private.h"
#include "cowl_individual.h"

UHASH_SET_IMPL(CowlIndividualSet, CowlIndividual*, cowl_individual_hash, cowl_individual_equals)

bool cowl_individual_set_insert(CowlMutableIndividualSet *set, CowlIndividual *exp) {
    return uhset_insert(CowlIndividualSet, set, cowl_individual_retain(exp)) == UHASH_INSERTED;
}

void cowl_individual_set_free(CowlIndividualSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlIndividualSet, set, exp, cowl_individual_release(exp));
    uhash_free(CowlIndividualSet, (UHash(CowlIndividualSet) *)set);
}
