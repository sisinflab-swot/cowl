/// @author Ivano Bilenchi

#ifndef COWL_OBJ_SOME_H
#define COWL_OBJ_SOME_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp const CowlClsExp;
typedef struct CowlObjPropExp const CowlObjPropExp;

typedef struct CowlObjSome const CowlObjSome;

CowlObjSome* cowl_obj_some_get(CowlObjPropExp *prop, CowlClsExp *filler);
CowlObjSome* cowl_obj_some_retain(CowlObjSome *restr);
void cowl_obj_some_release(CowlObjSome *restr);

CowlObjPropExp* cowl_obj_some_get_prop(CowlObjSome *restr);
CowlClsExp* cowl_obj_some_get_filler(CowlObjSome *restr);

bool cowl_obj_some_equals(CowlObjSome *lhs, CowlObjSome *rhs);
uint32_t cowl_obj_some_hash(CowlObjSome *restr);

bool cowl_obj_some_iterate_signature(CowlObjSome *restr, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_SOME_H
