/// @author Ivano Bilenchi

#ifndef COWL_INV_OBJ_PROP_H
#define COWL_INV_OBJ_PROP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlObjProp);

cowl_struct_decl(CowlInvObjProp);

CowlInvObjProp* cowl_inv_obj_prop_get(CowlObjProp *prop);
CowlInvObjProp* cowl_inv_obj_prop_retain(CowlInvObjProp *inv);
void cowl_inv_obj_prop_release(CowlInvObjProp *inv);

CowlObjProp* cowl_inv_obj_prop_get_prop(CowlInvObjProp *inv);

bool cowl_inv_obj_prop_equals(CowlInvObjProp *lhs, CowlInvObjProp *rhs);
cowl_uint_t cowl_inv_obj_prop_hash(CowlInvObjProp *inv);

bool cowl_inv_obj_prop_iterate_signature(CowlInvObjProp *inv, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_INV_OBJ_PROP_H
