/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_SET_H
#define COWL_OBJ_PROP_EXP_SET_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlObjPropExp);

UHASH_SET_DECL(CowlObjPropExpSet, CowlObjPropExp*)
cowl_hash_decl(CowlObjPropExpSet);
cowl_hash_decl_mutable(CowlObjPropExpSet, CowlMutableObjPropExpSet);

bool cowl_obj_prop_exp_set_insert(CowlMutableObjPropExpSet *set, CowlObjPropExp *exp);
void cowl_obj_prop_exp_set_free(CowlObjPropExpSet *set);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_SET_H
