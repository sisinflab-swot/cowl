/// @author Ivano Bilenchi

#ifndef COWL_INVERSE_OBJ_PROP_H
#define COWL_INVERSE_OBJ_PROP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlObjProp const CowlObjProp;

typedef struct CowlInverseObjProp const CowlInverseObjProp;

CowlInverseObjProp* cowl_inverse_obj_prop_get(CowlObjProp *prop);
CowlInverseObjProp* cowl_inverse_obj_prop_retain(CowlInverseObjProp *inv);
void cowl_inverse_obj_prop_release(CowlInverseObjProp *inv);

CowlObjProp* cowl_inverse_obj_prop_get_prop(CowlInverseObjProp *inv);

bool cowl_inverse_obj_prop_equals(CowlInverseObjProp *lhs, CowlInverseObjProp *rhs);
cowl_uint_t cowl_inverse_obj_prop_hash(CowlInverseObjProp *inv);

bool cowl_inverse_obj_prop_iterate_signature(CowlInverseObjProp *inv,
                                             void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_INVERSE_OBJ_PROP_H
