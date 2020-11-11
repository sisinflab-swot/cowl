/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_exp_vec.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"

UVEC_IMPL_EQUATABLE(CowlObjPropExpPtr, cowl_obj_prop_exp_equals)

void cowl_obj_prop_exp_vec_free(CowlObjPropExpVec *vec) {
    if (!vec) return;
    uvec_foreach(CowlObjPropExpPtr, vec, prop, cowl_obj_prop_exp_release(prop));
    uvec_free(CowlObjPropExpPtr, (UVec(CowlObjPropExpPtr)*)vec);
}

bool cowl_obj_prop_exp_vec_equals(CowlObjPropExpVec *lhs, CowlObjPropExpVec *rhs) {
    return uvec_equals(CowlObjPropExpPtr, lhs, rhs);
}

cowl_uint cowl_obj_prop_exp_vec_hash(CowlObjPropExpVec *vec) {
    cowl_uint hash = 0;

    uvec_foreach(CowlObjPropExpPtr, vec, prop, {
        hash = cowl_hash_iter(hash, cowl_obj_prop_exp_hash(prop));
    });

    return hash;
}

bool cowl_obj_prop_exp_vec_iterate_primitives(CowlObjPropExpVec *vec, CowlIterator *iter,
                                              CowlPrimitiveFlags flags) {
    uvec_foreach(CowlObjPropExpPtr, vec, prop, {
        if (!cowl_obj_prop_exp_iterate_primitives(prop, iter, flags)) return false;
    });
    return true;
}
