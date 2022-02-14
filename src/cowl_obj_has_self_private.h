/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_HAS_SELF_PRIVATE_H
#define COWL_OBJ_HAS_SELF_PRIVATE_H

#include "cowl_obj_has_self.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

struct CowlObjHasSelf {
    CowlClsExp super;
    CowlObjPropExp *prop;
};

COWL_END_DECLS

#endif // COWL_OBJ_HAS_SELF_PRIVATE_H
