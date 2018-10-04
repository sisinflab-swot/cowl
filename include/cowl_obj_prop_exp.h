/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_H
#define COWL_OBJ_PROP_EXP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlObjPropExp CowlObjPropExp;

bool cowl_obj_prop_exp_is_inverse(CowlObjPropExp const *exp);

bool cowl_obj_prop_exp_enum_signature(CowlObjPropExp const *exp, void *ctx,
                                      CowlEntityIterator iter);

bool cowl_obj_prop_exp_equals(CowlObjPropExp const *lhs, CowlObjPropExp const *rhs);
uint32_t cowl_obj_prop_exp_hash(CowlObjPropExp const *exp);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_H
