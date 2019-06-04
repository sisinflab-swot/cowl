/// @author Ivano Bilenchi

#include "cowl_nary_individual_axiom_private.h"
#include "cowl_hash_utils.h"
#include "cowl_individual.h"
#include "cowl_individual_set.h"

static CowlNAryIndividualAxiom* cowl_nary_individual_axiom_alloc(CowlAxiomType type,
                                                                 CowlIndividualSet *operands) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_NARY_IND_AXIOM, type,
                                   uhset_hash(CowlIndividualSet, operands));

    CowlNAryIndividualAxiom init = {
        .super = COWL_AXIOM_INIT(type, hash),
        .operands = operands
    };

    cowl_struct(CowlNAryIndividualAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_nary_individual_axiom_free(CowlNAryIndividualAxiom *axiom) {
    if (!axiom) return;
    cowl_individual_set_free(axiom->operands);
    free((void *)axiom);
}

CowlNAryIndividualAxiom* cowl_nary_individual_axiom_get(CowlNAryAxiomType type,
                                                        CowlIndividualSet *operands) {
    return cowl_nary_individual_axiom_alloc((CowlAxiomType)type + CAT_SAME_INDIVIDUAL, operands);
}

CowlNAryIndividualAxiom* cowl_nary_individual_axiom_retain(CowlNAryIndividualAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_nary_individual_axiom_release(CowlNAryIndividualAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_nary_individual_axiom_free(axiom);
    }
}

CowlNAryAxiomType cowl_nary_individual_axiom_get_type(CowlNAryIndividualAxiom *axiom) {
    return (CowlNAryAxiomType)(axiom->super.type - CAT_SAME_INDIVIDUAL);
}

CowlIndividualSet* cowl_nary_individual_axiom_get_operands(CowlNAryIndividualAxiom *axiom) {
    return axiom->operands;
}

bool cowl_nary_individual_axiom_equals(CowlNAryIndividualAxiom *lhs, CowlNAryIndividualAxiom *rhs) {
    return lhs->super.type == rhs->super.type &&
           uhset_equals(CowlIndividualSet, lhs->operands, rhs->operands);
}

cowl_uint_t cowl_nary_individual_axiom_hash(CowlNAryIndividualAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_nary_individual_axiom_iterate_signature(CowlNAryIndividualAxiom *axiom, void *ctx,
                                                  CowlEntityIterator iter) {
    uhash_foreach_key(CowlIndividualSet, axiom->operands, individual, {
        if (!cowl_individual_iterate_signature(individual, ctx, iter)) return false;
    });
    return true;
}
