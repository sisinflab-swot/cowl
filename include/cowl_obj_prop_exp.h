/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_H
#define COWL_OBJ_PROP_EXP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlObjProp const CowlObjProp;

typedef struct CowlObjPropExp const CowlObjPropExp;

CowlObjPropExp* cowl_obj_prop_exp_retain(CowlObjPropExp *prop);
void cowl_obj_prop_exp_release(CowlObjPropExp *prop);

bool cowl_obj_prop_exp_is_inverse(CowlObjPropExp *exp);
CowlObjProp* cowl_obj_prop_exp_get_prop(CowlObjPropExp *exp);

bool cowl_obj_prop_exp_equals(CowlObjPropExp *lhs, CowlObjPropExp *rhs);
cowl_uint_t cowl_obj_prop_exp_hash(CowlObjPropExp *exp);

bool cowl_obj_prop_exp_iterate_signature(CowlObjPropExp *exp,
                                         void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_H
