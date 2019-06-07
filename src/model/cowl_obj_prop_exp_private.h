/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_PRIVATE_H
#define COWL_OBJ_PROP_EXP_PRIVATE_H

#include "cowl_obj_prop_exp.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlObjPropExp) {
    CowlObject super;
    bool is_inverse;
};

#define COWL_OBJ_PROP_EXP_INIT(I) { .super = COWL_OBJECT_INIT, .is_inverse = (I) }

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_PRIVATE_H
