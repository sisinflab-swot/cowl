/// @author Ivano Bilenchi

#include "cowl_nary_bool_private.h"
#include "cowl_cls_exp_set.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlNAryBool* cowl_nary_bool_alloc(CowlClsExpType type, CowlClsExpSet *operands) {
    uint32_t hash = cowl_hash_2(COWL_HASH_INIT_NARY_BOOL, type,
                                kh_set_hash(CowlClsExpSet, operands));

    CowlNAryBool init = {
        .super = COWL_CLS_EXP_INIT(type, hash),
        .operands = operands
    };

    struct CowlNAryBool *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_nary_bool_free(CowlNAryBool *exp) {
    if (!exp) return;
    cowl_cls_exp_set_free(exp->operands);
    free((void *)exp);
}

#pragma mark - Public

CowlNAryBool* cowl_nary_bool_get(CowlNAryBoolType type, CowlClsExpSet *operands) {
    return cowl_nary_bool_alloc(type + CCET_OBJ_INTERSECTION, operands);
}

CowlNAryBool* cowl_nary_bool_retain(CowlNAryBool *exp) {
    return cowl_cls_exp_ref_incr(exp);
}

void cowl_nary_bool_release(CowlNAryBool *exp) {
    if (exp && !cowl_cls_exp_ref_decr(exp)) {
        cowl_nary_bool_free(exp);
    }
}

CowlNAryBoolType cowl_nary_bool_get_type(CowlNAryBool *exp) {
    return exp->super.type - CCET_OBJ_INTERSECTION;
}

CowlClsExpSet* cowl_nary_bool_get_operands(CowlNAryBool *exp) {
    return exp->operands;
}

bool cowl_nary_bool_equals(CowlNAryBool *lhs, CowlNAryBool *rhs) {
    return lhs->super.type == rhs->super.type &&
           kh_set_equals(CowlClsExpSet, lhs->operands, rhs->operands);
}

uint32_t cowl_nary_bool_hash(CowlNAryBool *exp) {
    return cowl_cls_exp_hash_get(exp);
}

bool cowl_nary_bool_iterate_signature(CowlNAryBool *exp,
                                      void *ctx, CowlEntityIterator iter) {
    kh_foreach_key(exp->operands, CowlClsExp *operand, {
        if (!cowl_cls_exp_iterate_signature(operand, ctx, iter)) return false;
    });
    return true;
}
