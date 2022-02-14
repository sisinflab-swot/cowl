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
#include "cowl_object_table.h"
#include "cowl_template.h"

static CowlObjOneOf* cowl_obj_one_of_alloc(CowlObjectTable *inds) {
    CowlObjOneOf *exp = ulib_alloc(exp);
    if (!exp) return NULL;

    ulib_uint hash = cowl_hash_1(COWL_HASH_INIT_OBJECT_ONE_OF,
                                 cowl_object_set_hash(inds));

    *exp = (CowlObjOneOf) {
        .super = COWL_CLS_EXP_INIT(COWL_CET_OBJ_ONE_OF, hash),
        .inds = inds
    };

    return exp;
}

static void cowl_obj_one_of_free(CowlObjOneOf *exp) {
    cowl_object_set_free(exp->inds);
    ulib_free(exp);
}

CowlObjOneOf* cowl_obj_one_of_get(CowlObjectTable *inds) {
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

CowlObjectTable* cowl_obj_one_of_get_inds(CowlObjOneOf *exp) {
    return exp->inds;
}

CowlString* cowl_obj_one_of_to_string(CowlObjOneOf *exp)
    COWL_TO_STRING_IMPL(obj_one_of, exp)

bool cowl_obj_one_of_equals(CowlObjOneOf *lhs, CowlObjOneOf *rhs) {
    return cowl_object_hash_equals(lhs, rhs) && cowl_object_set_equals(lhs->inds, rhs->inds);
}

ulib_uint cowl_obj_one_of_hash(CowlObjOneOf *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_obj_one_of_iterate_primitives(CowlObjOneOf *exp, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return cowl_object_set_iterate_primitives(exp->inds, flags, iter);
}
