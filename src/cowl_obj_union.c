/// @author Ivano Bilenchi

#include "cowl_obj_union_private.h"
#include "cowl_hash_utils.h"

khash_t(CowlClsExpSet) const* cowl_obj_union_get_operands(CowlObjUnion const *exp) {
    return exp->operands;
}

bool cowl_obj_union_equals(CowlObjUnion const *lhs, CowlObjUnion const *rhs) {
    return kh_set_equals(CowlClsExpSet, lhs->operands, rhs->operands);
}

uint32_t cowl_obj_union_hash(CowlObjUnion const *exp) {
    return cowl_hash_1(COWL_HASH_INIT_OBJ_UNION, kh_set_hash(CowlClsExpSet, exp->operands));
}
