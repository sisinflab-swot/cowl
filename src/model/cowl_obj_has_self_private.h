/// @author Ivano Bilenchi

#ifndef COWL_OBJ_HAS_SELF_PRIVATE_H
#define COWL_OBJ_HAS_SELF_PRIVATE_H

#include "cowl_obj_has_self.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlObjHasSelf) {
    CowlClsExp super;
    CowlObjPropExp *prop;
};

COWL_END_DECLS

#endif // COWL_OBJ_HAS_SELF_PRIVATE_H
