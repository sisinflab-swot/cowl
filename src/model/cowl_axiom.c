/// @author Ivano Bilenchi

#include "cowl_axiom_private.h"
#include "cowl_cls_assert_axiom.h"
#include "cowl_decl_axiom.h"
#include "cowl_nary_cls_axiom.h"
#include "cowl_disj_union_axiom.h"
#include "cowl_inv_obj_prop_axiom.h"
#include "cowl_nary_obj_prop_axiom.h"
#include "cowl_obj_prop_assert_axiom.h"
#include "cowl_obj_prop_char_axiom.h"
#include "cowl_obj_prop_domain_axiom.h"
#include "cowl_obj_prop_range_axiom.h"
#include "cowl_sub_cls_axiom.h"
#include "cowl_sub_obj_prop_axiom.h"

CowlAxiom* cowl_axiom_retain(CowlAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_axiom_release(CowlAxiom *axiom) {
    if (!axiom) return;

#define GEN_CASE_RELEASE(CAT, TYPE, PREFIX) \
    case CAT: PREFIX##_release((TYPE *)axiom); break

    switch (axiom->type) {

        GEN_CASE_RELEASE(CAT_DECLARATION, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_RELEASE(CAT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_RELEASE(CAT_EQUIVALENT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_RELEASE(CAT_DISJOINT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_RELEASE(CAT_DISJOINT_UNION, CowlDisjUnionAxiom, cowl_disj_union_axiom);
        GEN_CASE_RELEASE(CAT_CLASS_ASSERTION, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_RELEASE(CAT_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_RELEASE(CAT_NEGATIVE_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_RELEASE(CAT_SUB_OBJ_PROP, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_RELEASE(CAT_INVERSE_OBJ_PROP, CowlInvObjPropAxiom, cowl_inv_obj_prop_axiom);
        GEN_CASE_RELEASE(CAT_EQUIVALENT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_RELEASE(CAT_DISJOINT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_RELEASE(CAT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_RELEASE(CAT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_RELEASE(CAT_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_INVERSE_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_SYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_ASYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_REFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_IRREFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_TRANSITIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);

        default:
            break;
    }
}

CowlAxiomType cowl_axiom_get_type(CowlAxiom *axiom) {
    return axiom->type;
}

bool cowl_axiom_equals(CowlAxiom *lhs, CowlAxiom *rhs) {
    if (lhs == rhs) return true;
    if (lhs->type != rhs->type || lhs->super.hash != rhs->super.hash) return false;

#define GEN_CASE_EQUAL(CAT, TYPE, PREFIX) \
    case CAT: return PREFIX##_equals((TYPE *)lhs, (TYPE *)rhs)

    switch (lhs->type) {

        GEN_CASE_EQUAL(CAT_DECLARATION, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_EQUAL(CAT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_EQUAL(CAT_EQUIVALENT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_EQUAL(CAT_DISJOINT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_EQUAL(CAT_DISJOINT_UNION, CowlDisjUnionAxiom, cowl_disj_union_axiom);
        GEN_CASE_EQUAL(CAT_CLASS_ASSERTION, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_EQUAL(CAT_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_EQUAL(CAT_NEGATIVE_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_EQUAL(CAT_SUB_OBJ_PROP, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_EQUAL(CAT_INVERSE_OBJ_PROP, CowlInvObjPropAxiom, cowl_inv_obj_prop_axiom);
        GEN_CASE_EQUAL(CAT_EQUIVALENT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_EQUAL(CAT_DISJOINT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_EQUAL(CAT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_EQUAL(CAT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_EQUAL(CAT_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_INVERSE_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_SYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_ASYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_REFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_IRREFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_TRANSITIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);

        default:
            return false;
    }
}

cowl_uint_t cowl_axiom_hash(CowlAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_axiom_iterate_signature(CowlAxiom *axiom, void *ctx, CowlEntityIterator iter) {

#define GEN_CASE_SIG(CAT, TYPE, PREFIX) \
    case CAT: return PREFIX##_iterate_signature((TYPE *)axiom, ctx, iter)

    switch (axiom->type) {

        GEN_CASE_SIG(CAT_DECLARATION, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_SIG(CAT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_SIG(CAT_EQUIVALENT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_SIG(CAT_DISJOINT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_SIG(CAT_DISJOINT_UNION, CowlDisjUnionAxiom, cowl_disj_union_axiom);
        GEN_CASE_SIG(CAT_CLASS_ASSERTION, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_SIG(CAT_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_SIG(CAT_NEGATIVE_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_SIG(CAT_SUB_OBJ_PROP, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_SIG(CAT_INVERSE_OBJ_PROP, CowlInvObjPropAxiom, cowl_inv_obj_prop_axiom);
        GEN_CASE_SIG(CAT_EQUIVALENT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_SIG(CAT_DISJOINT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_SIG(CAT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_SIG(CAT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_SIG(CAT_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_INVERSE_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_SYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_ASYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_REFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_IRREFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_TRANSITIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);

        default:
            return true;
    }
}
