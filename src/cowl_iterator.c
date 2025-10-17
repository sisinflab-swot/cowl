/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_iterator.h"
#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_object.h"
#include "cowl_table.h"  // IWYU pragma: keep, needed for UHash(CowlObjectPtr)
#include "cowl_vector.h" // IWYU pragma: keep, needed for UVec(CowlObjectPtr)
#include "ulib.h"

static bool for_each_store_vec(void *vec, CowlAny *obj) {
    return ulib_is_ok(uvec_push(CowlObjectPtr, vec, obj));
}

static bool for_each_store_vec_retain(void *vec, CowlAny *obj) {
    ulib_ret const ret = uvec_push(CowlObjectPtr, vec, obj);
    if (ulib_is_err(ret)) return false;
    cowl_retain(obj);
    return true;
}

static bool for_each_store_set(void *set, CowlAny *obj) {
    return ulib_is_ok(uhset_insert(CowlObjectPtr, set, obj));
}

static bool for_each_store_set_retain(void *set, CowlAny *obj) {
    ulib_ret const ret = uhset_insert(CowlObjectPtr, set, obj);
    if (ulib_is_err(ret)) return false;
    if (ret == ULIB_OK) cowl_retain(obj);
    return true;
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

static bool for_each_retain(cowl_unused void *ctx, CowlAny *obj) {
    cowl_retain(obj);
    return true;
}

static bool for_each_release(cowl_unused void *ctx, CowlAny *obj) {
    cowl_release(obj);
    return true;
}

CowlIterator cowl_iterator_vec(UVec(CowlObjectPtr) *vec, bool retain) {
    return (CowlIterator){
        .ctx = vec,
        .for_each = retain ? for_each_store_vec_retain : for_each_store_vec,
    };
}

CowlIterator cowl_iterator_set(UHash(CowlObjectPtr) *set, bool retain) {
    return (CowlIterator){
        .ctx = set,
        .for_each = retain ? for_each_store_set_retain : for_each_store_set,
    };
}

CowlIterator cowl_iterator_count(ulib_uint *count) {
    return (CowlIterator){ .ctx = count, .for_each = for_each_count };
}

CowlIterator cowl_iterator_contains(CowlAny *object) {
    return (CowlIterator){
        .ctx = object,
        .for_each = cowl_is_primitive(object) ? for_each_contains_primitive : for_each_contains,
    };
}

CowlIterator cowl_iterator_retain(void) {
    return (CowlIterator){ .for_each = for_each_retain };
}

CowlIterator cowl_iterator_release(void) {
    return (CowlIterator){ .for_each = for_each_release };
}
