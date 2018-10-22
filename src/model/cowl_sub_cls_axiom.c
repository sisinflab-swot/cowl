/// @author Ivano Bilenchi

#include "cowl_sub_cls_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlSubClsAxiom* cowl_sub_cls_axiom_alloc(CowlClsExp const *super, CowlClsExp const *sub) {
    uint32_t hash = cowl_hash_2(COWL_HASH_INIT_SUBCLASS_AXIOM,
                                cowl_cls_exp_hash(super),
                                cowl_cls_exp_hash(sub));

    CowlSubClsAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_SUB_CLASS, hash),
        .super_class = cowl_cls_exp_retain(super),
        .sub_class = cowl_cls_exp_retain(sub)
    };

    CowlSubClsAxiom *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_sub_cls_axiom_free(CowlSubClsAxiom const *axiom) {
    if (!axiom) return;
    cowl_cls_exp_release(axiom->super_class);
    cowl_cls_exp_release(axiom->sub_class);
    free((void *)axiom);
}

#pragma mark - Public

CowlSubClsAxiom const* cowl_sub_cls_axiom_get(CowlClsExp const *super, CowlClsExp const *sub) {
    return cowl_sub_cls_axiom_alloc(super, sub);
}

CowlSubClsAxiom const* cowl_sub_cls_axiom_retain(CowlSubClsAxiom const *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_sub_cls_axiom_release(CowlSubClsAxiom const *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_sub_cls_axiom_free(axiom);
    }
}

CowlClsExp const* cowl_sub_cls_axiom_get_super(CowlSubClsAxiom const *axiom) {
    return axiom->super_class;
}

CowlClsExp const* cowl_sub_cls_axiom_get_sub(CowlSubClsAxiom const *axiom) {
    return axiom->sub_class;
}

bool cowl_sub_cls_axiom_equals(CowlSubClsAxiom const *lhs, CowlSubClsAxiom const *rhs) {
    return cowl_cls_exp_equals(lhs->sub_class, rhs->sub_class) &&
           cowl_cls_exp_equals(lhs->super_class, rhs->super_class);
}

uint32_t cowl_sub_cls_axiom_hash(CowlSubClsAxiom const *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_sub_cls_axiom_iterate_signature(CowlSubClsAxiom const *axiom,
                                          void *ctx, CowlEntityIterator iter) {
    if (!cowl_cls_exp_iterate_signature(axiom->super_class, ctx, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(axiom->sub_class, ctx, iter)) return false;
    return true;
}