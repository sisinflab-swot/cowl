/// @author Ivano Bilenchi

#include "cowl_obj_union_private.h"
#include "cowl_cls_exp_set.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlObjUnion* cowl_obj_union_alloc(CowlClsExpSet *operands) {
    uint32_t hash = cowl_hash_1(COWL_HASH_INIT_OBJ_UNION,
                                kh_set_hash(CowlClsExpSet, operands));

    CowlObjUnion init = {
        .super = COWL_CLS_EXP_INIT(CCET_OBJ_UNION, hash),
        .operands = operands
    };

    struct CowlObjUnion *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_obj_union_free(CowlObjUnion *exp) {
    if (!exp) return;
    cowl_cls_exp_set_free(exp->operands);
    free((void *)exp);
}

#pragma mark - Public

CowlObjUnion* cowl_obj_union_get(CowlClsExpSet *operands) {
    return cowl_obj_union_alloc(operands);
}

CowlObjUnion* cowl_obj_union_retain(CowlObjUnion *exp) {
    return cowl_cls_exp_ref_incr(exp);
}

void cowl_obj_union_release(CowlObjUnion *exp) {
    if (exp && !cowl_cls_exp_ref_decr(exp)) {
        cowl_obj_union_free(exp);
    }
}

CowlClsExpSet* cowl_obj_union_get_operands(CowlObjUnion *exp) {
    return exp->operands;
}

bool cowl_obj_union_equals(CowlObjUnion *lhs, CowlObjUnion *rhs) {
    return kh_set_equals(CowlClsExpSet, lhs->operands, rhs->operands);
}

uint32_t cowl_obj_union_hash(CowlObjUnion *exp) {
    return cowl_cls_exp_hash_get(exp);
}

bool cowl_obj_union_iterate_signature(CowlObjUnion *exp, void *ctx, CowlEntityIterator iter) {
    kh_foreach_key(exp->operands, CowlClsExp *operand, {
        if (!cowl_cls_exp_iterate_signature(operand, ctx, iter)) return false;
    });
    return true;
}
