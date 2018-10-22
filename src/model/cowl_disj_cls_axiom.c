/// @author Ivano Bilenchi

#include "cowl_disj_cls_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_cls_exp_set.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlDisjClsAxiom* cowl_disj_cls_axiom_alloc(CowlClsExpSet *classes) {
    uint32_t hash = cowl_hash_1(COWL_HASH_INIT_DISJ_CLS_AXIOM,
                                kh_set_hash(CowlClsExpSet, classes));

    CowlDisjClsAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_DISJOINT_CLASSES, hash),
        .classes = classes
    };

    struct CowlDisjClsAxiom *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_disj_cls_axiom_free(CowlDisjClsAxiom *axiom) {
    if (!axiom) return;
    cowl_cls_exp_set_free(axiom->classes);
    free((void *)axiom);
}

#pragma mark - Public

CowlDisjClsAxiom* cowl_disj_cls_axiom_get(CowlClsExpSet *classes) {
    return cowl_disj_cls_axiom_alloc(classes);
}

CowlDisjClsAxiom* cowl_disj_cls_axiom_retain(CowlDisjClsAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_disj_cls_axiom_release(CowlDisjClsAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_disj_cls_axiom_free(axiom);
    }
}

CowlClsExpSet *cowl_disj_cls_axiom_get_classes(CowlDisjClsAxiom *axiom) {
    return axiom->classes;
}

bool cowl_disj_cls_axiom_equals(CowlDisjClsAxiom *lhs, CowlDisjClsAxiom *rhs) {
    return kh_set_equals(CowlClsExpSet, lhs->classes, rhs->classes);
}

uint32_t cowl_disj_cls_axiom_hash(CowlDisjClsAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_disj_cls_axiom_iterate_signature(CowlDisjClsAxiom *axiom, void *ctx,
                                           CowlEntityIterator iter) {
    kh_foreach_key(axiom->classes, CowlClsExp *exp, {
        if (!cowl_cls_exp_iterate_signature(exp, ctx, iter)) return false;
    });
    return true;
}
