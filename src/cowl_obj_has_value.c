/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_has_value_private.h"
#include "cowl_hash_utils.h"
#include "cowl_individual.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlObjHasValue* cowl_obj_has_value_alloc(CowlObjPropExp *prop, CowlIndividual *ind) {
    CowlObjHasValue *exp = cowl_alloc(exp);
    if (!exp) return NULL;

    cowl_uint hash = cowl_hash_2(COWL_HASH_INIT_OBJ_HAS_VALUE,
                                 cowl_obj_prop_exp_hash(prop),
                                 cowl_individual_hash(ind));

    *exp = (CowlObjHasValue) {
        .super = COWL_CLS_EXP_INIT(COWL_CET_OBJ_HAS_VALUE, hash),
        .prop = cowl_obj_prop_exp_retain(prop),
        .ind = cowl_individual_retain(ind)
    };

    return exp;
}

static void cowl_obj_has_value_free(CowlObjHasValue *exp) {
    if (!exp) return;
    cowl_obj_prop_exp_release(exp->prop);
    cowl_individual_release(exp->ind);
    cowl_free(exp);
}

CowlObjHasValue* cowl_obj_has_value_get(CowlObjPropExp *prop, CowlIndividual *ind) {
    if (!(prop && ind)) return NULL;
    return cowl_obj_has_value_alloc(prop, ind);
}

CowlObjHasValue* cowl_obj_has_value_retain(CowlObjHasValue *exp) {
    return cowl_object_retain(exp);
}

void cowl_obj_has_value_release(CowlObjHasValue *exp) {
    if (exp && !cowl_object_release(exp)) {
        cowl_obj_has_value_free(exp);
    }
}

CowlObjPropExp* cowl_obj_has_value_get_prop(CowlObjHasValue *exp) {
    return exp->prop;
}

CowlIndividual* cowl_obj_has_value_get_ind(CowlObjHasValue *exp) {
    return exp->ind;
}

CowlString* cowl_obj_has_value_to_string(CowlObjHasValue *exp)
    COWL_TO_STRING_IMPL(obj_has_value, exp)


bool cowl_obj_has_value_equals(CowlObjHasValue *lhs, CowlObjHasValue *rhs) {
    return cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_individual_equals(lhs->ind, rhs->ind);
}

cowl_uint cowl_obj_has_value_hash(CowlObjHasValue *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_obj_has_value_iterate_primitives(CowlObjHasValue *exp, CowlIterator *iter,
                                           CowlPrimitiveFlags flags) {
    return (cowl_obj_prop_exp_iterate_primitives(exp->prop, iter, flags) &&
            cowl_individual_iterate_primitives(exp->ind, iter, flags));
}
