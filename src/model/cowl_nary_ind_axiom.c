/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_ind_axiom_private.h"
#include "cowl_individual_set.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlNAryIndAxiom* cowl_nary_ind_axiom_alloc(CowlAxiomType type, CowlIndividualSet *individuals,
                                                   CowlAnnotationVec *annot) {
    CowlNAryIndAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_NARY_IND_AXIOM, annot, type,
                                         cowl_individual_set_hash(individuals));

    cowl_axiom_init(CowlNAryIndAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .individuals = individuals
    );

    return axiom;
}

static void cowl_nary_ind_axiom_free(CowlNAryIndAxiom *axiom) {
    if (!axiom) return;
    cowl_individual_set_free(axiom->individuals);
    cowl_axiom_free(axiom);
}

CowlNAryIndAxiom* cowl_nary_ind_axiom_get(CowlNAryAxiomType type, CowlIndividualSet *operands,
                                          CowlAnnotationVec *annot) {
    CowlAxiomType axiom_type = (CowlAxiomType)type + COWL_AT_SAME_IND;
    return cowl_nary_ind_axiom_alloc(axiom_type, operands, annot);
}

CowlNAryIndAxiom* cowl_nary_ind_axiom_retain(CowlNAryIndAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_nary_ind_axiom_release(CowlNAryIndAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_nary_ind_axiom_free(axiom);
    }
}

CowlNAryAxiomType cowl_nary_ind_axiom_get_type(CowlNAryIndAxiom *axiom) {
    CowlAxiomFlags flags = axiom->super.flags;
    return (CowlNAryAxiomType)(cowl_axiom_flags_get_type(flags) - COWL_AT_SAME_IND);
}

CowlIndividualSet* cowl_nary_ind_axiom_get_individuals(CowlNAryIndAxiom *axiom) {
    return axiom->individuals;
}

CowlAnnotationVec* cowl_nary_ind_axiom_get_annot(CowlNAryIndAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_nary_ind_axiom_to_string(CowlNAryIndAxiom *axiom)
    COWL_TO_STRING_IMPL(nary_ind_axiom, axiom)

bool cowl_nary_ind_axiom_equals(CowlNAryIndAxiom *lhs, CowlNAryIndAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_individual_set_equals(lhs->individuals, rhs->individuals));
}

cowl_uint_t cowl_nary_ind_axiom_hash(CowlNAryIndAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_ind_axiom_iterate_signature(CowlNAryIndAxiom *axiom, CowlEntityIterator *iter) {
    if (!cowl_individual_set_iterate_signature(axiom->individuals, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}

bool cowl_nary_ind_axiom_iterate_anon_inds(CowlNAryIndAxiom *axiom, CowlAnonIndIterator *iter) {
    if (!cowl_individual_set_iterate_anon_inds(axiom->individuals, iter)) return false;
    if (!cowl_axiom_annot_iterate_anon_inds(axiom, iter)) return false;
    return true;
}
