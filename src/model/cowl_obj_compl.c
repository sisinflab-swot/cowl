/// @author Ivano Bilenchi

#include "cowl_obj_compl_private.h"
#include "cowl_hash_utils.h"

static CowlObjCompl* cowl_obj_compl_alloc(CowlClsExp *operand) {
    cowl_uint_t hash = cowl_hash_1(COWL_HASH_INIT_OBJ_COMPL, cowl_cls_exp_hash(operand));

    CowlObjCompl init = {
        .super = COWL_CLS_EXP_INIT(COWL_CET_OBJ_COMPL, hash),
        .operand = cowl_cls_exp_retain(operand)
    };

    cowl_struct(CowlObjCompl) *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_obj_compl_free(CowlObjCompl *exp) {
    if (!exp) return;
    cowl_cls_exp_release(exp->operand);
    free((void *)exp);
}

CowlObjCompl* cowl_obj_compl_get(CowlClsExp *operand) {
    return cowl_obj_compl_alloc(operand);
}

CowlObjCompl* cowl_obj_compl_retain(CowlObjCompl *exp) {
    return cowl_object_retain(exp);
}

void cowl_obj_compl_release(CowlObjCompl *exp) {
    if (exp && !cowl_object_release(exp)) {
        cowl_obj_compl_free(exp);
    }
}

CowlClsExp* cowl_obj_compl_get_operand(CowlObjCompl *exp) {
    return exp->operand;
}

bool cowl_obj_compl_equals(CowlObjCompl *lhs, CowlObjCompl *rhs) {
    return cowl_cls_exp_equals(lhs->operand, rhs->operand);
}

cowl_uint_t cowl_obj_compl_hash(CowlObjCompl *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_obj_compl_iterate_signature(CowlObjCompl *exp, CowlEntityIterator *iter) {
    return cowl_cls_exp_iterate_signature(exp->operand, iter);
}
