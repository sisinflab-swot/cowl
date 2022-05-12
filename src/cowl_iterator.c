/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_iterator_private.h"
#include "cowl_set.h"
#include "cowl_vector.h"

static bool cowl_store_vec(void *vec, void *obj) {
    return uvec_push(CowlObjectPtr, vec, obj) != UVEC_ERR;
}

static bool cowl_store_set(void *set, void *obj) {
    return uhset_insert(CowlObjectTable, set, obj) != UHASH_ERR;
}

CowlIterator cowl_iterator_vec_init(UVec(CowlObjectPtr) *vec) {
    if (!vec) {
        vec = ulib_alloc(vec);
        *vec = uvec_init(CowlObjectPtr);
    }
    return (CowlIterator) { .ctx = vec, .for_each = cowl_store_vec };
}

CowlIterator cowl_iterator_set_init(UHash(CowlObjectTable) *set) {
    if (!set) {
        set = ulib_alloc(set);
        *set = uhset_init(CowlObjectTable);
    }
    return (CowlIterator) { .ctx = set, .for_each = cowl_store_set };
}
