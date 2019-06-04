/// @author Ivano Bilenchi

#include "cowl_data_prop_exp_set_private.h"
#include "cowl_data_prop_exp.h"

UHASH_SET_IMPL(CowlDataPropExpSet, CowlDataPropExp*,
               cowl_data_prop_exp_hash, cowl_data_prop_exp_equals)

bool cowl_data_prop_exp_set_insert(CowlMutableDataPropExpSet *set, CowlDataPropExp *exp) {
    return uhset_insert(CowlDataPropExpSet, set, cowl_data_prop_exp_retain(exp)) == UHASH_INSERTED;
}

void cowl_data_prop_exp_set_free(CowlDataPropExpSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlDataPropExpSet, set, exp, cowl_data_prop_exp_release(exp));
    uhash_free(CowlDataPropExpSet, (UHash(CowlDataPropExpSet) *)set);
}
