/// @author Ivano Bilenchi

#include "cowl_axiom_private.h"
#include "cowl_cls_assert_axiom.h"
#include "cowl_decl_axiom.h"
#include "cowl_disj_cls_axiom.h"
#include "cowl_eq_cls_axiom.h"
#include "cowl_obj_prop_assert_axiom.h"
#include "cowl_obj_prop_domain_axiom.h"
#include "cowl_obj_prop_range_axiom.h"
#include "cowl_sub_cls_axiom.h"

CowlAxiom const* cowl_axiom_retain(CowlAxiom const *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_axiom_release(CowlAxiom const *axiom) {
    if (!axiom) return;

#define GEN_CASE_RELEASE(CAT, TYPE, PREFIX) \
    case CAT: PREFIX##_release((TYPE *)axiom);

    switch (axiom->type) {

        GEN_CASE_RELEASE(CAT_DECLARATION, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_RELEASE(CAT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_RELEASE(CAT_EQUIVALENT_CLASSES, CowlEqClsAxiom, cowl_eq_cls_axiom);
        GEN_CASE_RELEASE(CAT_DISJOINT_CLASSES, CowlDisjClsAxiom, cowl_disj_cls_axiom);
        GEN_CASE_RELEASE(CAT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_RELEASE(CAT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_RELEASE(CAT_CLASS_ASSERTION, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_RELEASE(CAT_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);

        default:
            break;
    }
}

CowlAxiomType cowl_axiom_get_type(CowlAxiom const *axiom) {
    return axiom->type;
}

bool cowl_axiom_equals(CowlAxiom const *lhs, CowlAxiom const *rhs) {
    if (lhs->type != rhs->type) return false;

#define GEN_CASE_EQUAL(CAT, TYPE, PREFIX) \
    case CAT: return PREFIX##_equals((TYPE *)lhs, (TYPE *)rhs)

    switch (lhs->type) {

        GEN_CASE_EQUAL(CAT_DECLARATION, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_EQUAL(CAT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_EQUAL(CAT_EQUIVALENT_CLASSES, CowlEqClsAxiom, cowl_eq_cls_axiom);
        GEN_CASE_EQUAL(CAT_DISJOINT_CLASSES, CowlDisjClsAxiom, cowl_disj_cls_axiom);
        GEN_CASE_EQUAL(CAT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_EQUAL(CAT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_EQUAL(CAT_CLASS_ASSERTION, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_EQUAL(CAT_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);

        default:
            return false;
    }
}

uint32_t cowl_axiom_hash(CowlAxiom const *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_axiom_iterate_signature(CowlAxiom const *axiom, void *ctx, CowlEntityIterator iter) {

#define GEN_CASE_SIG(CAT, TYPE, PREFIX) \
    case CAT: return PREFIX##_iterate_signature((TYPE *)axiom, ctx, iter)

    switch (axiom->type) {

        GEN_CASE_SIG(CAT_DECLARATION, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_SIG(CAT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_SIG(CAT_EQUIVALENT_CLASSES, CowlEqClsAxiom, cowl_eq_cls_axiom);
        GEN_CASE_SIG(CAT_DISJOINT_CLASSES, CowlDisjClsAxiom, cowl_disj_cls_axiom);
        GEN_CASE_SIG(CAT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_SIG(CAT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_SIG(CAT_CLASS_ASSERTION, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_SIG(CAT_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);

        default:
            return true;
    }
}
