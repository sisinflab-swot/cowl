/// @author Ivano Bilenchi

#ifndef COWL_OBJ_ALL_H
#define COWL_OBJ_ALL_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;
typedef struct CowlObjPropExp CowlObjPropExp;

typedef struct CowlObjAll CowlObjAll;

CowlObjPropExp const* cowl_obj_all_get_prop(CowlObjAll const *restr);
CowlClsExp const* cowl_obj_all_get_filler(CowlObjAll const *restr);

bool cowl_obj_all_enum_signature(CowlObjAll const *restr, void *ctx, CowlEntityIterator iter);

bool cowl_obj_all_equals(CowlObjAll const *lhs, CowlObjAll const *rhs);
uint32_t cowl_obj_all_hash(CowlObjAll const *restr);

COWL_END_DECLS

#endif // COWL_OBJ_ALL_H
