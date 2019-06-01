/// @author Ivano Bilenchi

#ifndef COWL_INV_OBJ_PROP_PRIVATE_H
#define COWL_INV_OBJ_PROP_PRIVATE_H

#include "cowl_inv_obj_prop.h"
#include "cowl_obj_prop_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlInvObjProp) {
    CowlObjPropExp super;
    CowlObjProp *prop;
};

COWL_END_DECLS

#endif // COWL_INV_OBJ_PROP_PRIVATE_H
