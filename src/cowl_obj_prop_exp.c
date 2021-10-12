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
    return cowl_object_incr_ref(prop);
}

void cowl_obj_prop_exp_release(CowlObjPropExp *exp) {
    cowl_object_release((CowlObject *)exp);
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

cowl_uint cowl_obj_prop_exp_hash(CowlObjPropExp *exp) {
    return uhash_ptr_hash(exp);
}

bool cowl_obj_prop_exp_iterate_primitives(CowlObjPropExp *exp, CowlPrimitiveFlags flags,
                                          CowlIterator *iter) {
    return cowl_object_iterate_primitives((CowlObject *)exp, flags, iter);
}
