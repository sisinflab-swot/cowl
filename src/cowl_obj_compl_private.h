/// @author Ivano Bilenchi

#ifndef COWL_OBJ_COMPL_PRIVATE_H
#define COWL_OBJ_COMPL_PRIVATE_H

#include "cowl_obj_compl.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

typedef struct CowlObjCompl {
    CowlClsExp super;
    CowlClsExp const *operand;
} CowlObjCompl;

COWL_END_DECLS

#endif // COWL_OBJ_COMPL_PRIVATE_H
