/// @author Ivano Bilenchi

#include "cowl_obj_compl_private.h"
#include "cowl_hash_utils.h"

static CowlObjCompl* cowl_obj_compl_alloc(CowlClsExp *operand) {
    cowl_uint_t hash = cowl_hash_1(COWL_HASH_INIT_OBJ_COMPL, cowl_cls_exp_hash(operand));

    CowlObjCompl init = {
        .super = COWL_CLS_EXP_INIT(CCET_OBJ_COMPLEMENT, hash),
        .operand = cowl_cls_exp_retain(operand)
    };

    struct CowlObjCompl *compl = malloc(sizeof(*compl));
    memcpy(compl, &init, sizeof(*compl));
    return compl;
}

static void cowl_obj_compl_free(CowlObjCompl *compl) {
    if (!compl) return;
    cowl_cls_exp_release(compl->operand);
    free((void *)compl);
}

CowlObjCompl* cowl_obj_compl_get(CowlClsExp *operand) {
    return cowl_obj_compl_alloc(operand);
}

CowlObjCompl* cowl_obj_compl_retain(CowlObjCompl *compl) {
    return cowl_cls_exp_ref_incr(compl);
}

void cowl_obj_compl_release(CowlObjCompl *compl) {
    if (compl && !cowl_cls_exp_ref_decr(compl)) {
        cowl_obj_compl_free(compl);
    }
}

CowlClsExp* cowl_obj_compl_get_operand(CowlObjCompl *compl) {
    return compl->operand;
}

bool cowl_obj_compl_equals(CowlObjCompl *lhs, CowlObjCompl *rhs) {
    return cowl_cls_exp_equals(lhs->operand, rhs->operand);
}

cowl_uint_t cowl_obj_compl_hash(CowlObjCompl *compl) {
    return cowl_cls_exp_hash_get(compl);
}

bool cowl_obj_compl_iterate_signature(CowlObjCompl *compl, void *ctx, CowlEntityIterator iter) {
    return cowl_cls_exp_iterate_signature(compl->operand, ctx, iter);
}
