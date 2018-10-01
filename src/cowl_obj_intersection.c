/// @author Ivano Bilenchi

#include "cowl_obj_intersection_private.h"
#include "cowl_hash_utils.h"

khash_t(CowlClsExpSet) const* cowl_obj_intersection_get_operands(CowlObjIntersection const *exp) {
    return exp->operands;
}

bool cowl_obj_intersection_equals(CowlObjIntersection const *lhs, CowlObjIntersection const *rhs) {
    return kh_set_equals(CowlClsExpSet, lhs->operands, rhs->operands);
}

uint32_t cowl_obj_intersection_hash(CowlObjIntersection const *exp) {
    return cowl_hash_1(COWL_HASH_INIT_OBJ_INTERSECTION, kh_set_hash(CowlClsExpSet, exp->operands));
}
