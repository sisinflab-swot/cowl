/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_prop_exp_set.h"
#include "cowl_data_prop_exp.h"

UHASH_IMPL(CowlDataPropExpSet, cowl_data_prop_exp_hash, cowl_data_prop_exp_equals)

void cowl_data_prop_exp_set_free(CowlDataPropExpSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlDataPropExpSet, set, exp, cowl_data_prop_exp_release(exp));
    uhash_free(CowlDataPropExpSet, set);
}

bool cowl_data_prop_exp_set_equals(CowlDataPropExpSet *lhs, CowlDataPropExpSet *rhs) {
    return uhset_equals(CowlDataPropExpSet, lhs, rhs);
}

cowl_uint_t cowl_data_prop_exp_set_hash(CowlDataPropExpSet *set) {
    return uhset_hash(CowlDataPropExpSet, set);
}

bool cowl_data_prop_exp_set_iterate_signature(CowlDataPropExpSet *set, CowlEntityIterator *iter) {
    uhash_foreach_key(CowlDataPropExpSet, set, prop, {
        if (!cowl_data_prop_exp_iterate_signature(prop, iter)) return false;
    });
    return true;
}
