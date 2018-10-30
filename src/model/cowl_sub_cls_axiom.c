/// @author Ivano Bilenchi

#include "cowl_sub_cls_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlSubClsAxiom* cowl_sub_cls_axiom_alloc(CowlClsExp *sub, CowlClsExp *super) {
    uint32_t hash = cowl_hash_2(COWL_HASH_INIT_SUBCLASS_AXIOM,
                                cowl_cls_exp_hash(super),
                                cowl_cls_exp_hash(sub));

    CowlSubClsAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_SUB_CLASS, hash),
        .super_class = cowl_cls_exp_retain(super),
        .sub_class = cowl_cls_exp_retain(sub)
    };

    struct CowlSubClsAxiom *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_sub_cls_axiom_free(CowlSubClsAxiom *axiom) {
    if (!axiom) return;
    cowl_cls_exp_release(axiom->super_class);
    cowl_cls_exp_release(axiom->sub_class);
    free((void *)axiom);
}

#pragma mark - Public

CowlSubClsAxiom* cowl_sub_cls_axiom_get(CowlClsExp *sub, CowlClsExp *super) {
    return cowl_sub_cls_axiom_alloc(sub, super);
}

CowlSubClsAxiom* cowl_sub_cls_axiom_retain(CowlSubClsAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_sub_cls_axiom_release(CowlSubClsAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_sub_cls_axiom_free(axiom);
    }
}

CowlClsExp* cowl_sub_cls_axiom_get_super(CowlSubClsAxiom *axiom) {
    return axiom->super_class;
}

CowlClsExp* cowl_sub_cls_axiom_get_sub(CowlSubClsAxiom *axiom) {
    return axiom->sub_class;
}

bool cowl_sub_cls_axiom_equals(CowlSubClsAxiom *lhs, CowlSubClsAxiom *rhs) {
    return cowl_cls_exp_equals(lhs->sub_class, rhs->sub_class) &&
           cowl_cls_exp_equals(lhs->super_class, rhs->super_class);
}

uint32_t cowl_sub_cls_axiom_hash(CowlSubClsAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_sub_cls_axiom_iterate_signature(CowlSubClsAxiom *axiom,
                                          void *ctx, CowlEntityIterator iter) {
    if (!cowl_cls_exp_iterate_signature(axiom->super_class, ctx, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(axiom->sub_class, ctx, iter)) return false;
    return true;
}
