/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_exp_private.h"
#include "cowl_inv_obj_prop_private.h"
#include "cowl_obj_prop_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlObjPropExp* cowl_obj_prop_exp_retain(CowlObjPropExp *prop) {
    return cowl_object_retain(prop);
}

void cowl_obj_prop_exp_release(CowlObjPropExp *exp) {
    if (!exp) return;

    if (cowl_obj_prop_exp_is_inverse(exp)) {
        cowl_inv_obj_prop_release((CowlInvObjProp *)exp);
    } else {
        cowl_obj_prop_release((CowlObjProp *)exp);
    }
}

bool cowl_obj_prop_exp_is_inverse(CowlObjPropExp *exp) {
    return cowl_get_type(exp) == COWL_OT_OPE_INV_OBJ_PROP;
}

CowlObjProp* cowl_obj_prop_exp_get_prop(CowlObjPropExp *exp) {
    if (cowl_obj_prop_exp_is_inverse(exp)) {
        return ((CowlInvObjProp *)exp)->prop;
    } else {
        return (CowlObjProp *)exp;
    }
}

CowlString* cowl_obj_prop_exp_to_string(CowlObjPropExp *exp)
    COWL_TO_STRING_IMPL(obj_prop_exp, exp)

bool cowl_obj_prop_exp_equals(CowlObjPropExp *lhs, CowlObjPropExp *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_obj_prop_exp_hash(CowlObjPropExp *exp) {
    return uhash_ptr_hash(exp);
}

bool cowl_obj_prop_exp_iterate_signature(CowlObjPropExp *exp, CowlEntityIterator *iter) {
    if (cowl_obj_prop_exp_is_inverse(exp)) {
        return cowl_inv_obj_prop_iterate_signature((CowlInvObjProp *)exp, iter);
    } else {
        return cowl_obj_prop_iterate_signature((CowlObjProp *)exp, iter);
    }
}

bool cowl_obj_prop_exp_iterate_primitives(CowlObjPropExp *exp, CowlPrimitiveIterator *iter) {
    if (cowl_obj_prop_exp_is_inverse(exp)) {
        return cowl_inv_obj_prop_iterate_primitives((CowlInvObjProp *)exp, iter);
    } else {
        return cowl_obj_prop_iterate_primitives((CowlObjProp *)exp, iter);
    }
}
