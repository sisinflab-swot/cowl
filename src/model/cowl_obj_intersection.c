/// @author Ivano Bilenchi

#include "cowl_obj_intersection_private.h"
#include "cowl_cls_exp_set.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlObjIntersection* cowl_obj_intersection_alloc(CowlClsExpSet *operands) {
    uint32_t hash = cowl_hash_1(COWL_HASH_INIT_OBJ_INTERSECTION,
                                kh_set_hash(CowlClsExpSet, operands));

    CowlObjIntersection init = {
        .super = COWL_CLS_EXP_INIT(CCET_OBJ_INTERSECTION, hash),
        .operands = operands
    };

    struct CowlObjIntersection *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_obj_intersection_free(CowlObjIntersection *exp) {
    if (!exp) return;
    cowl_cls_exp_set_free(exp->operands);
    free((void *)exp);
}

#pragma mark - Public

CowlObjIntersection* cowl_obj_intersection_get(CowlClsExpSet *operands) {
    return cowl_obj_intersection_alloc(operands);
}

CowlObjIntersection* cowl_obj_intersection_retain(CowlObjIntersection *exp) {
    return cowl_cls_exp_ref_incr(exp);
}

void cowl_obj_intersection_release(CowlObjIntersection *exp) {
    if (exp && !cowl_cls_exp_ref_decr(exp)) {
        cowl_obj_intersection_free(exp);
    }
}

CowlClsExpSet* cowl_obj_intersection_get_operands(CowlObjIntersection *exp) {
    return exp->operands;
}

bool cowl_obj_intersection_equals(CowlObjIntersection *lhs, CowlObjIntersection *rhs) {
    return kh_set_equals(CowlClsExpSet, lhs->operands, rhs->operands);
}

uint32_t cowl_obj_intersection_hash(CowlObjIntersection *exp) {
    return cowl_cls_exp_hash_get(exp);
}

bool cowl_obj_intersection_iterate_signature(CowlObjIntersection *exp,
                                             void *ctx, CowlEntityIterator iter) {
    kh_foreach_key(exp->operands, CowlClsExp *operand, {
        if (!cowl_cls_exp_iterate_signature(operand, ctx, iter)) return false;
    });
    return true;
}
