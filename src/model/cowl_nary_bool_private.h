/// @author Ivano Bilenchi

#ifndef COWL_NARY_BOOL_PRIVATE_H
#define COWL_NARY_BOOL_PRIVATE_H

#include "cowl_nary_bool.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlNAryBool) {
    CowlClsExp super;
    CowlClsExpSet *operands;
};

COWL_END_DECLS

#endif // COWL_NARY_BOOL_PRIVATE_H
