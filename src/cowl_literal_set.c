/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_literal_set.h"
#include "cowl_literal.h"

UHASH_IMPL(CowlLiteralSet, cowl_literal_hash, cowl_literal_equals)

void cowl_literal_set_free(CowlLiteralSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlLiteralSet, set, literal, cowl_literal_release(literal));
    uhash_free(CowlLiteralSet, (UHash(CowlLiteralSet)*)set);
}

bool cowl_literal_set_equals(CowlLiteralSet *lhs, CowlLiteralSet *rhs) {
    return uhset_equals(CowlLiteralSet, lhs, rhs);
}

cowl_uint cowl_literal_set_hash(CowlLiteralSet *set) {
    return uhset_hash(CowlLiteralSet, set);
}

bool cowl_literal_set_iterate_primitives(CowlLiteralSet *set, CowlIterator *iter,
                                         CowlPrimitiveFlags flags) {
    uhash_foreach_key(CowlLiteralSet, set, literal, {
        if (!cowl_literal_iterate_primitives(literal, iter, flags)) return false;
    });
    return true;
}
