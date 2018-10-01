/// @author Ivano Bilenchi

#ifndef COWL_INVERSE_OBJ_PROP_H
#define COWL_INVERSE_OBJ_PROP_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlObjProp CowlObjProp;

typedef struct CowlInverseObjProp CowlInverseObjProp;

CowlObjProp const* cowl_inverse_obj_prop_get_prop(CowlInverseObjProp const *inv);

bool cowl_inverse_obj_prop_equals(CowlInverseObjProp const *lhs, CowlInverseObjProp const *rhs);
uint32_t cowl_inverse_obj_prop_hash(CowlInverseObjProp const *inv);

COWL_END_DECLS

#endif // COWL_INVERSE_OBJ_PROP_H
