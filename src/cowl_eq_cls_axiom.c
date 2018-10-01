/// @author Ivano Bilenchi

#include "cowl_eq_cls_axiom_private.h"
#include "cowl_cls_exp_private.h"
#include "cowl_hash_utils.h"

khash_t(CowlClsExpSet) const* cowl_eq_cls_axiom_get_classes(CowlEqClsAxiom const *axiom) {
    return axiom->classes;
}

bool cowl_eq_cls_axiom_equals(CowlEqClsAxiom const *lhs, CowlEqClsAxiom const *rhs) {
    return kh_set_equals(CowlClsExpSet, lhs->classes, rhs->classes);
}

uint32_t cowl_eq_cls_axiom_hash(CowlEqClsAxiom const *axiom) {
    return cowl_hash_1(COWL_HASH_INIT_EQ_CLS_AXIOM,
                       kh_set_hash(CowlClsExpSet, axiom->classes));
}
