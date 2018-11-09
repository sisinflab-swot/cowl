/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_SET_H
#define COWL_OBJ_PROP_EXP_SET_H

#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef struct CowlObjPropExp const CowlObjPropExp;

KHASH_SET_UTILS_DECL(CowlObjPropExpSet, CowlObjPropExp*);
typedef khash_struct(CowlObjPropExpSet) const CowlObjPropExpSet;
typedef khash_struct(CowlObjPropExpSet) CowlMutableObjPropExpSet;

bool cowl_obj_prop_exp_set_insert(CowlMutableObjPropExpSet *set, CowlObjPropExp *exp);
void cowl_obj_prop_exp_set_free(CowlObjPropExpSet *set);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_SET_H
