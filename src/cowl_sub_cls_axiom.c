/// @author Ivano Bilenchi

#include "cowl_sub_cls_axiom_private.h"
#include "cowl_class_exp_private.h"
#include "cowl_hash_utils.h"

CowlClassExp const* cowl_sub_cls_axiom_get_super(CowlSubClsAxiom const *axiom) {
    return axiom->super_class;
}

CowlClassExp const* cowl_sub_cls_axiom_get_sub(CowlSubClsAxiom const *axiom) {
    return axiom->sub_class;
}

bool cowl_sub_cls_axiom_equals(CowlSubClsAxiom const *lhs, CowlSubClsAxiom const *rhs) {
    return cowl_class_exp_equals(lhs->sub_class, rhs->sub_class) &&
           cowl_class_exp_equals(lhs->super_class, rhs->super_class);
}

uint32_t cowl_sub_cls_axiom_hash(CowlSubClsAxiom const *axiom) {
    return cowl_hash_2(COWL_HASH_INIT_SUBCLASS_AXIOM,
                       cowl_class_exp_hash(axiom->super_class),
                       cowl_class_exp_hash(axiom->sub_class));
}
