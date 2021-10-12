/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_cls_exp_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlClsExp* cowl_cls_exp_retain(CowlClsExp *exp) {
    return cowl_object_incr_ref(exp);
}

void cowl_cls_exp_release(CowlClsExp *exp) {
    cowl_object_release((CowlObject *)exp);
}

CowlClsExpType cowl_cls_exp_get_type(CowlClsExp *exp) {
    return (CowlClsExpType)(cowl_get_type(exp) - COWL_OT_CE_CLASS);
}

CowlString* cowl_cls_exp_to_string(CowlClsExp *exp)
    COWL_TO_STRING_IMPL(cls_exp, exp)

bool cowl_cls_exp_equals(CowlClsExp *lhs, CowlClsExp *rhs) {
    return cowl_object_equals((CowlObject *)lhs, (CowlObject *)rhs);
}

cowl_uint cowl_cls_exp_hash(CowlClsExp *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_cls_exp_iterate_primitives(CowlClsExp *exp, CowlPrimitiveFlags flags,
                                     CowlIterator *iter) {
    return cowl_object_iterate_primitives((CowlObject *)exp, flags, iter);
}
