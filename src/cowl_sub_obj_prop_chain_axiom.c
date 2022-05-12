/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_sub_obj_prop_chain_axiom_private.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_template.h"
#include "cowl_vector.h"

static CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_alloc(CowlVector *sub,
                                                                     CowlObjPropExp *super,
                                                                     CowlVector *annot) {
    CowlSubObjPropChainAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_axiom_init(CowlSubObjPropChainAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_SUB_OBJ_PROP_CHAIN, annot),
        .sub_props = cowl_vector_retain(sub),
        .super_prop = cowl_obj_prop_exp_retain(super)
    );

    return axiom;
}

static void cowl_sub_obj_prop_chain_axiom_free(CowlSubObjPropChainAxiom *axiom) {
    cowl_vector_release(axiom->sub_props);
    cowl_obj_prop_exp_release(axiom->super_prop);
    cowl_axiom_free(axiom);
}

CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_get(CowlVector *sub,
                                                            CowlObjPropExp *super,
                                                            CowlVector *annot) {
    if ((!sub && super)) return NULL;
    return cowl_sub_obj_prop_chain_axiom_alloc(sub, super, annot);
}

CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_retain(CowlSubObjPropChainAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_sub_obj_prop_chain_axiom_release(CowlSubObjPropChainAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_sub_obj_prop_chain_axiom_free(axiom);
    }
}

CowlVector* cowl_sub_obj_prop_chain_axiom_get_sub_props(CowlSubObjPropChainAxiom *axiom) {
    return axiom->sub_props;
}

CowlObjPropExp* cowl_sub_obj_prop_chain_axiom_get_super_prop(CowlSubObjPropChainAxiom *axiom) {
    return axiom->super_prop;
}

CowlVector* cowl_sub_obj_prop_chain_axiom_get_annot(CowlSubObjPropChainAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_sub_obj_prop_chain_axiom_to_string(CowlSubObjPropChainAxiom *axiom)
    COWL_TO_STRING_IMPL(sub_obj_prop_chain_axiom, axiom)

bool cowl_sub_obj_prop_chain_axiom_equals(CowlSubObjPropChainAxiom *lhs,
                                          CowlSubObjPropChainAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_obj_prop_exp_equals(lhs->super_prop, rhs->super_prop) &&
                                  cowl_vector_equals(lhs->sub_props, rhs->sub_props));
}

ulib_uint cowl_sub_obj_prop_chain_axiom_hash(CowlSubObjPropChainAxiom *axiom) {
    return cowl_hash_2(COWL_HASH_INIT_SUB_OBJ_PROP_CHAIN_AXIOM,
                       cowl_obj_prop_exp_hash(axiom->super_prop),
                       cowl_vector_hash(axiom->sub_props));
}

bool cowl_sub_obj_prop_chain_axiom_iterate_primitives(CowlSubObjPropChainAxiom *axiom,
                                                      CowlPrimitiveFlags flags,
                                                      CowlIterator *iter) {
    return (cowl_obj_prop_exp_iterate_primitives(axiom->super_prop, flags, iter) &&
            cowl_vector_iterate_primitives(axiom->sub_props, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
