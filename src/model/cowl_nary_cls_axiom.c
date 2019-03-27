/// @author Ivano Bilenchi

#include "cowl_nary_cls_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_cls_exp_set.h"
#include "cowl_hash_utils.h"

static CowlNAryClsAxiom* cowl_nary_cls_axiom_alloc(CowlAxiomType type, CowlClsExpSet *classes) {
    uint32_t hash = cowl_hash_2(COWL_HASH_INIT_NARY_CLS_AXIOM, type,
                                kh_set_hash(CowlClsExpSet, classes));

    CowlNAryClsAxiom init = {
        .super = COWL_AXIOM_INIT(type, hash),
        .classes = classes
    };

    struct CowlNAryClsAxiom *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_nary_cls_axiom_free(CowlNAryClsAxiom *axiom) {
    if (!axiom) return;
    cowl_cls_exp_set_free(axiom->classes);
    free((void *)axiom);
}

CowlNAryClsAxiom* cowl_nary_cls_axiom_get(CowlNAryClsAxiomType type, CowlClsExpSet *classes) {
    return cowl_nary_cls_axiom_alloc(type + CAT_EQUIVALENT_CLASSES, classes);
}

CowlNAryClsAxiom* cowl_nary_cls_axiom_retain(CowlNAryClsAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_nary_cls_axiom_release(CowlNAryClsAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_nary_cls_axiom_free(axiom);
    }
}

CowlNAryClsAxiomType cowl_nary_cls_axiom_get_type(CowlNAryClsAxiom *axiom) {
    return axiom->super.type - CAT_EQUIVALENT_CLASSES;
}

CowlClsExpSet *cowl_nary_cls_axiom_get_classes(CowlNAryClsAxiom *axiom) {
    return axiom->classes;
}

bool cowl_nary_cls_axiom_equals(CowlNAryClsAxiom *lhs, CowlNAryClsAxiom *rhs) {
    return lhs->super.type == rhs->super.type &&
           kh_set_equals(CowlClsExpSet, lhs->classes, rhs->classes);
}

uint32_t cowl_nary_cls_axiom_hash(CowlNAryClsAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_nary_cls_axiom_iterate_signature(CowlNAryClsAxiom *axiom, void *ctx,
                                           CowlEntityIterator iter) {
    kh_foreach_key(axiom->classes, CowlClsExp *exp, {
        if (!cowl_cls_exp_iterate_signature(exp, ctx, iter)) return false;
    });
    return true;
}
