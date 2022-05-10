/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_object_vec_private.h"
#include "cowl_hash_utils.h"
#include "cowl_object.h"

UVEC_IMPL_EQUATABLE(CowlObjectPtr, cowl_object_equals)

void cowl_object_vec_deinit(CowlObjectVec *vec) {
    uvec_foreach(CowlObjectPtr, vec, obj) { cowl_object_release(*obj.item); }
    uvec_deinit(CowlObjectPtr, (UVec(CowlObjectPtr)*)vec);
}

void cowl_object_vec_free(CowlObjectVec *vec) {
    if (!vec) return;
    uvec_foreach(CowlObjectPtr, vec, obj) { cowl_object_release(*obj.item); }
    uvec_free(CowlObjectPtr, (UVec(CowlObjectPtr)*)vec);
}

bool cowl_object_vec_equals(CowlObjectVec *lhs, CowlObjectVec *rhs) {
    return uvec_equals(CowlObjectPtr, lhs, rhs);
}

bool cowl_object_vec_equals_no_order(CowlObjectVec *lhs, CowlObjectVec *rhs) {
    if (lhs == rhs) return true;
    if (uvec_count(CowlObjectPtr, lhs) != uvec_count(CowlObjectPtr, rhs)) return false;
    uvec_foreach(CowlObjectPtr, lhs, obj) {
        if (!uvec_contains(CowlObjectPtr, rhs, *obj.item)) return false;
    }
    return true;
}

ulib_uint cowl_object_vec_hash(CowlObjectVec *vec) {
    ulib_uint hash = 0;

    uvec_foreach(CowlObjectPtr, vec, obj) {
        hash = cowl_hash_1(hash, cowl_object_hash(*obj.item));
    }

    return hash;
}

ulib_uint cowl_object_vec_hash_no_order(CowlObjectVec *vec) {
    ulib_uint hash = 0;

    uvec_foreach(CowlObjectPtr, vec, obj) {
        hash ^= cowl_object_hash(*obj.item);
    }

    return hash;
}

cowl_ret cowl_object_vec_push(UVec(CowlObjectPtr) *vec, CowlObject *object) {
    if ((uvec_push(CowlObjectPtr, vec, object) == UVEC_OK)) {
        cowl_object_retain(object);
        return COWL_OK;
    }
    return COWL_ERR_MEM;
}

bool cowl_object_vec_iterate_primitives(CowlObjectVec *vec, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    if (!vec) return true;

    uvec_foreach(CowlObjectPtr, vec, obj) {
        if (!cowl_object_iterate_primitives(*obj.item, flags, iter)) return false;
    }

    return true;
}
