/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_func_data_prop_axiom_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_template.h"

static CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_alloc(CowlDataPropExp *prop,
                                                              CowlObjectVec *annot) {
    CowlFuncDataPropAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    ulib_uint hash = cowl_axiom_hash_1(COWL_HASH_INIT_FUNCTIONAL_DATA_PROP_AXIOM, annot,
                                       cowl_data_prop_exp_hash(prop));

    cowl_axiom_init(CowlFuncDataPropAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_FUNC_DATA_PROP, hash, annot),
        .prop = cowl_data_prop_exp_retain(prop)
    );

    return axiom;
}

static void cowl_func_data_prop_axiom_free(CowlFuncDataPropAxiom *axiom) {
    cowl_data_prop_exp_release(axiom->prop);
    cowl_axiom_free(axiom);
}

CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_get(CowlDataPropExp *prop,
                                                     CowlObjectVec *annot) {
    if (!prop) return NULL;
    return cowl_func_data_prop_axiom_alloc(prop, annot);
}

CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_retain(CowlFuncDataPropAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_func_data_prop_axiom_release(CowlFuncDataPropAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_func_data_prop_axiom_free(axiom);
    }
}

CowlDataPropExp* cowl_func_data_prop_axiom_get_prop(CowlFuncDataPropAxiom *axiom) {
    return axiom->prop;
}

CowlObjectVec* cowl_func_data_prop_axiom_get_annot(CowlFuncDataPropAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_func_data_prop_axiom_to_string(CowlFuncDataPropAxiom *axiom)
    COWL_TO_STRING_IMPL(func_data_prop_axiom, axiom)

bool cowl_func_data_prop_axiom_equals(CowlFuncDataPropAxiom *lhs, CowlFuncDataPropAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs, cowl_data_prop_exp_equals(lhs->prop, rhs->prop));
}

ulib_uint cowl_func_data_prop_axiom_hash(CowlFuncDataPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_func_data_prop_axiom_iterate_primitives(CowlFuncDataPropAxiom *axiom,
                                                  CowlPrimitiveFlags flags, CowlIterator *iter) {
    return (cowl_data_prop_exp_iterate_primitives(axiom->prop, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
