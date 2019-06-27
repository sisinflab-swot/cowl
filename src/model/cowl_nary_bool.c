/// @author Ivano Bilenchi

#include "cowl_nary_bool_private.h"
#include "cowl_cls_exp_set.h"
#include "cowl_hash_utils.h"

static CowlNAryBool* cowl_nary_bool_alloc(CowlClsExpType type, CowlClsExpSet *operands) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_NARY_BOOL, type,
                                   uhset_hash(CowlClsExpSet, operands));

    CowlNAryBool init = {
        .super = COWL_CLS_EXP_INIT(type, hash),
        .operands = operands
    };

    cowl_struct(CowlNAryBool) *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_nary_bool_free(CowlNAryBool *exp) {
    if (!exp) return;
    cowl_cls_exp_set_free(exp->operands);
    free((void *)exp);
}

CowlNAryBool* cowl_nary_bool_get(CowlNAryType type, CowlClsExpSet *operands) {
    return cowl_nary_bool_alloc((CowlClsExpType)type + CCET_OBJ_INTERSECTION, operands);
}

CowlNAryBool* cowl_nary_bool_retain(CowlNAryBool *exp) {
    return cowl_object_retain(exp);
}

void cowl_nary_bool_release(CowlNAryBool *exp) {
    if (exp && !cowl_object_release(exp)) {
        cowl_nary_bool_free(exp);
    }
}

CowlNAryType cowl_nary_bool_get_type(CowlNAryBool *exp) {
    return (CowlNAryType)(exp->super.type - CCET_OBJ_INTERSECTION);
}

CowlClsExpSet* cowl_nary_bool_get_operands(CowlNAryBool *exp) {
    return exp->operands;
}

bool cowl_nary_bool_equals(CowlNAryBool *lhs, CowlNAryBool *rhs) {
    return (lhs->super.type == rhs->super.type &&
            uhset_equals(CowlClsExpSet, lhs->operands, rhs->operands));
}

cowl_uint_t cowl_nary_bool_hash(CowlNAryBool *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_nary_bool_iterate_signature(CowlNAryBool *exp, CowlEntityIterator *iter) {
    return cowl_cls_exp_set_iterate_signature(exp->operands, iter);
}
