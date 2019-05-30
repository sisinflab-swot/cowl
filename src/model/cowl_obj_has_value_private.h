/// @author Ivano Bilenchi

#ifndef COWL_OBJ_HAS_VALUE_PRIVATE_H
#define COWL_OBJ_HAS_VALUE_PRIVATE_H

#include "cowl_obj_has_value.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlObjHasValue) {
    CowlClsExp super;
    CowlObjPropExp *prop;
    CowlIndividual *individual;
};

COWL_END_DECLS

#endif // COWL_OBJ_HAS_VALUE_PRIVATE_H
