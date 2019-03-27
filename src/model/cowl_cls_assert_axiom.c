/// @author Ivano Bilenchi

#include "cowl_cls_assert_axiom_private.h"
#include "cowl_cls_exp_private.h"
#include "cowl_hash_utils.h"
#include "cowl_individual_private.h"

static CowlClsAssertAxiom* cowl_cls_assert_axiom_alloc(CowlIndividual *ind, CowlClsExp *exp) {
    uint32_t hash = cowl_hash_2(COWL_HASH_INIT_CLS_ASSERT_AXIOM,
                                cowl_individual_hash(ind),
                                cowl_cls_exp_hash(exp));

    CowlClsAssertAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_CLASS_ASSERTION, hash),
        .individual = cowl_individual_retain(ind),
        .cls_exp = cowl_cls_exp_retain(exp)
    };

    struct CowlClsAssertAxiom *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_cls_assert_axiom_free(CowlClsAssertAxiom *axiom) {
    if (!axiom) return;
    cowl_individual_release(axiom->individual);
    cowl_cls_exp_release(axiom->cls_exp);
    free((void *)axiom);
}

CowlClsAssertAxiom* cowl_cls_assert_axiom_get(CowlIndividual *ind, CowlClsExp *exp) {
    return cowl_cls_assert_axiom_alloc(ind, exp);
}

CowlClsAssertAxiom* cowl_cls_assert_axiom_retain(CowlClsAssertAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_cls_assert_axiom_release(CowlClsAssertAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_cls_assert_axiom_free(axiom);
    }
}

CowlIndividual* cowl_cls_assert_axiom_get_individual(CowlClsAssertAxiom *axiom) {
    return axiom->individual;
}

CowlClsExp* cowl_cls_assert_axiom_get_cls_exp(CowlClsAssertAxiom *axiom) {
    return axiom->cls_exp;
}

bool cowl_cls_assert_axiom_iterate_signature(CowlClsAssertAxiom *axiom, void *ctx,
                                             CowlEntityIterator iter) {
    if (!cowl_individual_iterate_signature(axiom->individual, ctx, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(axiom->cls_exp, ctx, iter)) return false;
    return true;
}

bool cowl_cls_assert_axiom_equals(CowlClsAssertAxiom *lhs, CowlClsAssertAxiom *rhs) {
    return cowl_individual_equals(lhs->individual, rhs->individual) &&
           cowl_cls_exp_equals(lhs->cls_exp, rhs->cls_exp);
}

uint32_t cowl_cls_assert_axiom_hash(CowlClsAssertAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}
