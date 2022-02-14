/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_data_prop_axiom_private.h"
#include "cowl_macros.h"
#include "cowl_object_table.h"
#include "cowl_template.h"

static CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_alloc(CowlAxiomType type,
                                                              CowlObjectTable *props,
                                                              CowlObjectVec *annot) {
    CowlNAryDataPropAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    ulib_uint hash = cowl_axiom_hash_2(COWL_HASH_INIT_NARY_DATA_PROP_AXIOM, annot, type,
                                       cowl_object_set_hash(props));

    cowl_axiom_init(CowlNAryDataPropAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .props = props
    );

    return axiom;
}

static void cowl_nary_data_prop_axiom_free(CowlNAryDataPropAxiom *axiom) {
    cowl_object_set_free(axiom->props);
    cowl_axiom_free(axiom);
}

CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_get(CowlNAryAxiomType type,
                                                     CowlObjectTable *props,
                                                     CowlObjectVec *annot) {
    if (!(props && cowl_enum_value_is_valid(NAT, type))) return NULL;
    CowlAxiomType axiom_type = (CowlAxiomType)type + COWL_AT_EQUIV_DATA_PROP;
    return cowl_nary_data_prop_axiom_alloc(axiom_type, props, annot);
}

CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_retain(CowlNAryDataPropAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_nary_data_prop_axiom_release(CowlNAryDataPropAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_nary_data_prop_axiom_free(axiom);
    }
}

CowlNAryAxiomType cowl_nary_data_prop_axiom_get_type(CowlNAryDataPropAxiom *axiom) {
    return (CowlNAryAxiomType)(cowl_get_type(axiom) - COWL_OT_A_EQUIV_DATA_PROP);
}

CowlObjectTable* cowl_nary_data_prop_axiom_get_props(CowlNAryDataPropAxiom *axiom) {
    return axiom->props;
}

CowlObjectVec* cowl_nary_data_prop_axiom_get_annot(CowlNAryDataPropAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_nary_data_prop_axiom_to_string(CowlNAryDataPropAxiom *axiom)
    COWL_TO_STRING_IMPL(nary_data_prop_axiom, axiom)

bool cowl_nary_data_prop_axiom_equals(CowlNAryDataPropAxiom *lhs, CowlNAryDataPropAxiom *rhs) {
    return cowl_object_type_equals(lhs, rhs) &&
           cowl_axiom_equals_impl(lhs, rhs, cowl_object_set_equals(lhs->props, rhs->props));
}

ulib_uint cowl_nary_data_prop_axiom_hash(CowlNAryDataPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_data_prop_axiom_iterate_primitives(CowlNAryDataPropAxiom *axiom,
                                                  CowlPrimitiveFlags flags, CowlIterator *iter) {
    return (cowl_object_set_iterate_primitives(axiom->props, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
