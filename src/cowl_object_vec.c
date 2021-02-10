/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_object_vec_private.h"
#include "cowl_hash_utils.h"
#include "cowl_object.h"

UVEC_IMPL_EQUATABLE(CowlObjectPtr, cowl_object_equals)

void cowl_object_vec_free(CowlObjectVec *vec) {
    cowl_object_vec_free_spec(object, vec);
}

bool cowl_object_vec_equals(CowlObjectVec *lhs, CowlObjectVec *rhs) {
    return uvec_equals(CowlObjectPtr, lhs, rhs);
}

cowl_uint cowl_object_vec_hash(CowlObjectVec *vec) {
    cowl_uint hash = 0;

    uvec_foreach(CowlObjectPtr, vec, prop, {
        hash = cowl_hash_1(hash, cowl_object_hash(prop));
    });

    return hash;
}

bool cowl_object_vec_iterate_primitives(CowlObjectVec *vec, CowlIterator *iter,
                                              CowlPrimitiveFlags flags) {
    uvec_foreach(CowlObjectPtr, vec, prop, {
        if (!cowl_object_iterate_primitives(prop, iter, flags)) return false;
    });
    return true;
}
