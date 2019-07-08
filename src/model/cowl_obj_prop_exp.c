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

CowlObjPropExp* cowl_obj_prop_exp_retain(CowlObjPropExp *prop) {
    return cowl_object_retain(prop);
}

void cowl_obj_prop_exp_release(CowlObjPropExp *prop) {
    if (!prop) return;

    if (prop->is_inverse) {
        cowl_inv_obj_prop_release((CowlInvObjProp *)prop);
    } else {
        cowl_obj_prop_release((CowlObjProp *)prop);
    }
}

bool cowl_obj_prop_exp_is_inverse(CowlObjPropExp *exp) {
    return exp->is_inverse;
}

CowlObjProp* cowl_obj_prop_exp_get_prop(CowlObjPropExp *exp) {
    if (exp->is_inverse) {
        return ((CowlInvObjProp *)exp)->prop;
    } else {
        return (CowlObjProp *)exp;
    }
}

bool cowl_obj_prop_exp_equals(CowlObjPropExp *lhs, CowlObjPropExp *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_obj_prop_exp_hash(CowlObjPropExp *exp) {
    return uhash_ptr_hash(exp);
}

bool cowl_obj_prop_exp_iterate_signature(CowlObjPropExp *exp, CowlEntityIterator *iter) {
    if (exp->is_inverse) {
        return cowl_inv_obj_prop_iterate_signature((CowlInvObjProp *)exp, iter);
    } else {
        return cowl_obj_prop_iterate_signature((CowlObjProp *)exp, iter);
    }
}
