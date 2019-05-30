/// @author Ivano Bilenchi

#include "cowl_obj_one_of_private.h"
#include "cowl_hash_utils.h"
#include "cowl_individual.h"
#include "cowl_individual_set.h"

static CowlObjOneOf* cowl_obj_one_of_alloc(CowlIndividualSet *individuals) {
    cowl_uint_t hash = cowl_hash_1(COWL_HASH_INIT_OBJECT_ONE_OF,
                                   uhset_hash(CowlIndividualSet, individuals));

    CowlObjOneOf init = {
        .super = COWL_CLS_EXP_INIT(CCET_OBJ_ONE_OF, hash),
        .individuals = individuals
    };

    cowl_struct(CowlObjOneOf) *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_obj_one_of_free(CowlObjOneOf *exp) {
    if (!exp) return;
    cowl_individual_set_free(exp->individuals);
    free((void *)exp);
}

CowlObjOneOf* cowl_obj_one_of_get(CowlIndividualSet *individuals) {
    return cowl_obj_one_of_alloc(individuals);
}

CowlObjOneOf* cowl_obj_one_of_retain(CowlObjOneOf *exp) {
    return cowl_cls_exp_ref_incr(exp);
}

void cowl_obj_one_of_release(CowlObjOneOf *exp) {
    if (exp && !cowl_cls_exp_ref_decr(exp)) {
        cowl_obj_one_of_free(exp);
    }
}

CowlIndividualSet* cowl_obj_one_of_get_individuals(CowlObjOneOf *exp) {
    return exp->individuals;
}

bool cowl_obj_one_of_equals(CowlObjOneOf *lhs, CowlObjOneOf *rhs) {
    return uhset_equals(CowlIndividualSet, lhs->individuals, rhs->individuals);
}

cowl_uint_t cowl_obj_one_of_hash(CowlObjOneOf *exp) {
    return cowl_cls_exp_hash_get(exp);
}

bool cowl_obj_one_of_iterate_signature(CowlObjOneOf *exp, void *ctx, CowlEntityIterator iter) {
    uhash_foreach_key(CowlIndividualSet, exp->individuals, individual, {
        if (!cowl_individual_iterate_signature(individual, ctx, iter)) return false;
    });
    return true;
}
