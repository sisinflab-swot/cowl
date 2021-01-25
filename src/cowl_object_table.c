/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_object_table.h"
#include "cowl_object.h"

UHASH_IMPL(CowlObjectTable, cowl_object_hash, cowl_object_equals)

void cowl_object_set_free(CowlObjectTable *set) {
    if (!set) return;
    uhash_foreach_key(CowlObjectTable, set, obj, cowl_object_release(obj));
    uhash_free(CowlObjectTable, (UHash(CowlObjectTable)*)set);
}

bool cowl_object_set_equals(CowlObjectTable *lhs, CowlObjectTable *rhs) {
    return uhset_equals(CowlObjectTable, lhs, rhs);
}

cowl_uint cowl_object_set_hash(CowlObjectTable *set) {
    return uhset_hash(CowlObjectTable, set);
}

bool cowl_object_set_iterate_primitives(CowlObjectTable *set, CowlIterator *iter,
                                        CowlPrimitiveFlags flags) {
    uhash_foreach_key(CowlObjectTable, set, obj, {
        if (!cowl_object_iterate_primitives(obj, iter, flags)) return false;
    });
    return true;
}
