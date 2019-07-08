/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_sub_data_prop_axiom_private.h"
#include "cowl_data_prop_exp.h"

static CowlSubDataPropAxiom* cowl_sub_data_prop_axiom_alloc(CowlDataPropExp *sub,
                                                            CowlDataPropExp *super,
                                                            CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_SUB_DATA_PROP_AXIOM, annot,
                                         cowl_data_prop_exp_hash(sub),
                                         cowl_data_prop_exp_hash(super));

    CowlSubDataPropAxiom init = {
        .super = COWL_AXIOM_INIT(COWL_AT_SUB_DATA_PROP, hash, annot),
        .super_prop = cowl_data_prop_exp_retain(super),
        .sub_prop = cowl_data_prop_exp_retain(sub)
    };

    cowl_struct(CowlSubDataPropAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_sub_data_prop_axiom_free(CowlSubDataPropAxiom *axiom) {
    if (!axiom) return;
    cowl_data_prop_exp_release(axiom->super_prop);
    cowl_data_prop_exp_release(axiom->sub_prop);
    cowl_axiom_free(axiom);
}

CowlSubDataPropAxiom* cowl_sub_data_prop_axiom_get(CowlDataPropExp *sub, CowlDataPropExp *super,
                                                   CowlAnnotationVec *annot) {
    return cowl_sub_data_prop_axiom_alloc(sub, super, annot);
}

CowlSubDataPropAxiom* cowl_sub_data_prop_axiom_retain(CowlSubDataPropAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_sub_data_prop_axiom_release(CowlSubDataPropAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_sub_data_prop_axiom_free(axiom);
    }
}

CowlDataPropExp* cowl_sub_data_prop_axiom_get_super(CowlSubDataPropAxiom *axiom) {
    return axiom->super_prop;
}

CowlDataPropExp* cowl_sub_data_prop_axiom_get_sub(CowlSubDataPropAxiom *axiom) {
    return axiom->sub_prop;
}

CowlAnnotationVec* cowl_sub_data_prop_axiom_get_annot(CowlSubDataPropAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

bool cowl_sub_data_prop_axiom_equals(CowlSubDataPropAxiom *lhs, CowlSubDataPropAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_data_prop_exp_equals(lhs->super_prop, rhs->super_prop) &&
                                  cowl_data_prop_exp_equals(lhs->sub_prop, rhs->sub_prop));
}

cowl_uint_t cowl_sub_data_prop_axiom_hash(CowlSubDataPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_sub_data_prop_axiom_iterate_signature(CowlSubDataPropAxiom *axiom,
                                               CowlEntityIterator *iter) {
    if (!cowl_data_prop_exp_iterate_signature(axiom->super_prop, iter)) return false;
    if (!cowl_data_prop_exp_iterate_signature(axiom->sub_prop, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}
