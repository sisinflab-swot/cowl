/// @author Ivano Bilenchi

#ifndef COWL_OBJ_INTERSECTION_H
#define COWL_OBJ_INTERSECTION_H

#include "cowl_iterator.h"
#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef khash_struct(CowlClsExpSet) khash_t(CowlClsExpSet);

typedef struct CowlObjIntersection CowlObjIntersection;

khash_t(CowlClsExpSet) const* cowl_obj_intersection_get_operands(CowlObjIntersection const *exp);

bool cowl_obj_intersection_equals(CowlObjIntersection const *lhs, CowlObjIntersection const *rhs);
uint32_t cowl_obj_intersection_hash(CowlObjIntersection const *exp);

bool cowl_obj_intersection_iterate_signature(CowlObjIntersection const *exp,
                                             void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_INTERSECTION_H
