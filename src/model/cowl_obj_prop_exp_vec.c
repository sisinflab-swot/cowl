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

VECTOR_IMPL_EQUATABLE(CowlObjPropExpPtr, cowl_obj_prop_exp_equals)

void cowl_obj_prop_exp_vec_free(CowlObjPropExpVec *vec) {
    if (!vec) return;
    vector_foreach(CowlObjPropExpPtr, vec, prop, cowl_obj_prop_exp_release(prop));
    vector_free(CowlObjPropExpPtr, vec);
}

bool cowl_obj_prop_exp_vec_equals(CowlObjPropExpVec *lhs, CowlObjPropExpVec *rhs) {
    return vector_equals(CowlObjPropExpPtr, lhs, rhs);
}

cowl_uint_t cowl_obj_prop_exp_vec_hash(CowlObjPropExpVec *vec) {
    cowl_uint_t hash = 0;

    vector_foreach(CowlObjPropExpPtr, vec, prop, {
        hash = cowl_hash_iter(hash, cowl_obj_prop_exp_hash(prop));
    });

    return hash;
}

bool cowl_obj_prop_exp_vec_iterate_signature(CowlObjPropExpVec *vec, CowlEntityIterator *iter) {
    vector_foreach(CowlObjPropExpPtr, vec, prop, {
        if (!cowl_obj_prop_exp_iterate_signature(prop, iter)) return false;
    });
    return true;
}

bool cowl_obj_prop_exp_vec_iterate_primitives(CowlObjPropExpVec *vec, CowlPrimitiveIterator *iter) {
    vector_foreach(CowlObjPropExpPtr, vec, prop, {
        if (!cowl_obj_prop_exp_iterate_primitives(prop, iter)) return false;
    });
    return true;
}
