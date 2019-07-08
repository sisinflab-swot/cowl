/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_func_data_prop_axiom_private.h"
#include "cowl_data_prop_exp.h"

static CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_alloc(CowlDataPropExp *prop,
                                                              CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_1(COWL_HASH_INIT_FUNCTIONAL_DATA_PROP_AXIOM, annot,
                                         cowl_data_prop_exp_hash(prop));

    CowlFuncDataPropAxiom init = {
        .super = COWL_AXIOM_INIT(COWL_AT_FUNC_DATA_PROP, hash, annot),
        .prop = cowl_data_prop_exp_retain(prop)
    };

    cowl_struct(CowlFuncDataPropAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_func_data_prop_axiom_free(CowlFuncDataPropAxiom *axiom) {
    if (!axiom) return;
    cowl_data_prop_exp_release(axiom->prop);
    cowl_axiom_free(axiom);
}

CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_get(CowlDataPropExp *prop,
                                                     CowlAnnotationVec *annot) {
    return cowl_func_data_prop_axiom_alloc(prop, annot);
}

CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_retain(CowlFuncDataPropAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_func_data_prop_axiom_release(CowlFuncDataPropAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_func_data_prop_axiom_free(axiom);
    }
}

CowlDataPropExp* cowl_func_data_prop_axiom_get_prop(CowlFuncDataPropAxiom *axiom) {
    return axiom->prop;
}

CowlAnnotationVec* cowl_func_data_prop_axiom_get_annot(CowlFuncDataPropAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

bool cowl_func_data_prop_axiom_equals(CowlFuncDataPropAxiom *lhs, CowlFuncDataPropAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs, cowl_data_prop_exp_equals(lhs->prop, rhs->prop));
}

cowl_uint_t cowl_func_data_prop_axiom_hash(CowlFuncDataPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_func_data_prop_axiom_iterate_signature(CowlFuncDataPropAxiom *axiom,
                                                 CowlEntityIterator *iter) {
    if (!cowl_data_prop_exp_iterate_signature(axiom->prop, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}
