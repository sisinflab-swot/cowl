/// @author Ivano Bilenchi

#ifndef COWL_INVERSE_OBJ_PROP_PRIVATE_H
#define COWL_INVERSE_OBJ_PROP_PRIVATE_H

#include "cowl_inverse_obj_prop.h"
#include "cowl_obj_prop_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlInverseObjProp) {
    CowlObjPropExp super;
    CowlObjProp *prop;
};

COWL_END_DECLS

#endif // COWL_INVERSE_OBJ_PROP_PRIVATE_H
