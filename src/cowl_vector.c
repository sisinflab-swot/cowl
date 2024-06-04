/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_vector.h"
#include "cowl_any.h"
#include "cowl_iterator.h"
#include "cowl_object.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_primitive_flags.h"
#include "cowl_ret.h"
#include "cowl_vector_private.h"
#include "ulib.h"
#include <stddef.h>

UVEC_IMPL_EQUATABLE(CowlObjectPtr, cowl_equals)

CowlVector *cowl_vector(UVec(CowlObjectPtr) *data) {
    if (data && uvec_shrink(CowlObjectPtr, data) != UVEC_OK) return NULL;

    CowlVector *vec = ulib_alloc(vec);
    if (!vec) return NULL;

    *vec = (CowlVector){
        .super = COWL_OBJECT_INIT(COWL_OT_VECTOR),
        .data = data ? uvec_move(CowlObjectPtr, data) : uvec(CowlObjectPtr),
    };

    uvec_foreach (CowlObjectPtr, &vec->data, obj) {
        cowl_retain(*obj.item);
    }

    return vec;
}

CowlVector *cowl_vector_ordered_empty(void) {
    CowlVector *ret = cowl_vector_empty();
    cowl_vector_set_ordered(ret);
    return ret;
}

static void cowl_vector_free_ex(CowlVector *vec, bool release_elements) {
    if (release_elements) {
        uvec_foreach (CowlObjectPtr, &vec->data, obj) {
            cowl_release(*obj.item);
        }
    }
    uvec_deinit(CowlObjectPtr, &vec->data);
    ulib_free(vec);
}

void cowl_vector_free(CowlVector *vec) {
    cowl_vector_free_ex(vec, true);
}

void cowl_vector_release_ex(CowlVector *vec, bool release_elements) {
    if (vec && !cowl_object_decr_ref(vec)) {
        cowl_vector_free_ex(vec, release_elements);
    }
}

UVec(CowlObjectPtr) const *cowl_vector_get_data(CowlVector *vec) {
    static UVec(CowlObjectPtr) const empty_data = { 0 };
    return vec ? &vec->data : &empty_data;
}

static bool cowl_vector_equals_order(CowlVector *lhs, CowlVector *rhs) {
    return uvec_equals(CowlObjectPtr, &lhs->data, &rhs->data);
}

static bool cowl_vector_equals_no_order(CowlVector *lhs, CowlVector *rhs) {
    if (lhs == rhs) return true;
    if (uvec_count(CowlObjectPtr, &lhs->data) != uvec_count(CowlObjectPtr, &rhs->data)) {
        return false;
    }
    uvec_foreach (CowlObjectPtr, &lhs->data, obj) {
        if (!uvec_contains(CowlObjectPtr, &rhs->data, *obj.item)) return false;
    }
    return true;
}

bool cowl_vector_equals(CowlVector *lhs, CowlVector *rhs) {
    if (cowl_vector_is_ordered(lhs)) return cowl_vector_equals_order(lhs, rhs);
    return cowl_vector_equals_no_order(lhs, rhs);
}

static ulib_uint cowl_vector_ordered_hash(CowlVector *vec) {
    ulib_uint hash = 0;
    uvec_foreach (CowlObjectPtr, &vec->data, obj) {
        ulib_uint h = cowl_hash(*obj.item);
        hash = ulib_hash_combine(hash, h);
    }
    return hash;
}

static ulib_uint cowl_vector_unordered_hash(CowlVector *vec) {
    ulib_uint hash = 0;
    uvec_foreach (CowlObjectPtr, &vec->data, obj) {
        hash ^= cowl_hash(*obj.item);
    }
    return hash;
}

ulib_uint cowl_vector_hash(CowlVector *vec) {
    if (cowl_vector_is_ordered(vec)) return cowl_vector_ordered_hash(vec);
    return cowl_vector_unordered_hash(vec);
}

bool cowl_vector_iterate_primitives(CowlVector *vec, CowlPrimitiveFlags flags, CowlIterator *iter) {
    if (!vec) return true;
    uvec_foreach (CowlObjectPtr, &vec->data, obj) {
        if (!cowl_iterate_primitives(*obj.item, flags, iter)) return false;
    }
    return true;
}

cowl_ret cowl_vector_add(CowlVector *vec, CowlAny *object) {
    if (uvec_push(CowlObjectPtr, &vec->data, object)) return COWL_ERR_MEM;
    cowl_retain(object);
    return COWL_OK;
}

cowl_ret cowl_vector_push(CowlVector *vec, CowlAny *object) {
    if (uvec_push(CowlObjectPtr, &vec->data, object) == UVEC_OK) return COWL_OK;
    cowl_release(object);
    return COWL_ERR_MEM;
}

bool cowl_vector_remove(CowlVector *vec, CowlAny *object) {
    bool removed = false;
    if (cowl_vector_is_ordered(vec)) {
        removed = uvec_remove(CowlObjectPtr, &vec->data, object);
    } else {
        removed = uvec_unordered_remove(CowlObjectPtr, &vec->data, object);
    }
    if (removed) cowl_release(object);
    return removed;
}

cowl_ret cowl_vector_shrink(CowlVector *vec) {
    return uvec_shrink(CowlObjectPtr, &vec->data) ? COWL_ERR_MEM : COWL_OK;
}
