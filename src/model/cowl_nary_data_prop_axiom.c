/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_data_prop_axiom_private.h"
#include "cowl_data_prop_exp_set.h"
#include "cowl_str_buf.h"

static CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_alloc(CowlAxiomType type,
                                                              CowlDataPropExpSet *props,
                                                              CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_NARY_DATA_PROP_AXIOM, annot, type,
                                         cowl_data_prop_exp_set_hash(props));

    CowlNAryDataPropAxiom init = {
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .props = props
    };

    cowl_struct(CowlNAryDataPropAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_nary_data_prop_axiom_free(CowlNAryDataPropAxiom *axiom) {
    if (!axiom) return;
    cowl_data_prop_exp_set_free(axiom->props);
    cowl_axiom_free(axiom);
}

CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_get(CowlNAryAxiomType type,
                                                     CowlDataPropExpSet *props,
                                                     CowlAnnotationVec *annot) {
    CowlAxiomType axiom_type = (CowlAxiomType)type + COWL_AT_EQUIV_DATA_PROP;
    return cowl_nary_data_prop_axiom_alloc(axiom_type, props, annot);
}

CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_retain(CowlNAryDataPropAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_nary_data_prop_axiom_release(CowlNAryDataPropAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_nary_data_prop_axiom_free(axiom);
    }
}

CowlNAryAxiomType cowl_nary_data_prop_axiom_get_type(CowlNAryDataPropAxiom *axiom) {
    CowlAxiomFlags flags = axiom->super.flags;
    return (CowlNAryAxiomType)(cowl_axiom_flags_get_type(flags) - COWL_AT_EQUIV_DATA_PROP);
}

CowlDataPropExpSet* cowl_nary_data_prop_axiom_get_props(CowlNAryDataPropAxiom *axiom) {
    return axiom->props;
}

CowlAnnotationVec* cowl_nary_data_prop_axiom_get_annot(CowlNAryDataPropAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_nary_data_prop_axiom_to_string(CowlNAryDataPropAxiom *axiom) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_nary_data_prop_axiom(buf, axiom);
    return cowl_str_buf_to_string(buf);
}

bool cowl_nary_data_prop_axiom_equals(CowlNAryDataPropAxiom *lhs, CowlNAryDataPropAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs, cowl_data_prop_exp_set_equals(lhs->props, rhs->props));
}

cowl_uint_t cowl_nary_data_prop_axiom_hash(CowlNAryDataPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_data_prop_axiom_iterate_signature(CowlNAryDataPropAxiom *axiom,
                                                 CowlEntityIterator *iter) {
    if (!cowl_data_prop_exp_set_iterate_signature(axiom->props, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}

bool cowl_nary_data_prop_axiom_iterate_anon_inds(CowlNAryDataPropAxiom *axiom,
                                                 CowlAnonIndIterator *iter) {
    return cowl_axiom_annot_iterate_anon_inds(axiom, iter);
}
