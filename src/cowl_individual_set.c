/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_individual_set.h"
#include "cowl_individual.h"

UHASH_IMPL(CowlIndividualSet, cowl_individual_hash, cowl_individual_equals)

void cowl_individual_set_free(CowlIndividualSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlIndividualSet, set, exp, cowl_individual_release(exp));
    uhash_free(CowlIndividualSet, (UHash(CowlIndividualSet)*)set);
}

bool cowl_individual_set_equals(CowlIndividualSet *lhs, CowlIndividualSet *rhs) {
    return uhset_equals(CowlIndividualSet, lhs, rhs);
}

cowl_uint cowl_individual_set_hash(CowlIndividualSet *set) {
    return uhset_hash(CowlIndividualSet, set);
}

bool cowl_individual_set_iterate_primitives(CowlIndividualSet *set, CowlIterator *iter,
                                            CowlPrimitiveFlags flags) {
    uhash_foreach_key(CowlIndividualSet, set, ind, {
        if (!cowl_individual_iterate_primitives(ind, iter, flags)) return false;
    });
    return true;
}
