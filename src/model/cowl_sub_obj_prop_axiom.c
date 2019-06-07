/// @author Ivano Bilenchi

#include "cowl_sub_obj_prop_axiom_private.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"

static CowlSubObjPropAxiom* cowl_sub_obj_prop_axiom_alloc(CowlObjPropExp *sub,
                                                          CowlObjPropExp *super) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_SUB_OBJ_PROP_AXIOM,
                                   cowl_obj_prop_exp_hash(sub),
                                   cowl_obj_prop_exp_hash(super));

    CowlSubObjPropAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_SUB_OBJ_PROP, hash),
        .super_prop = cowl_obj_prop_exp_retain(super),
        .sub_prop = cowl_obj_prop_exp_retain(sub)
    };

    cowl_struct(CowlSubObjPropAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_sub_obj_prop_axiom_free(CowlSubObjPropAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_release(axiom->super_prop);
    cowl_obj_prop_exp_release(axiom->sub_prop);
    free((void *)axiom);
}

CowlSubObjPropAxiom* cowl_sub_obj_prop_axiom_get(CowlObjPropExp *sub, CowlObjPropExp *super) {
    return cowl_sub_obj_prop_axiom_alloc(sub, super);
}

CowlSubObjPropAxiom* cowl_sub_obj_prop_axiom_retain(CowlSubObjPropAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_sub_obj_prop_axiom_release(CowlSubObjPropAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_sub_obj_prop_axiom_free(axiom);
    }
}

CowlObjPropExp* cowl_sub_obj_prop_axiom_get_super(CowlSubObjPropAxiom *axiom) {
    return axiom->super_prop;
}

CowlObjPropExp* cowl_sub_obj_prop_axiom_get_sub(CowlSubObjPropAxiom *axiom) {
    return axiom->sub_prop;
}

bool cowl_sub_obj_prop_axiom_equals(CowlSubObjPropAxiom *lhs, CowlSubObjPropAxiom *rhs) {
    return cowl_obj_prop_exp_equals(lhs->super_prop, rhs->super_prop) &&
           cowl_obj_prop_exp_equals(lhs->sub_prop, rhs->sub_prop);
}

cowl_uint_t cowl_sub_obj_prop_axiom_hash(CowlSubObjPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_sub_obj_prop_axiom_iterate_signature(CowlSubObjPropAxiom *axiom,
                                               void *ctx, CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_iterate_signature(axiom->super_prop, ctx, iter)) return false;
    if (!cowl_obj_prop_exp_iterate_signature(axiom->sub_prop, ctx, iter)) return false;
    return true;
}
