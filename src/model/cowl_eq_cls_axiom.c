/// @author Ivano Bilenchi

#include "cowl_eq_cls_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_cls_exp_set.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlEqClsAxiom* cowl_eq_cls_axiom_alloc(CowlClsExpSet *classes) {
    uint32_t hash = cowl_hash_1(COWL_HASH_INIT_EQ_CLS_AXIOM,
                                kh_set_hash(CowlClsExpSet, classes));

    CowlEqClsAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_EQUIVALENT_CLASSES, hash),
        .classes = classes
    };

    struct CowlEqClsAxiom *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_eq_cls_axiom_free(CowlEqClsAxiom *axiom) {
    if (!axiom) return;
    cowl_cls_exp_set_free(axiom->classes);
    free((void *)axiom);
}

#pragma mark - Public

CowlEqClsAxiom* cowl_eq_cls_axiom_get(CowlClsExpSet *classes) {
    return cowl_eq_cls_axiom_alloc(classes);
}

CowlEqClsAxiom* cowl_eq_cls_axiom_retain(CowlEqClsAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_eq_cls_axiom_release(CowlEqClsAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_eq_cls_axiom_free(axiom);
    }
}

CowlClsExpSet* cowl_eq_cls_axiom_get_classes(CowlEqClsAxiom *axiom) {
    return axiom->classes;
}

bool cowl_eq_cls_axiom_equals(CowlEqClsAxiom *lhs, CowlEqClsAxiom *rhs) {
    return kh_set_equals(CowlClsExpSet, lhs->classes, rhs->classes);
}

uint32_t cowl_eq_cls_axiom_hash(CowlEqClsAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_eq_cls_axiom_iterate_signature(CowlEqClsAxiom *axiom, void *ctx,
                                         CowlEntityIterator iter) {
    kh_foreach_key(axiom->classes, CowlClsExp *exp, {
        if (!cowl_cls_exp_iterate_signature(exp, ctx, iter)) return false;
    });
    return true;
}
