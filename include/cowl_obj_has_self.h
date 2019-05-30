/// @author Ivano Bilenchi

#ifndef COWL_OBJ_HAS_SELF_H
#define COWL_OBJ_HAS_SELF_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlObjPropExp);

cowl_struct_decl(CowlObjHasSelf);

CowlObjHasSelf* cowl_obj_has_self_get(CowlObjPropExp *prop);
CowlObjHasSelf* cowl_obj_has_self_retain(CowlObjHasSelf *exp);
void cowl_obj_has_self_release(CowlObjHasSelf *exp);

CowlObjPropExp* cowl_obj_has_self_get_prop(CowlObjHasSelf *exp);

bool cowl_obj_has_self_equals(CowlObjHasSelf *lhs, CowlObjHasSelf *rhs);
cowl_uint_t cowl_obj_has_self_hash(CowlObjHasSelf *exp);

bool cowl_obj_has_self_iterate_signature(CowlObjHasSelf *exp, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_HAS_SELF_H
