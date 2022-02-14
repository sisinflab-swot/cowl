/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_ind_axiom_private.h"
#include "cowl_macros.h"
#include "cowl_object_table.h"
#include "cowl_template.h"

static CowlNAryIndAxiom* cowl_nary_ind_axiom_alloc(CowlAxiomType type, CowlObjectTable *individuals,
                                                   CowlObjectVec *annot) {
    CowlNAryIndAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    ulib_uint hash = cowl_axiom_hash_2(COWL_HASH_INIT_NARY_IND_AXIOM, annot, type,
                                       cowl_object_set_hash(individuals));

    cowl_axiom_init(CowlNAryIndAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .individuals = individuals
    );

    return axiom;
}

static void cowl_nary_ind_axiom_free(CowlNAryIndAxiom *axiom) {
    cowl_object_set_free(axiom->individuals);
    cowl_axiom_free(axiom);
}

CowlNAryIndAxiom* cowl_nary_ind_axiom_get(CowlNAryAxiomType type, CowlObjectTable *operands,
                                          CowlObjectVec *annot) {
    if (!(operands && cowl_enum_value_is_valid(NAT, type))) return NULL;
    CowlAxiomType axiom_type = (CowlAxiomType)type + COWL_AT_SAME_IND;
    return cowl_nary_ind_axiom_alloc(axiom_type, operands, annot);
}

CowlNAryIndAxiom* cowl_nary_ind_axiom_retain(CowlNAryIndAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_nary_ind_axiom_release(CowlNAryIndAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_nary_ind_axiom_free(axiom);
    }
}

CowlNAryAxiomType cowl_nary_ind_axiom_get_type(CowlNAryIndAxiom *axiom) {
    return (CowlNAryAxiomType)(cowl_get_type(axiom) - COWL_OT_A_SAME_IND);
}

CowlObjectTable* cowl_nary_ind_axiom_get_individuals(CowlNAryIndAxiom *axiom) {
    return axiom->individuals;
}

CowlObjectVec* cowl_nary_ind_axiom_get_annot(CowlNAryIndAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_nary_ind_axiom_to_string(CowlNAryIndAxiom *axiom)
    COWL_TO_STRING_IMPL(nary_ind_axiom, axiom)

bool cowl_nary_ind_axiom_equals(CowlNAryIndAxiom *lhs, CowlNAryIndAxiom *rhs) {
    return cowl_object_type_equals(lhs, rhs) &&
           cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_object_set_equals(lhs->individuals, rhs->individuals));
}

ulib_uint cowl_nary_ind_axiom_hash(CowlNAryIndAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_ind_axiom_iterate_primitives(CowlNAryIndAxiom *axiom, CowlPrimitiveFlags flags,
                                            CowlIterator *iter) {
    return (cowl_object_set_iterate_primitives(axiom->individuals, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
