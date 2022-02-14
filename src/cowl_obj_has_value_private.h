/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_HAS_VALUE_PRIVATE_H
#define COWL_OBJ_HAS_VALUE_PRIVATE_H

#include "cowl_obj_has_value.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

struct CowlObjHasValue {
    CowlClsExp super;
    CowlObjPropExp *prop;
    CowlIndividual *ind;
};

COWL_END_DECLS

#endif // COWL_OBJ_HAS_VALUE_PRIVATE_H
