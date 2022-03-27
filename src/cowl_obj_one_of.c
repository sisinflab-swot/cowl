/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_one_of_private.h"
#include "cowl_hash_utils.h"
#include "cowl_object_vec.h"
#include "cowl_template.h"

static CowlObjOneOf* cowl_obj_one_of_alloc(CowlObjectVec *inds) {
    CowlObjOneOf *exp = ulib_alloc(exp);
    if (!exp) return NULL;

    *exp = (CowlObjOneOf) {
        .super = COWL_CLS_EXP_INIT(COWL_CET_OBJ_ONE_OF),
        .inds = inds
    };

    return exp;
}

static void cowl_obj_one_of_free(CowlObjOneOf *exp) {
    cowl_object_vec_free(exp->inds);
    ulib_free(exp);
}

CowlObjOneOf* cowl_obj_one_of_get(CowlObjectVec *inds) {
    if (!inds) return NULL;
    return cowl_obj_one_of_alloc(inds);
}

CowlObjOneOf* cowl_obj_one_of_retain(CowlObjOneOf *exp) {
    return cowl_object_incr_ref(exp);
}

void cowl_obj_one_of_release(CowlObjOneOf *exp) {
    if (exp && !cowl_object_decr_ref(exp)) {
        cowl_obj_one_of_free(exp);
    }
}

CowlObjectVec* cowl_obj_one_of_get_inds(CowlObjOneOf *exp) {
    return exp->inds;
}

CowlString* cowl_obj_one_of_to_string(CowlObjOneOf *exp)
    COWL_TO_STRING_IMPL(obj_one_of, exp)

bool cowl_obj_one_of_equals(CowlObjOneOf *lhs, CowlObjOneOf *rhs) {
    return cowl_object_vec_equals(lhs->inds, rhs->inds);
}

ulib_uint cowl_obj_one_of_hash(CowlObjOneOf *exp) {
    return cowl_hash_1(COWL_HASH_INIT_OBJECT_ONE_OF, cowl_object_vec_hash(exp->inds));
}

bool cowl_obj_one_of_iterate_primitives(CowlObjOneOf *exp, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return cowl_object_vec_iterate_primitives(exp->inds, flags, iter);
}
