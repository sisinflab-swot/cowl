/// @author Ivano Bilenchi

#include "cowl_obj_one_of_private.h"
#include "cowl_hash_utils.h"
#include "cowl_individual.h"
#include "cowl_individual_set.h"

static CowlObjOneOf* cowl_obj_one_of_alloc(CowlIndividualSet *inds) {
    cowl_uint_t hash = cowl_hash_1(COWL_HASH_INIT_OBJECT_ONE_OF,
                                   uhset_hash(CowlIndividualSet, inds));

    CowlObjOneOf init = {
        .super = COWL_CLS_EXP_INIT(CCET_OBJ_ONE_OF, hash),
        .inds = inds
    };

    cowl_struct(CowlObjOneOf) *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_obj_one_of_free(CowlObjOneOf *exp) {
    if (!exp) return;
    cowl_individual_set_free(exp->inds);
    free((void *)exp);
}

CowlObjOneOf* cowl_obj_one_of_get(CowlIndividualSet *inds) {
    return cowl_obj_one_of_alloc(inds);
}

CowlObjOneOf* cowl_obj_one_of_retain(CowlObjOneOf *exp) {
    return cowl_object_retain(exp);
}

void cowl_obj_one_of_release(CowlObjOneOf *exp) {
    if (exp && !cowl_object_release(exp)) {
        cowl_obj_one_of_free(exp);
    }
}

CowlIndividualSet* cowl_obj_one_of_get_inds(CowlObjOneOf *exp) {
    return exp->inds;
}

bool cowl_obj_one_of_equals(CowlObjOneOf *lhs, CowlObjOneOf *rhs) {
    return uhset_equals(CowlIndividualSet, lhs->inds, rhs->inds);
}

cowl_uint_t cowl_obj_one_of_hash(CowlObjOneOf *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_obj_one_of_iterate_signature(CowlObjOneOf *exp, void *ctx, CowlEntityIterator iter) {
    uhash_foreach_key(CowlIndividualSet, exp->inds, ind, {
        if (!cowl_individual_iterate_signature(ind, ctx, iter)) return false;
    });
    return true;
}
