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

bool cowl_data_prop_exp_set_equals(CowlDataPropExpSet *lhs, CowlDataPropExpSet *rhs) {
    return uhset_equals(CowlDataPropExpSet, lhs, rhs);
}

cowl_uint_t cowl_data_prop_exp_set_hash(CowlDataPropExpSet *set) {
    return uhset_hash(CowlDataPropExpSet, set);
}

bool cowl_data_prop_exp_set_iterate_signature(CowlDataPropExpSet *set, void *ctx,
                                              CowlEntityIterator iter) {
    uhash_foreach_key(CowlDataPropExpSet, set, prop, {
        if (!cowl_data_prop_exp_iterate_signature(prop, ctx, iter)) return false;
    });
    return true;
}
