/// @author Ivano Bilenchi

#ifndef COWL_OBJ_ONE_OF_PRIVATE_H
#define COWL_OBJ_ONE_OF_PRIVATE_H

#include "cowl_obj_one_of.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlObjOneOf) {
    CowlClsExp super;
    CowlIndividualSet *individuals;
};

COWL_END_DECLS

#endif // COWL_OBJ_ONE_OF_PRIVATE_H
