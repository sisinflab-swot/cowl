/// @author Ivano Bilenchi

#ifndef COWL_OBJ_SOME_H
#define COWL_OBJ_SOME_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;
typedef struct CowlObjPropExp CowlObjPropExp;

typedef struct CowlObjSome CowlObjSome;

CowlObjPropExp const* cowl_obj_some_get_prop(CowlObjSome const *restr);
CowlClsExp const* cowl_obj_some_get_filler(CowlObjSome const *restr);

bool cowl_obj_some_equals(CowlObjSome const *lhs, CowlObjSome const *rhs);
uint32_t cowl_obj_some_hash(CowlObjSome const *restr);

bool cowl_obj_some_iterate_signature(CowlObjSome const *restr, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_SOME_H
