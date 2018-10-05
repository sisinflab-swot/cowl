/// @author Ivano Bilenchi

#include "cowl_obj_compl_private.h"
#include "cowl_hash_utils.h"

CowlClsExp const* cowl_obj_compl_get_operand(CowlObjCompl const *compl) {
    return compl->operand;
}

bool cowl_obj_compl_equals(CowlObjCompl const *lhs, CowlObjCompl const *rhs) {
    return cowl_cls_exp_equals(lhs->operand, rhs->operand);
}

uint32_t cowl_obj_compl_hash(CowlObjCompl const *compl) {
    return cowl_hash_1(COWL_HASH_INIT_OBJ_COMPL, cowl_cls_exp_hash(compl->operand));
}

bool cowl_obj_compl_iterate_signature(CowlObjCompl const *compl,
                                      void *ctx, CowlEntityIterator iter) {
    return cowl_cls_exp_iterate_signature(compl->operand, ctx, iter);
}
