/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_vector_private.h"
#include "cowl_hash_utils.h"

UVEC_IMPL_EQUATABLE(CowlObjectPtr, cowl_equals)

static CowlVector* cowl_vector_alloc(UVec(CowlObjectPtr) *data, bool ordered) {
    CowlVector *vec = ulib_alloc(vec);
    if (!vec) return NULL;

    *vec = (CowlVector) {
        .super = COWL_OBJECT_BIT_INIT(COWL_OT_VECTOR, ordered),
        .data = data ? uvec_move(CowlObjectPtr, data) : uvec_init(CowlObjectPtr)
    };

    uvec_foreach(CowlObjectPtr, &vec->data, obj) {
        cowl_retain(*obj.item);
    }

    return vec;
}

static void cowl_vector_free(CowlVector *vec) {
    uvec_foreach(CowlObjectPtr, &vec->data, obj) { cowl_release(*obj.item); }
    uvec_deinit(CowlObjectPtr, &vec->data);
    ulib_free(vec);
}

CowlVector* cowl_vector_get(UVec(CowlObjectPtr) *vec) {
    return cowl_vector_alloc(vec, false);
}

CowlVector* cowl_vector_ordered_get(UVec(CowlObjectPtr) *vec) {
    return cowl_vector_alloc(vec, true);
}

CowlVector* cowl_vector_retain(CowlVector *vec) {
    return cowl_object_incr_ref(vec);
}

void cowl_vector_release(CowlVector *vec) {
    if (vec && !cowl_object_decr_ref(vec)) {
        cowl_vector_free(vec);
    }
}

UVec(CowlObjectPtr) const* cowl_vector_get_data(CowlVector *vec) {
    return &vec->data;
}

static bool cowl_vector_equals_order(CowlVector *lhs, CowlVector *rhs) {
    return uvec_equals(CowlObjectPtr, &lhs->data, &rhs->data);
}

static bool cowl_vector_equals_no_order(CowlVector *lhs, CowlVector *rhs) {
    if (lhs == rhs) return true;
    if (uvec_count(CowlObjectPtr, &lhs->data) != uvec_count(CowlObjectPtr, &rhs->data)) return false;
    uvec_foreach(CowlObjectPtr, &lhs->data, obj) {
        if (!uvec_contains(CowlObjectPtr, &rhs->data, *obj.item)) return false;
    }
    return true;
}

bool cowl_vector_equals(CowlVector *lhs, CowlVector *rhs) {
    if (cowl_object_bit_get(lhs)) return cowl_vector_equals_order(lhs, rhs);
    return cowl_vector_equals_no_order(lhs, rhs);
}

static ulib_uint cowl_vector_hash_order(CowlVector *vec) {
    ulib_uint hash = 0;

    uvec_foreach(CowlObjectPtr, &vec->data, obj) {
        hash = cowl_hash_1(hash, cowl_hash(*obj.item));
    }

    return hash;
}

static ulib_uint cowl_vector_hash_no_order(CowlVector *vec) {
    ulib_uint hash = 0;

    uvec_foreach(CowlObjectPtr, &vec->data, obj) {
        hash ^= cowl_hash(*obj.item);
    }

    return hash;
}

ulib_uint cowl_vector_hash(CowlVector *vec) {
    if (cowl_object_bit_get(vec)) return cowl_vector_hash_order(vec);
    return cowl_vector_hash_no_order(vec);
}

bool cowl_vector_iterate_primitives(CowlVector *vec, CowlPrimitiveFlags flags, CowlIterator *iter) {
    if (!vec) return true;

    uvec_foreach(CowlObjectPtr, &vec->data, obj) {
        if (!cowl_iterate_primitives(*obj.item, flags, iter)) return false;
    }

    return true;
}

void cowl_object_vec_deinit(UVec(CowlObjectPtr) *vec) {
    uvec_foreach(CowlObjectPtr, vec, obj) { cowl_release(*obj.item); }
    uvec_deinit(CowlObjectPtr, (UVec(CowlObjectPtr) * )vec);
}
