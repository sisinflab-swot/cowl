/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_sub_obj_prop_chain_axiom_private.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_obj_prop_exp_vec.h"
#include "cowl_str_buf.h"

static CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_alloc(CowlObjPropExpVec *sub,
                                                                     CowlObjPropExp *super,
                                                                     CowlAnnotationVec *annot) {
    CowlSubObjPropChainAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_SUB_OBJ_PROP_CHAIN_AXIOM, annot,
                                         cowl_obj_prop_exp_vec_hash(sub),
                                         cowl_obj_prop_exp_hash(super));

    cowl_axiom_init(CowlSubObjPropChainAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_SUB_OBJ_PROP_CHAIN, hash, annot),
        .sub_props = sub,
        .super_prop = cowl_obj_prop_exp_retain(super)
    );

    return axiom;
}

static void cowl_sub_obj_prop_chain_axiom_free(CowlSubObjPropChainAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_vec_free(axiom->sub_props);
    cowl_obj_prop_exp_release(axiom->super_prop);
    cowl_axiom_free(axiom);
}

CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_get(CowlObjPropExpVec *sub,
                                                            CowlObjPropExp *super,
                                                            CowlAnnotationVec *annot) {
    return cowl_sub_obj_prop_chain_axiom_alloc(sub, super, annot);
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

CowlAnnotationVec* cowl_sub_obj_prop_chain_axiom_get_annot(CowlSubObjPropChainAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_sub_obj_prop_chain_axiom_to_string(CowlSubObjPropChainAxiom *axiom) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_sub_obj_prop_chain_axiom(buf, axiom);
    return cowl_str_buf_to_string(buf);
}

bool cowl_sub_obj_prop_chain_axiom_equals(CowlSubObjPropChainAxiom *lhs,
                                          CowlSubObjPropChainAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_obj_prop_exp_equals(lhs->super_prop, rhs->super_prop) &&
                                  cowl_obj_prop_exp_vec_equals(lhs->sub_props, rhs->sub_props));
}

cowl_uint_t cowl_sub_obj_prop_chain_axiom_hash(CowlSubObjPropChainAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_sub_obj_prop_chain_axiom_iterate_signature(CowlSubObjPropChainAxiom *axiom,
                                                     CowlEntityIterator *iter) {
    if (!cowl_obj_prop_exp_iterate_signature(axiom->super_prop, iter)) return false;
    if (!cowl_obj_prop_exp_vec_iterate_signature(axiom->sub_props, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}

bool cowl_sub_obj_prop_chain_axiom_iterate_anon_inds(CowlSubObjPropChainAxiom *axiom,
                                                     CowlAnonIndIterator *iter) {
    return cowl_axiom_annot_iterate_anon_inds(axiom, iter);
}
