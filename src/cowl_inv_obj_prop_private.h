/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INV_OBJ_PROP_PRIVATE_H
#define COWL_INV_OBJ_PROP_PRIVATE_H

#include "cowl_inv_obj_prop.h"
#include "cowl_obj_prop_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlInvObjProp) {
    CowlObjPropExp super;
    CowlObjProp *prop;
};

cowl_ret_t cowl_inv_obj_prop_api_init(void);
void cowl_inv_obj_prop_api_deinit(void);

COWL_END_DECLS

#endif // COWL_INV_OBJ_PROP_PRIVATE_H
