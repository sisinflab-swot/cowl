/// @author Ivano Bilenchi

#include "cowl_disj_cls_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_cls_exp_set.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlDisjClsAxiom* cowl_disj_cls_axiom_alloc(khash_t(CowlClsExpSet) const *classes) {
    uint32_t hash = cowl_hash_1(COWL_HASH_INIT_DISJ_CLS_AXIOM,
                                kh_set_hash(CowlClsExpSet, classes));

    CowlDisjClsAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_DISJOINT_CLASSES, hash),
        .classes = classes
    };

    CowlDisjClsAxiom *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_disj_cls_axiom_free(CowlDisjClsAxiom const *axiom) {
    if (!axiom) return;
    cowl_cls_exp_set_free(axiom->classes);
    free((void *)axiom);
}

#pragma mark - Public

CowlDisjClsAxiom const* cowl_disj_cls_axiom_get(khash_t(CowlClsExpSet) const *classes) {
    return cowl_disj_cls_axiom_alloc(classes);
}

CowlDisjClsAxiom const* cowl_disj_cls_axiom_retain(CowlDisjClsAxiom const *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_disj_cls_axiom_release(CowlDisjClsAxiom const *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_disj_cls_axiom_free(axiom);
    }
}

khash_t(CowlClsExpSet) const *cowl_disj_cls_axiom_get_classes(CowlDisjClsAxiom const *axiom) {
    return axiom->classes;
}

bool cowl_disj_cls_axiom_equals(CowlDisjClsAxiom const *lhs, CowlDisjClsAxiom const *rhs) {
    return kh_set_equals(CowlClsExpSet, lhs->classes, rhs->classes);
}

uint32_t cowl_disj_cls_axiom_hash(CowlDisjClsAxiom const *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_disj_cls_axiom_iterate_signature(CowlDisjClsAxiom const *axiom, void *ctx,
                                           CowlEntityIterator iter) {
    kh_foreach_key(axiom->classes, CowlClsExp const *exp, {
        if (!cowl_cls_exp_iterate_signature(exp, ctx, iter)) return false;
    });
    return true;
}
