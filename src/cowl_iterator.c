/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_iterator_private.h"
#include "cowl_table.h"
#include "cowl_vector.h"

static bool for_each_store_vec(void *vec, CowlAny *obj) {
    return uvec_push(CowlObjectPtr, vec, obj) != UVEC_ERR;
}

static bool for_each_store_set(void *set, CowlAny *obj) {
    return uhset_insert(CowlObjectTable, set, obj) != UHASH_ERR;
}

static bool for_each_count(void *count, cowl_unused CowlAny *obj) {
    (*((ulib_uint *)count))++;
    return true;
}

static bool for_each_contains(void *ctx, CowlAny *obj) {
    return !cowl_equals(obj, ctx);
}

static bool for_each_contains_primitive(void *ctx, CowlAny *obj) {
    return obj != ctx;
}

CowlIterator cowl_iterator_vec(UVec(CowlObjectPtr) *vec) {
    return (CowlIterator){ .ctx = vec, .for_each = for_each_store_vec };
}

CowlIterator cowl_iterator_set(UHash(CowlObjectTable) *set) {
    return (CowlIterator){ .ctx = set, .for_each = for_each_store_set };
}

CowlIterator cowl_iterator_count(ulib_uint *count) {
    return (CowlIterator){ .ctx = count, .for_each = for_each_count };
}

CowlIterator cowl_iterator_contains(CowlAny *object) {
    return (CowlIterator){
        .ctx = object,
        .for_each = cowl_is_primitive(object) ? for_each_contains_primitive : for_each_contains
    };
}
