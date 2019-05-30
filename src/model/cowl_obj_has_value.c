/// @author Ivano Bilenchi

#include "cowl_obj_has_value_private.h"
#include "cowl_hash_utils.h"
#include "cowl_individual.h"
#include "cowl_obj_prop_exp.h"

static CowlObjHasValue* cowl_obj_has_value_alloc(CowlObjPropExp *prop, CowlIndividual *individual) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_OBJ_HAS_VALUE,
                                   cowl_obj_prop_exp_hash(prop),
                                   cowl_individual_hash(individual));

    CowlObjHasValue init = {
        .super = COWL_CLS_EXP_INIT(CCET_OBJ_HAS_VALUE, hash),
        .prop = cowl_obj_prop_exp_retain(prop),
        .individual = cowl_individual_retain(individual)
    };

    cowl_struct(CowlObjHasValue) *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_obj_has_value_free(CowlObjHasValue *exp) {
    if (!exp) return;
    cowl_obj_prop_exp_release(exp->prop);
    cowl_individual_release(exp->individual);
    free((void *)exp);
}

CowlObjHasValue* cowl_obj_has_value_get(CowlObjPropExp *prop, CowlIndividual *individual) {
    return cowl_obj_has_value_alloc(prop, individual);
}

CowlObjHasValue* cowl_obj_has_value_retain(CowlObjHasValue *exp) {
    return cowl_cls_exp_ref_incr(exp);
}

void cowl_obj_has_value_release(CowlObjHasValue *exp) {
    if (exp && !cowl_cls_exp_ref_decr(exp)) {
        cowl_obj_has_value_free(exp);
    }
}

CowlObjPropExp* cowl_obj_has_value_get_prop(CowlObjHasValue *exp) {
    return exp->prop;
}

CowlIndividual* cowl_obj_has_value_get_individual(CowlObjHasValue *exp) {
    return exp->individual;
}

bool cowl_obj_has_value_equals(CowlObjHasValue *lhs, CowlObjHasValue *rhs) {
    return cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_individual_equals(lhs->individual, rhs->individual);
}

cowl_uint_t cowl_obj_has_value_hash(CowlObjHasValue *exp) {
    return cowl_cls_exp_hash_get(exp);
}

bool cowl_obj_has_value_iterate_signature(CowlObjHasValue *exp, void *ctx,
                                          CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_iterate_signature(exp->prop, ctx, iter)) return false;
    if (!cowl_individual_iterate_signature(exp->individual, ctx, iter)) return false;
    return true;
}