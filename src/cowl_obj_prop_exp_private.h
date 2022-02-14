/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_EXP_PRIVATE_H
#define COWL_OBJ_PROP_EXP_PRIVATE_H

#include "cowl_obj_prop_exp.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

struct CowlObjPropExp {
    CowlObject super;
};

#define COWL_OBJ_PROP_EXP_INIT(I) {                                                                 \
    .super = COWL_OBJECT_INIT((I) ? COWL_OT_OPE_INV_OBJ_PROP : COWL_OT_OPE_OBJ_PROP)                \
}

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_PRIVATE_H
