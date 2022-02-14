/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_prop_range_axiom_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_data_range.h"
#include "cowl_template.h"

static CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_alloc(CowlDataPropExp *prop,
                                                                CowlDataRange *range,
                                                                CowlObjectVec *annot) {
    CowlDataPropRangeAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    ulib_uint hash = cowl_axiom_hash_2(COWL_HASH_INIT_DATA_PROP_RANGE_AXIOM, annot,
                                       cowl_data_prop_exp_hash(prop),
                                       cowl_data_range_hash(range));

    cowl_axiom_init(CowlDataPropRangeAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_DATA_PROP_RANGE, hash, annot),
        .prop_exp = cowl_data_prop_exp_retain(prop),
        .range = cowl_data_range_retain(range)
    );

    return axiom;
}

static void cowl_data_prop_range_axiom_free(CowlDataPropRangeAxiom *axiom) {
    cowl_data_prop_exp_release(axiom->prop_exp);
    cowl_data_range_release(axiom->range);
    cowl_axiom_free(axiom);
}

CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_get(CowlDataPropExp *prop, CowlDataRange *range,
                                                       CowlObjectVec *annot) {
    if (!(prop && range)) return NULL;
    return cowl_data_prop_range_axiom_alloc(prop, range, annot);
}

CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_retain(CowlDataPropRangeAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_data_prop_range_axiom_release(CowlDataPropRangeAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_data_prop_range_axiom_free(axiom);
    }
}

CowlDataPropExp* cowl_data_prop_range_axiom_get_prop(CowlDataPropRangeAxiom *axiom) {
    return axiom->prop_exp;
}

CowlDataRange* cowl_data_prop_range_axiom_get_range(CowlDataPropRangeAxiom *axiom) {
    return axiom->range;
}

CowlObjectVec* cowl_data_prop_range_axiom_get_annot(CowlDataPropRangeAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_data_prop_range_axiom_to_string(CowlDataPropRangeAxiom *axiom)
    COWL_TO_STRING_IMPL(data_prop_range, axiom)

bool cowl_data_prop_range_axiom_equals(CowlDataPropRangeAxiom *lhs, CowlDataPropRangeAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_data_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
                                  cowl_data_range_equals(lhs->range, rhs->range));
}

ulib_uint cowl_data_prop_range_axiom_hash(CowlDataPropRangeAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_data_prop_range_axiom_iterate_primitives(CowlDataPropRangeAxiom *axiom,
                                                   CowlPrimitiveFlags flags, CowlIterator *iter) {
    return (cowl_data_prop_exp_iterate_primitives(axiom->prop_exp, flags, iter) &&
            cowl_data_range_iterate_primitives(axiom->range, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
