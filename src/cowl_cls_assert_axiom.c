/// @author Ivano Bilenchi

#include "cowl_cls_assert_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_hash_utils.h"
#include "cowl_individual.h"

CowlIndividual const* cowl_cls_assert_axiom_get_individual(CowlClsAssertAxiom const *axiom) {
    return axiom->individual;
}

CowlClsExp const* cowl_cls_assert_axiom_get_cls_exp(CowlClsAssertAxiom const *axiom) {
    return axiom->cls_exp;
}

bool cowl_cls_assert_axiom_enum_signature(CowlClsAssertAxiom const *axiom, void *ctx,
                                          CowlEntityIterator iter) {
    if (!cowl_individual_enum_signature(axiom->individual, ctx, iter)) return false;
    if (!cowl_cls_exp_enum_signature(axiom->cls_exp, ctx, iter)) return false;
    return true;
}

bool cowl_cls_assert_axiom_equals(CowlClsAssertAxiom const *lhs, CowlClsAssertAxiom const *rhs) {
    return cowl_individual_equals(lhs->individual, rhs->individual) &&
           cowl_cls_exp_equals(lhs->cls_exp, rhs->cls_exp);
}

uint32_t cowl_cls_assert_axiom_hash(CowlClsAssertAxiom const *axiom) {
    return cowl_hash_2(COWL_HASH_INIT_CLS_ASSERT_AXIOM,
                       cowl_individual_hash(axiom->individual),
                       cowl_cls_exp_hash(axiom->cls_exp));
}
