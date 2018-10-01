/// @author Ivano Bilenchi

#ifndef COWL_OBJ_UNION_PRIVATE_H
#define COWL_OBJ_UNION_PRIVATE_H

#include "cowl_obj_union.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

typedef struct CowlObjUnion {
    CowlClsExp super;
    khash_t(CowlClsExpSet) const *operands;
} CowlObjUnion;

COWL_END_DECLS

#endif // COWL_OBJ_UNION_PRIVATE_H
