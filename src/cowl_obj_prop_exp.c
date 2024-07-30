/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_exp.h"
#include "cowl_any.h"
#include "cowl_inv_obj_prop.h"

CowlObjProp *cowl_obj_prop_exp_get_prop(CowlAnyObjPropExp *exp) {
    return cowl_obj_prop_exp_is_inverse(exp) ? cowl_inv_obj_prop_get_prop(exp) : exp;
}
