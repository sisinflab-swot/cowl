/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_prop_range_axiom_private.h"
#include "cowl_alloc.h"
#include "cowl_data_prop_exp.h"
#include "cowl_data_range.h"
#include "cowl_str_buf.h"

static CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_alloc(CowlDataPropExp *prop,
                                                                CowlDataRange *range,
                                                                CowlAnnotationVec *annot) {
    CowlDataPropRangeAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_DATA_PROP_RANGE_AXIOM, annot,
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
    if (!axiom) return;
    cowl_data_prop_exp_release(axiom->prop_exp);
    cowl_data_range_release(axiom->range);
    cowl_axiom_free(axiom);
}

CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_get(CowlDataPropExp *prop, CowlDataRange *range,
                                                       CowlAnnotationVec *annot) {
    return cowl_data_prop_range_axiom_alloc(prop, range, annot);
}

CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_retain(CowlDataPropRangeAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_data_prop_range_axiom_release(CowlDataPropRangeAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_data_prop_range_axiom_free(axiom);
    }
}

CowlDataPropExp* cowl_data_prop_range_axiom_get_prop(CowlDataPropRangeAxiom *axiom) {
    return axiom->prop_exp;
}

CowlDataRange* cowl_data_prop_range_axiom_get_range(CowlDataPropRangeAxiom *axiom) {
    return axiom->range;
}

CowlAnnotationVec* cowl_data_prop_range_axiom_get_annot(CowlDataPropRangeAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_data_prop_range_axiom_to_string(CowlDataPropRangeAxiom *axiom) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_data_prop_range(buf, axiom);
    return cowl_str_buf_to_string(buf);
}

bool cowl_data_prop_range_axiom_equals(CowlDataPropRangeAxiom *lhs, CowlDataPropRangeAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_data_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
                                  cowl_data_range_equals(lhs->range, rhs->range));
}

cowl_uint_t cowl_data_prop_range_axiom_hash(CowlDataPropRangeAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_data_prop_range_axiom_iterate_signature(CowlDataPropRangeAxiom *axiom,
                                                  CowlEntityIterator *iter) {
    if (!cowl_data_prop_exp_iterate_signature(axiom->prop_exp, iter)) return false;
    if (!cowl_data_range_iterate_signature(axiom->range, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}

bool cowl_data_prop_range_axiom_iterate_anon_inds(CowlDataPropRangeAxiom *axiom,
                                                  CowlAnonIndIterator *iter) {
    return cowl_axiom_annot_iterate_anon_inds(axiom, iter);
}
