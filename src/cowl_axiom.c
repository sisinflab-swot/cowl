/// @author Ivano Bilenchi

#include "cowl_axiom_private.h"
#include "cowl_disj_cls_axiom.h"
#include "cowl_eq_cls_axiom.h"
#include "cowl_sub_cls_axiom.h"

CowlAxiomType cowl_axiom_get_type(CowlAxiom const *axiom) {
    return axiom->type;
}

bool cowl_axiom_equals(CowlAxiom const *lhs, CowlAxiom const *rhs) {
    if (lhs->type != rhs->type) return false;

    switch (lhs->type) {

        case CAT_SUBCLASS:
            return cowl_sub_cls_axiom_equals((CowlSubClsAxiom *)lhs, (CowlSubClsAxiom *)rhs);

        case CAT_EQUIVALENT_CLASSES:
            return cowl_eq_cls_axiom_equals((CowlEqClsAxiom *)lhs, (CowlEqClsAxiom *)rhs);

        case CAT_DISJOINT_CLASSES:
            return cowl_disj_cls_axiom_equals((CowlDisjClsAxiom *)lhs, (CowlDisjClsAxiom *)rhs);

        default:
            return false;
    }
}

uint32_t cowl_axiom_hash(CowlAxiom const *axiom) {
    switch (axiom->type) {

        case CAT_SUBCLASS:
            return cowl_sub_cls_axiom_hash((CowlSubClsAxiom *)axiom);

        case CAT_EQUIVALENT_CLASSES:
            return cowl_eq_cls_axiom_hash((CowlEqClsAxiom *)axiom);

        case CAT_DISJOINT_CLASSES:
            return cowl_disj_cls_axiom_hash((CowlDisjClsAxiom *)axiom);

        default:
            return 0;
    }
}
