/// @author Ivano Bilenchi

#include "cowl_obj_compl_private.h"
#include "cowl_hash_utils.h"

CowlClsExp const* cowl_obj_compl_get_operand(CowlObjCompl const *complement) {
    return complement->operand;
}

bool cowl_obj_compl_equals(CowlObjCompl const *lhs, CowlObjCompl const *rhs) {
    return cowl_cls_exp_equals(lhs->operand, rhs->operand);
}

uint32_t cowl_obj_compl_hash(CowlObjCompl const *complement) {
    return cowl_hash_1(COWL_HASH_INIT_OBJ_COMPL, cowl_cls_exp_hash(complement->operand));
}
