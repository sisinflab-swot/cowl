/// @author Ivano Bilenchi

#include "cowl_obj_intersection_private.h"
#include "cowl_cls_exp_set.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlObjIntersection* cowl_obj_intersection_alloc(khash_t(CowlClsExpSet) const *operands) {
    uint32_t hash = cowl_hash_1(COWL_HASH_INIT_OBJ_INTERSECTION,
                                kh_set_hash(CowlClsExpSet, operands));

    CowlObjIntersection init = {
        .super = COWL_CLS_EXP_INIT(CCET_OBJ_INTERSECTION, hash),
        .operands = operands
    };

    CowlObjIntersection *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_obj_intersection_free(CowlObjIntersection const *exp) {
    if (!exp) return;
    cowl_cls_exp_set_free(exp->operands);
    free((void *)exp);
}

#pragma mark - Public

CowlObjIntersection const* cowl_obj_intersection_get(khash_t(CowlClsExpSet) const *operands) {
    return cowl_obj_intersection_alloc(operands);
}

CowlObjIntersection const* cowl_obj_intersection_retain(CowlObjIntersection const *exp) {
    return cowl_cls_exp_ref_incr(exp);
}

void cowl_obj_intersection_release(CowlObjIntersection const *exp) {
    if (exp && !cowl_cls_exp_ref_decr(exp)) {
        cowl_obj_intersection_free(exp);
    }
}

khash_t(CowlClsExpSet) const* cowl_obj_intersection_get_operands(CowlObjIntersection const *exp) {
    return exp->operands;
}

bool cowl_obj_intersection_equals(CowlObjIntersection const *lhs, CowlObjIntersection const *rhs) {
    return kh_set_equals(CowlClsExpSet, lhs->operands, rhs->operands);
}

uint32_t cowl_obj_intersection_hash(CowlObjIntersection const *exp) {
    return cowl_cls_exp_hash_get(exp);
}

bool cowl_obj_intersection_iterate_signature(CowlObjIntersection const *exp,
                                             void *ctx, CowlEntityIterator iter) {
    kh_foreach_key(exp->operands, CowlClsExp const *operand, {
        if (!cowl_cls_exp_iterate_signature(operand, ctx, iter)) return false;
    });
    return true;
}
