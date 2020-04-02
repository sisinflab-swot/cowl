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
#include "cowl_template.h"

static CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_alloc(CowlAxiomType type,
                                                              CowlDataPropExpSet *props,
                                                              CowlAnnotationVec *annot) {
    CowlNAryDataPropAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_NARY_DATA_PROP_AXIOM, annot, type,
                                         cowl_data_prop_exp_set_hash(props));

    cowl_axiom_init(CowlNAryDataPropAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .props = props
    );

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

CowlString* cowl_nary_data_prop_axiom_to_string(CowlNAryDataPropAxiom *axiom)
    COWL_TO_STRING_IMPL(nary_data_prop_axiom, axiom)

bool cowl_nary_data_prop_axiom_equals(CowlNAryDataPropAxiom *lhs, CowlNAryDataPropAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs, cowl_data_prop_exp_set_equals(lhs->props, rhs->props));
}

cowl_uint_t cowl_nary_data_prop_axiom_hash(CowlNAryDataPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_data_prop_axiom_iterate_signature(CowlNAryDataPropAxiom *axiom,
                                                 CowlEntityIterator *iter) {
    if (cowl_data_prop_exp_set_iterate_signature(axiom->props, iter) &&
        cowl_axiom_annot_iterate_signature(axiom, iter)) {
        return true;
    }
    return false;
}

bool cowl_nary_data_prop_axiom_iterate_primitives(CowlNAryDataPropAxiom *axiom,
                                                  CowlPrimitiveIterator *iter) {
    if (cowl_data_prop_exp_set_iterate_primitives(axiom->props, iter) &&
        cowl_axiom_annot_iterate_primitives(axiom, iter)) {
        return true;
    }
    return false;
}
