/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_SET_PRIVATE_H
#define COWL_OBJ_PROP_EXP_SET_PRIVATE_H

#include "cowl_obj_prop_exp_set.h"

COWL_BEGIN_DECLS

cowl_hash_decl_mutable(CowlObjPropExpSet, CowlMutableObjPropExpSet);

bool cowl_obj_prop_exp_set_insert(CowlMutableObjPropExpSet *set, CowlObjPropExp *exp);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_SET_PRIVATE_H
