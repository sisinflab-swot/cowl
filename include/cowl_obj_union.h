/// @author Ivano Bilenchi

#ifndef COWL_OBJ_UNION_H
#define COWL_OBJ_UNION_H

#include "cowl_iterator.h"
#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef khash_struct(CowlClsExpSet) const CowlClsExpSet;

typedef struct CowlObjUnion const CowlObjUnion;

CowlObjUnion* cowl_obj_union_get(CowlClsExpSet *operands);
CowlObjUnion* cowl_obj_union_retain(CowlObjUnion *exp);
void cowl_obj_union_release(CowlObjUnion *exp);

CowlClsExpSet* cowl_obj_union_get_operands(CowlObjUnion *exp);

bool cowl_obj_union_equals(CowlObjUnion *lhs, CowlObjUnion *rhs);
uint32_t cowl_obj_union_hash(CowlObjUnion *exp);

bool cowl_obj_union_iterate_signature(CowlObjUnion *exp, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_UNION_H
