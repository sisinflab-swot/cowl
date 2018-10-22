/// @author Ivano Bilenchi

#ifndef COWL_OBJ_SOME_PRIVATE_H
#define COWL_OBJ_SOME_PRIVATE_H

#include "cowl_obj_some.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

typedef struct CowlObjSome {
    CowlClsExp super;
    CowlObjPropExp const *prop;
    CowlClsExp const *filler;
} CowlObjSome;

COWL_END_DECLS

#endif // COWL_OBJ_SOME_PRIVATE_H