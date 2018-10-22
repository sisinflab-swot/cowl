/// @author Ivano Bilenchi

#ifndef COWL_OBJ_INTERSECTION_H
#define COWL_OBJ_INTERSECTION_H

#include "cowl_iterator.h"
#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef khash_struct(CowlClsExpSet) const CowlClsExpSet;

typedef struct CowlObjIntersection const CowlObjIntersection;

CowlObjIntersection* cowl_obj_intersection_get(CowlClsExpSet *operands);
CowlObjIntersection* cowl_obj_intersection_retain(CowlObjIntersection *exp);
void cowl_obj_intersection_release(CowlObjIntersection *exp);

CowlClsExpSet* cowl_obj_intersection_get_operands(CowlObjIntersection *exp);

bool cowl_obj_intersection_equals(CowlObjIntersection *lhs, CowlObjIntersection *rhs);
uint32_t cowl_obj_intersection_hash(CowlObjIntersection *exp);

bool cowl_obj_intersection_iterate_signature(CowlObjIntersection *exp,
                                             void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_INTERSECTION_H
