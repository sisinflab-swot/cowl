/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_has_self_private.h"
#include "cowl_alloc.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlObjHasSelf* cowl_obj_has_self_alloc(CowlObjPropExp *prop) {
    CowlObjHasSelf *exp = cowl_alloc(exp);
    if (!exp) return NULL;

    cowl_uint_t hash = cowl_hash_1(COWL_HASH_INIT_OBJ_HAS_SELF, cowl_obj_prop_exp_hash(prop));

    *exp = (CowlObjHasSelf) {
        .super = COWL_CLS_EXP_INIT(COWL_CET_OBJ_HAS_SELF, hash),
        .prop = cowl_obj_prop_exp_retain(prop)
    };

    return exp;
}

static void cowl_obj_has_self_free(CowlObjHasSelf *exp) {
    if (!exp) return;
    cowl_obj_prop_exp_release(exp->prop);
    cowl_free(exp);
}

CowlObjHasSelf* cowl_obj_has_self_get(CowlObjPropExp *prop) {
    if (!prop) return NULL;
    return cowl_obj_has_self_alloc(prop);
}

CowlObjHasSelf* cowl_obj_has_self_retain(CowlObjHasSelf *exp) {
    return cowl_object_retain(exp);
}

void cowl_obj_has_self_release(CowlObjHasSelf *exp) {
    if (exp && !cowl_object_release(exp)) {
        cowl_obj_has_self_free(exp);
    }
}

CowlObjPropExp* cowl_obj_has_self_get_prop(CowlObjHasSelf *exp) {
    return exp->prop;
}

CowlString* cowl_obj_has_self_to_string(CowlObjHasSelf *exp)
    COWL_TO_STRING_IMPL(obj_has_self, exp)

bool cowl_obj_has_self_equals(CowlObjHasSelf *lhs, CowlObjHasSelf *rhs) {
    return cowl_obj_prop_exp_equals(lhs->prop, rhs->prop);
}

cowl_uint_t cowl_obj_has_self_hash(CowlObjHasSelf *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_obj_has_self_iterate_signature(CowlObjHasSelf *exp, CowlEntityIterator *iter) {
    return cowl_obj_prop_exp_iterate_signature(exp->prop, iter);
}

bool cowl_obj_has_self_iterate_primitives(CowlObjHasSelf *exp, CowlPrimitiveIterator *iter) {
    return cowl_obj_prop_exp_iterate_primitives(exp->prop, iter);
}
