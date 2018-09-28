/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXPR_PRIVATE_H
#define COWL_OBJ_PROP_EXPR_PRIVATE_H

#include "cowl_obj_prop_exp.h"
#include "cowl_entity.h"

COWL_BEGIN_DECLS

typedef struct CowlObjPropExp {
    bool is_inverse;
    CowlEntity const *prop;
} CowlObjPropExp;

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXPR_PRIVATE_H
