/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_SET_H
#define COWL_OBJ_PROP_EXP_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlObjPropExp);

UHASH_SET_DECL(CowlObjPropExpSet, CowlObjPropExp*)
cowl_hash_decl(CowlObjPropExpSet);

void cowl_obj_prop_exp_set_free(CowlObjPropExpSet *set);

bool cowl_obj_prop_exp_set_equals(CowlObjPropExpSet *lhs, CowlObjPropExpSet *rhs);
cowl_uint_t cowl_obj_prop_exp_set_hash(CowlObjPropExpSet *set);

bool cowl_obj_prop_exp_set_iterate_signature(CowlObjPropExpSet *set, void *ctx,
                                             CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_SET_H
