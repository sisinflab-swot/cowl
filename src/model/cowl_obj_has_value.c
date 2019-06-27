/// @author Ivano Bilenchi

#include "cowl_obj_has_value_private.h"
#include "cowl_hash_utils.h"
#include "cowl_individual.h"
#include "cowl_obj_prop_exp.h"

static CowlObjHasValue* cowl_obj_has_value_alloc(CowlObjPropExp *prop, CowlIndividual *ind) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_OBJ_HAS_VALUE,
                                   cowl_obj_prop_exp_hash(prop),
                                   cowl_individual_hash(ind));

    CowlObjHasValue init = {
        .super = COWL_CLS_EXP_INIT(CCET_OBJ_HAS_VALUE, hash),
        .prop = cowl_obj_prop_exp_retain(prop),
        .ind = cowl_individual_retain(ind)
    };

    cowl_struct(CowlObjHasValue) *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_obj_has_value_free(CowlObjHasValue *exp) {
    if (!exp) return;
    cowl_obj_prop_exp_release(exp->prop);
    cowl_individual_release(exp->ind);
    free((void *)exp);
}

CowlObjHasValue* cowl_obj_has_value_get(CowlObjPropExp *prop, CowlIndividual *ind) {
    return cowl_obj_has_value_alloc(prop, ind);
}

CowlObjHasValue* cowl_obj_has_value_retain(CowlObjHasValue *exp) {
    return cowl_object_retain(exp);
}

void cowl_obj_has_value_release(CowlObjHasValue *exp) {
    if (exp && !cowl_object_release(exp)) {
        cowl_obj_has_value_free(exp);
    }
}

CowlObjPropExp* cowl_obj_has_value_get_prop(CowlObjHasValue *exp) {
    return exp->prop;
}

CowlIndividual* cowl_obj_has_value_get_ind(CowlObjHasValue *exp) {
    return exp->ind;
}

bool cowl_obj_has_value_equals(CowlObjHasValue *lhs, CowlObjHasValue *rhs) {
    return cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_individual_equals(lhs->ind, rhs->ind);
}

cowl_uint_t cowl_obj_has_value_hash(CowlObjHasValue *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_obj_has_value_iterate_signature(CowlObjHasValue *exp, CowlEntityIterator *iter) {
    if (!cowl_obj_prop_exp_iterate_signature(exp->prop, iter)) return false;
    if (!cowl_individual_iterate_signature(exp->ind, iter)) return false;
    return true;
}