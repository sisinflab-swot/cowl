/// @author Ivano Bilenchi

#include "cowl_disj_cls_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_hash_utils.h"

khash_t(CowlClsExpSet) const *cowl_disj_cls_axiom_get_classes(CowlDisjClsAxiom const *axiom) {
    return axiom->classes;
}

bool cowl_disj_cls_axiom_equals(CowlDisjClsAxiom const *lhs, CowlDisjClsAxiom const *rhs) {
    return kh_set_equals(CowlClsExpSet, lhs->classes, rhs->classes);
}

uint32_t cowl_disj_cls_axiom_hash(CowlDisjClsAxiom const *axiom) {
    return cowl_hash_1(COWL_HASH_INIT_DISJ_CLS_AXIOM,
                       kh_set_hash(CowlClsExpSet, axiom->classes));
}

bool cowl_disj_cls_axiom_iterate_signature(CowlDisjClsAxiom const *axiom, void *ctx,
                                           CowlEntityIterator iter) {
    kh_foreach_key(axiom->classes, CowlClsExp const *exp, {
        if (!cowl_cls_exp_iterate_signature(exp, ctx, iter)) return false;
    });
    return true;
}
