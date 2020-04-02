/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_sub_obj_prop_axiom_private.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlSubObjPropAxiom* cowl_sub_obj_prop_axiom_alloc(CowlObjPropExp *sub,
                                                          CowlObjPropExp *super,
                                                          CowlAnnotationVec *annot) {
    CowlSubObjPropAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_SUB_OBJ_PROP_AXIOM, annot,
                                         cowl_obj_prop_exp_hash(sub),
                                         cowl_obj_prop_exp_hash(super));

    cowl_axiom_init(CowlSubObjPropAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_SUB_OBJ_PROP, hash, annot),
        .super_prop = cowl_obj_prop_exp_retain(super),
        .sub_prop = cowl_obj_prop_exp_retain(sub)
    );

    return axiom;
}

static void cowl_sub_obj_prop_axiom_free(CowlSubObjPropAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_release(axiom->super_prop);
    cowl_obj_prop_exp_release(axiom->sub_prop);
    cowl_axiom_free(axiom);
}

CowlSubObjPropAxiom* cowl_sub_obj_prop_axiom_get(CowlObjPropExp *sub, CowlObjPropExp *super,
                                                 CowlAnnotationVec *annot) {
    return cowl_sub_obj_prop_axiom_alloc(sub, super, annot);
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

CowlAnnotationVec* cowl_sub_obj_prop_axiom_get_annot(CowlSubObjPropAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_sub_obj_prop_axiom_to_string(CowlSubObjPropAxiom *axiom)
    COWL_TO_STRING_IMPL(sub_obj_prop_axiom, axiom)

bool cowl_sub_obj_prop_axiom_equals(CowlSubObjPropAxiom *lhs, CowlSubObjPropAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_obj_prop_exp_equals(lhs->super_prop, rhs->super_prop) &&
                                  cowl_obj_prop_exp_equals(lhs->sub_prop, rhs->sub_prop));
}

cowl_uint_t cowl_sub_obj_prop_axiom_hash(CowlSubObjPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_sub_obj_prop_axiom_iterate_signature(CowlSubObjPropAxiom *axiom,
                                               CowlEntityIterator *iter) {
    if (!cowl_obj_prop_exp_iterate_signature(axiom->super_prop, iter)) return false;
    if (!cowl_obj_prop_exp_iterate_signature(axiom->sub_prop, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}

bool cowl_sub_obj_prop_axiom_iterate_anon_inds(CowlSubObjPropAxiom *axiom,
                                               CowlAnonIndIterator *iter) {
    return cowl_axiom_annot_iterate_anon_inds(axiom, iter);
}
