/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXPR_H
#define COWL_OBJ_PROP_EXPR_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlEntity CowlEntity;

typedef struct CowlObjPropExp CowlObjPropExp;

CowlEntity const* cowl_obj_prop_exp_property(CowlObjPropExp const *exp);
bool cowl_obj_prop_exp_is_inverse(CowlObjPropExp const *exp);

bool cowl_obj_prop_exp_equals(CowlObjPropExp const *a, CowlObjPropExp const *b);
uint32_t cowl_obj_prop_exp_hash(CowlObjPropExp const *exp);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXPR_H
