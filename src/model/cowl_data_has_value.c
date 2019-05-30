/// @author Ivano Bilenchi

#include "cowl_data_has_value_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_hash_utils.h"
#include "cowl_literal.h"

static CowlDataHasValue* cowl_data_has_value_alloc(CowlDataPropExp *prop, CowlLiteral *value) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_DATA_HAS_VALUE,
                                   cowl_data_prop_exp_hash(prop),
                                   cowl_literal_hash(value));

    CowlDataHasValue init = {
        .super = COWL_CLS_EXP_INIT(CCET_DATA_HAS_VALUE, hash),
        .prop = cowl_data_prop_exp_retain(prop),
        .value = cowl_literal_retain(value)
    };

    cowl_struct(CowlDataHasValue) *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_data_has_value_free(CowlDataHasValue *exp) {
    if (!exp) return;
    cowl_data_prop_exp_release(exp->prop);
    cowl_literal_release(exp->value);
    free((void *)exp);
}

CowlDataHasValue* cowl_data_has_value_get(CowlDataPropExp *prop, CowlLiteral *value) {
    return cowl_data_has_value_alloc(prop, value);
}

CowlDataHasValue* cowl_data_has_value_retain(CowlDataHasValue *exp) {
    return cowl_cls_exp_ref_incr(exp);
}

void cowl_data_has_value_release(CowlDataHasValue *exp) {
    if (exp && !cowl_cls_exp_ref_decr(exp)) {
        cowl_data_has_value_free(exp);
    }
}

CowlDataPropExp* cowl_data_has_value_get_prop(CowlDataHasValue *exp) {
    return exp->prop;
}

CowlLiteral* cowl_data_has_value_get_value(CowlDataHasValue *exp) {
    return exp->value;
}

bool cowl_data_has_value_equals(CowlDataHasValue *lhs, CowlDataHasValue *rhs) {
    return cowl_data_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_literal_equals(lhs->value, rhs->value);
}

cowl_uint_t cowl_data_has_value_hash(CowlDataHasValue *exp) {
    return cowl_cls_exp_hash_get(exp);
}

bool cowl_data_has_value_iterate_signature(CowlDataHasValue *exp, void *ctx,
                                           CowlEntityIterator iter) {
    if (!cowl_data_prop_exp_iterate_signature(exp->prop, ctx, iter)) return false;
    if (!cowl_literal_iterate_signature(exp->value, ctx, iter)) return false;
    return true;
}
