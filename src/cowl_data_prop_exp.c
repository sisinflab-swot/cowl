/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_prop_exp_private.h"
#include "cowl_data_prop_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlDataPropExp* cowl_data_prop_exp_retain(CowlDataPropExp *exp) {
    return cowl_object_incr_ref(exp);
}

void cowl_data_prop_exp_release(CowlDataPropExp *exp) {
    cowl_data_prop_release((CowlDataProp *)exp);
}

CowlDataProp* cowl_data_prop_exp_get_prop(CowlDataPropExp *exp) {
    return (CowlDataProp *)exp;
}

CowlString* cowl_data_prop_exp_to_string(CowlDataPropExp *exp)
    COWL_TO_STRING_IMPL(data_prop_exp, exp)

bool cowl_data_prop_exp_equals(CowlDataPropExp *lhs, CowlDataPropExp *rhs) {
    return cowl_data_prop_equals((CowlDataProp *)lhs, (CowlDataProp *)rhs);
}

cowl_uint cowl_data_prop_exp_hash(CowlDataPropExp *exp) {
    return cowl_data_prop_hash((CowlDataProp *)exp);
}

bool cowl_data_prop_exp_iterate_primitives(CowlDataPropExp *exp, CowlPrimitiveFlags flags,
                                           CowlIterator *iter) {
    return cowl_data_prop_iterate_primitives((CowlDataProp *)exp, flags, iter);
}
