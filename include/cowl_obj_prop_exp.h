/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_H
#define COWL_OBJ_PROP_EXP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlObjPropExp CowlObjPropExp;

CowlObjPropExp const* cowl_obj_prop_exp_retain(CowlObjPropExp const *prop);
void cowl_obj_prop_exp_release(CowlObjPropExp const *prop);

bool cowl_obj_prop_exp_is_inverse(CowlObjPropExp const *exp);

bool cowl_obj_prop_exp_equals(CowlObjPropExp const *lhs, CowlObjPropExp const *rhs);
uint32_t cowl_obj_prop_exp_hash(CowlObjPropExp const *exp);

bool cowl_obj_prop_exp_iterate_signature(CowlObjPropExp const *exp,
                                         void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_H
