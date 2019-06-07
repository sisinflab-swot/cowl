/// @author Ivano Bilenchi

#include "cowl_sub_obj_prop_chain_axiom_private.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_obj_prop_exp_vec.h"

static CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_alloc(CowlObjPropExpVec *sub_props,
                                                                     CowlObjPropExp *super_prop) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_SUB_OBJ_PROP_CHAIN_AXIOM,
                                   cowl_obj_prop_exp_vec_hash(sub_props),
                                   cowl_obj_prop_exp_hash(super_prop));

    CowlSubObjPropChainAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_SUB_OBJ_PROP_CHAIN, hash),
        .sub_props = sub_props,
        .super_prop = cowl_obj_prop_exp_retain(super_prop)
    };

    cowl_struct(CowlSubObjPropChainAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_sub_obj_prop_chain_axiom_free(CowlSubObjPropChainAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_vec_free(axiom->sub_props);
    cowl_obj_prop_exp_release(axiom->super_prop);
    free((void *)axiom);
}

CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_get(CowlObjPropExpVec *sub_props,
                                                            CowlObjPropExp *super_prop) {
    return cowl_sub_obj_prop_chain_axiom_alloc(sub_props, super_prop);
}

CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_retain(CowlSubObjPropChainAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_sub_obj_prop_chain_axiom_release(CowlSubObjPropChainAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_sub_obj_prop_chain_axiom_free(axiom);
    }
}

CowlObjPropExpVec* cowl_sub_obj_prop_chain_axiom_get_sub_props(CowlSubObjPropChainAxiom *axiom) {
    return axiom->sub_props;
}

CowlObjPropExp* cowl_sub_obj_prop_chain_axiom_get_super_prop(CowlSubObjPropChainAxiom *axiom) {
    return axiom->super_prop;
}

bool cowl_sub_obj_prop_chain_axiom_equals(CowlSubObjPropChainAxiom *lhs,
                                          CowlSubObjPropChainAxiom *rhs) {
    return cowl_obj_prop_exp_equals(lhs->super_prop, rhs->super_prop) &&
           vector_equals(CowlObjPropExpPtr, lhs->sub_props, rhs->sub_props);
}

cowl_uint_t cowl_sub_obj_prop_chain_axiom_hash(CowlSubObjPropChainAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_sub_obj_prop_chain_axiom_iterate_signature(CowlSubObjPropChainAxiom *axiom, void *ctx,
                                                     CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_iterate_signature(axiom->super_prop, ctx, iter)) return false;

    vector_foreach(CowlObjPropExpPtr, axiom->sub_props, prop, {
        if (!cowl_obj_prop_exp_iterate_signature(prop, ctx, iter)) return false;
    });

    return true;
}
