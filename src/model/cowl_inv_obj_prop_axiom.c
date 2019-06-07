/// @author Ivano Bilenchi

#include "cowl_inv_obj_prop_axiom_private.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"

static CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_alloc(CowlObjPropExp *first,
                                                          CowlObjPropExp *second) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_INV_OBJ_PROP_AXIOM,
                                   cowl_obj_prop_exp_hash(first),
                                   cowl_obj_prop_exp_hash(second));

    CowlInvObjPropAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_INVERSE_OBJ_PROP, hash),
        .first = cowl_obj_prop_exp_retain(first),
        .second = cowl_obj_prop_exp_retain(second)
    };

    cowl_struct(CowlInvObjPropAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_inv_obj_prop_axiom_free(CowlInvObjPropAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_release(axiom->first);
    cowl_obj_prop_exp_release(axiom->second);
    free((void *)axiom);
}

CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_get(CowlObjPropExp *first, CowlObjPropExp *second) {
    return cowl_inv_obj_prop_axiom_alloc(first, second);
}

CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_retain(CowlInvObjPropAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_inv_obj_prop_axiom_release(CowlInvObjPropAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_inv_obj_prop_axiom_free(axiom);
    }
}

CowlObjPropExp* cowl_inv_obj_prop_axiom_get_first_prop(CowlInvObjPropAxiom *axiom) {
    return axiom->first;
}

CowlObjPropExp* cowl_inv_obj_prop_axiom_get_second_prop(CowlInvObjPropAxiom *axiom) {
    return axiom->second;
}

bool cowl_inv_obj_prop_axiom_equals(CowlInvObjPropAxiom *lhs, CowlInvObjPropAxiom *rhs) {
    return cowl_obj_prop_exp_equals(lhs->first, rhs->first) &&
           cowl_obj_prop_exp_equals(lhs->second, rhs->second);
}

cowl_uint_t cowl_inv_obj_prop_axiom_hash(CowlInvObjPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_inv_obj_prop_axiom_iterate_signature(CowlInvObjPropAxiom *axiom,
                                               void *ctx, CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_iterate_signature(axiom->first, ctx, iter)) return false;
    if (!cowl_obj_prop_exp_iterate_signature(axiom->second, ctx, iter)) return false;
    return true;
}
