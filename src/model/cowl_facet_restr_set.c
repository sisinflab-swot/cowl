/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_facet_restr_set.h"
#include "cowl_facet_restr.h"

UHASH_IMPL(CowlFacetRestrSet, cowl_facet_restr_hash, cowl_facet_restr_equals)

void cowl_facet_restr_set_free(CowlFacetRestrSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlFacetRestrSet, set, restr, cowl_facet_restr_release(restr));
    uhash_free(CowlFacetRestrSet, (UHash(CowlFacetRestrSet) *)set);
}

bool cowl_facet_restr_set_equals(CowlFacetRestrSet *lhs, CowlFacetRestrSet *rhs) {
    return uhset_equals(CowlFacetRestrSet, lhs, rhs);
}

cowl_uint_t cowl_facet_restr_set_hash(CowlFacetRestrSet *set) {
    return uhset_hash(CowlFacetRestrSet, set);
}

bool cowl_facet_restr_set_iterate_signature(CowlFacetRestrSet *set, CowlEntityIterator *iter) {
    uhash_foreach_key(CowlFacetRestrSet, set, restr, {
        if (!cowl_facet_restr_iterate_signature(restr, iter)) return false;
    });
    return true;
}
