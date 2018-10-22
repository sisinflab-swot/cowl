/// @author Ivano Bilenchi

#ifndef COWL_OBJ_ALL_H
#define COWL_OBJ_ALL_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp const CowlClsExp;
typedef struct CowlObjPropExp const CowlObjPropExp;

typedef struct CowlObjAll const CowlObjAll;

CowlObjAll* cowl_obj_all_get(CowlObjPropExp *prop, CowlClsExp *filler);
CowlObjAll* cowl_obj_all_retain(CowlObjAll *restr);
void cowl_obj_all_release(CowlObjAll *restr);

CowlObjPropExp* cowl_obj_all_get_prop(CowlObjAll *restr);
CowlClsExp* cowl_obj_all_get_filler(CowlObjAll *restr);

bool cowl_obj_all_equals(CowlObjAll *lhs, CowlObjAll *rhs);
uint32_t cowl_obj_all_hash(CowlObjAll *restr);

bool cowl_obj_all_iterate_signature(CowlObjAll *restr, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_ALL_H
