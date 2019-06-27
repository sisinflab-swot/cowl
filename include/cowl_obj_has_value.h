/// @author Ivano Bilenchi

#ifndef COWL_OBJ_HAS_VALUE_H
#define COWL_OBJ_HAS_VALUE_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlObjPropExp);

cowl_struct_decl(CowlObjHasValue);

CowlObjHasValue* cowl_obj_has_value_get(CowlObjPropExp *prop, CowlIndividual *individual);
CowlObjHasValue* cowl_obj_has_value_retain(CowlObjHasValue *exp);
void cowl_obj_has_value_release(CowlObjHasValue *exp);

CowlObjPropExp* cowl_obj_has_value_get_prop(CowlObjHasValue *exp);
CowlIndividual* cowl_obj_has_value_get_individual(CowlObjHasValue *exp);

bool cowl_obj_has_value_equals(CowlObjHasValue *lhs, CowlObjHasValue *rhs);
cowl_uint_t cowl_obj_has_value_hash(CowlObjHasValue *exp);

bool cowl_obj_has_value_iterate_signature(CowlObjHasValue *exp, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_HAS_VALUE_H
