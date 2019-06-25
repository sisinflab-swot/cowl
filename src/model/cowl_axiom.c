/// @author Ivano Bilenchi

#include "cowl_axiom_private.h"
#include "cowl_annot_assert_axiom.h"
#include "cowl_annot_prop_domain_axiom.h"
#include "cowl_annot_prop_range_axiom.h"
#include "cowl_cls_assert_axiom.h"
#include "cowl_data_prop_assert_axiom.h"
#include "cowl_data_prop_domain_axiom.h"
#include "cowl_data_prop_range_axiom.h"
#include "cowl_datatype_def_axiom.h"
#include "cowl_decl_axiom.h"
#include "cowl_func_data_prop_axiom.h"
#include "cowl_has_key_axiom.h"
#include "cowl_nary_cls_axiom.h"
#include "cowl_nary_individual_axiom.h"
#include "cowl_disj_union_axiom.h"
#include "cowl_inv_obj_prop_axiom.h"
#include "cowl_nary_data_prop_axiom.h"
#include "cowl_nary_obj_prop_axiom.h"
#include "cowl_obj_prop_assert_axiom.h"
#include "cowl_obj_prop_char_axiom.h"
#include "cowl_obj_prop_domain_axiom.h"
#include "cowl_obj_prop_range_axiom.h"
#include "cowl_sub_annot_prop_axiom.h"
#include "cowl_sub_cls_axiom.h"
#include "cowl_sub_data_prop_axiom.h"
#include "cowl_sub_obj_prop_axiom.h"
#include "cowl_sub_obj_prop_chain_axiom.h"

CowlAxiom* cowl_axiom_retain(CowlAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_axiom_release(CowlAxiom *axiom) {
    if (!axiom) return;

#define GEN_CASE_RELEASE(CAT, TYPE, PREFIX) \
    case CAT: PREFIX##_release((TYPE *)axiom); break

    switch (cowl_axiom_flags_get_type(axiom->flags)) {

        GEN_CASE_RELEASE(CAT_DECLARATION, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_RELEASE(CAT_DATATYPE_DEFINITION, CowlDatatypeDefAxiom, cowl_datatype_def_axiom);
        GEN_CASE_RELEASE(CAT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_RELEASE(CAT_EQUIVALENT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_RELEASE(CAT_DISJOINT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_RELEASE(CAT_DISJOINT_UNION, CowlDisjUnionAxiom, cowl_disj_union_axiom);
        GEN_CASE_RELEASE(CAT_CLASS_ASSERTION, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_RELEASE(CAT_SAME_INDIVIDUAL, CowlNAryIndividualAxiom, cowl_nary_individual_axiom);
        GEN_CASE_RELEASE(CAT_DIFFERENT_INDIVIDUALS, CowlNAryIndividualAxiom, cowl_nary_individual_axiom);
        GEN_CASE_RELEASE(CAT_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_RELEASE(CAT_NEGATIVE_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_RELEASE(CAT_DATA_PROP_ASSERTION, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_RELEASE(CAT_NEGATIVE_DATA_PROP_ASSERTION, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_RELEASE(CAT_SUB_OBJ_PROP, CowlSubObjPropAxiom, cowl_sub_obj_prop_axiom);
        GEN_CASE_RELEASE(CAT_SUB_OBJ_PROP_CHAIN, CowlSubObjPropChainAxiom, cowl_sub_obj_prop_chain_axiom);
        GEN_CASE_RELEASE(CAT_INVERSE_OBJ_PROP, CowlInvObjPropAxiom, cowl_inv_obj_prop_axiom);
        GEN_CASE_RELEASE(CAT_EQUIVALENT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_RELEASE(CAT_DISJOINT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_RELEASE(CAT_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_INVERSE_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_SYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_ASYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_REFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_IRREFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_TRANSITIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(CAT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_RELEASE(CAT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_RELEASE(CAT_SUB_DATA_PROP, CowlSubDataPropAxiom, cowl_sub_data_prop_axiom);
        GEN_CASE_RELEASE(CAT_EQUIVALENT_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_RELEASE(CAT_DISJOINT_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_RELEASE(CAT_FUNCTIONAL_DATA_PROP, CowlFuncDataPropAxiom, cowl_func_data_prop_axiom);
        GEN_CASE_RELEASE(CAT_DATA_PROP_DOMAIN, CowlDataPropDomainAxiom, cowl_data_prop_domain_axiom);
        GEN_CASE_RELEASE(CAT_DATA_PROP_RANGE, CowlDataPropRangeAxiom, cowl_data_prop_range_axiom);
        GEN_CASE_RELEASE(CAT_HAS_KEY, CowlHasKeyAxiom, cowl_has_key_axiom);
        GEN_CASE_RELEASE(CAT_ANNOT_ASSERTION, CowlAnnotAssertAxiom, cowl_annot_assert_axiom);
        GEN_CASE_RELEASE(CAT_SUB_ANNOT_PROP, CowlSubAnnotPropAxiom, cowl_sub_annot_prop_axiom);
        GEN_CASE_RELEASE(CAT_ANNOT_PROP_DOMAIN, CowlAnnotPropDomainAxiom, cowl_annot_prop_domain_axiom);
        GEN_CASE_RELEASE(CAT_ANNOT_PROP_RANGE, CowlAnnotPropRangeAxiom, cowl_annot_prop_range_axiom);

        default:
            break;
    }
}

CowlAxiomType cowl_axiom_get_type(CowlAxiom *axiom) {
    return cowl_axiom_flags_get_type(axiom->flags);
}

bool cowl_axiom_equals(CowlAxiom *lhs, CowlAxiom *rhs) {
    if (lhs == rhs) return true;
    if (lhs->flags != rhs->flags || lhs->super.hash != rhs->super.hash) return false;

#define GEN_CASE_EQUAL(CAT, TYPE, PREFIX) \
    case CAT: return PREFIX##_equals((TYPE *)lhs, (TYPE *)rhs)

    switch (cowl_axiom_flags_get_type(lhs->flags)) {

        GEN_CASE_EQUAL(CAT_DECLARATION, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_EQUAL(CAT_DATATYPE_DEFINITION, CowlDatatypeDefAxiom, cowl_datatype_def_axiom);
        GEN_CASE_EQUAL(CAT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_EQUAL(CAT_EQUIVALENT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_EQUAL(CAT_DISJOINT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_EQUAL(CAT_DISJOINT_UNION, CowlDisjUnionAxiom, cowl_disj_union_axiom);
        GEN_CASE_EQUAL(CAT_CLASS_ASSERTION, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_EQUAL(CAT_SAME_INDIVIDUAL, CowlNAryIndividualAxiom, cowl_nary_individual_axiom);
        GEN_CASE_EQUAL(CAT_DIFFERENT_INDIVIDUALS, CowlNAryIndividualAxiom, cowl_nary_individual_axiom);
        GEN_CASE_EQUAL(CAT_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_EQUAL(CAT_NEGATIVE_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_EQUAL(CAT_DATA_PROP_ASSERTION, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_EQUAL(CAT_NEGATIVE_DATA_PROP_ASSERTION, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_EQUAL(CAT_SUB_OBJ_PROP, CowlSubObjPropAxiom, cowl_sub_obj_prop_axiom);
        GEN_CASE_EQUAL(CAT_SUB_OBJ_PROP_CHAIN, CowlSubObjPropChainAxiom, cowl_sub_obj_prop_chain_axiom);
        GEN_CASE_EQUAL(CAT_INVERSE_OBJ_PROP, CowlInvObjPropAxiom, cowl_inv_obj_prop_axiom);
        GEN_CASE_EQUAL(CAT_EQUIVALENT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_EQUAL(CAT_DISJOINT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_EQUAL(CAT_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_INVERSE_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_SYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_ASYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_REFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_IRREFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_TRANSITIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(CAT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_EQUAL(CAT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_EQUAL(CAT_SUB_DATA_PROP, CowlSubDataPropAxiom, cowl_sub_data_prop_axiom);
        GEN_CASE_EQUAL(CAT_EQUIVALENT_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_EQUAL(CAT_DISJOINT_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_EQUAL(CAT_FUNCTIONAL_DATA_PROP, CowlFuncDataPropAxiom, cowl_func_data_prop_axiom);
        GEN_CASE_EQUAL(CAT_DATA_PROP_DOMAIN, CowlDataPropDomainAxiom, cowl_data_prop_domain_axiom);
        GEN_CASE_EQUAL(CAT_DATA_PROP_RANGE, CowlDataPropRangeAxiom, cowl_data_prop_range_axiom);
        GEN_CASE_EQUAL(CAT_HAS_KEY, CowlHasKeyAxiom, cowl_has_key_axiom);
        GEN_CASE_EQUAL(CAT_ANNOT_ASSERTION, CowlAnnotAssertAxiom, cowl_annot_assert_axiom);
        GEN_CASE_EQUAL(CAT_SUB_ANNOT_PROP, CowlSubAnnotPropAxiom, cowl_sub_annot_prop_axiom);
        GEN_CASE_EQUAL(CAT_ANNOT_PROP_DOMAIN, CowlAnnotPropDomainAxiom, cowl_annot_prop_domain_axiom);
        GEN_CASE_EQUAL(CAT_ANNOT_PROP_RANGE, CowlAnnotPropRangeAxiom, cowl_annot_prop_range_axiom);

        default:
            return false;
    }
}

cowl_uint_t cowl_axiom_hash(CowlAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_axiom_iterate_signature(CowlAxiom *axiom, void *ctx, CowlEntityIterator iter) {

#define GEN_CASE_SIG(CAT, TYPE, PREFIX) \
    case CAT: return PREFIX##_iterate_signature((TYPE *)axiom, ctx, iter)

    switch (cowl_axiom_flags_get_type(axiom->flags)) {

        GEN_CASE_SIG(CAT_DECLARATION, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_SIG(CAT_DATATYPE_DEFINITION, CowlDatatypeDefAxiom, cowl_datatype_def_axiom);
        GEN_CASE_SIG(CAT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_SIG(CAT_EQUIVALENT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_SIG(CAT_DISJOINT_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_SIG(CAT_DISJOINT_UNION, CowlDisjUnionAxiom, cowl_disj_union_axiom);
        GEN_CASE_SIG(CAT_CLASS_ASSERTION, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_SIG(CAT_SAME_INDIVIDUAL, CowlNAryIndividualAxiom, cowl_nary_individual_axiom);
        GEN_CASE_SIG(CAT_DIFFERENT_INDIVIDUALS, CowlNAryIndividualAxiom, cowl_nary_individual_axiom);
        GEN_CASE_SIG(CAT_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_SIG(CAT_NEGATIVE_OBJ_PROP_ASSERTION, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_SIG(CAT_DATA_PROP_ASSERTION, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_SIG(CAT_NEGATIVE_DATA_PROP_ASSERTION, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_SIG(CAT_SUB_OBJ_PROP, CowlSubObjPropAxiom, cowl_sub_obj_prop_axiom);
        GEN_CASE_SIG(CAT_SUB_OBJ_PROP_CHAIN, CowlSubObjPropChainAxiom, cowl_sub_obj_prop_chain_axiom);
        GEN_CASE_SIG(CAT_INVERSE_OBJ_PROP, CowlInvObjPropAxiom, cowl_inv_obj_prop_axiom);
        GEN_CASE_SIG(CAT_EQUIVALENT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_SIG(CAT_DISJOINT_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_SIG(CAT_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_INVERSE_FUNCTIONAL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_SYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_ASYMMETRIC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_REFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_IRREFLEXIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_TRANSITIVE_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(CAT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_SIG(CAT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_SIG(CAT_SUB_DATA_PROP, CowlSubDataPropAxiom, cowl_sub_data_prop_axiom);
        GEN_CASE_SIG(CAT_EQUIVALENT_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_SIG(CAT_DISJOINT_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_SIG(CAT_FUNCTIONAL_DATA_PROP, CowlFuncDataPropAxiom, cowl_func_data_prop_axiom);
        GEN_CASE_SIG(CAT_DATA_PROP_DOMAIN, CowlDataPropDomainAxiom, cowl_data_prop_domain_axiom);
        GEN_CASE_SIG(CAT_DATA_PROP_RANGE, CowlDataPropRangeAxiom, cowl_data_prop_range_axiom);
        GEN_CASE_SIG(CAT_HAS_KEY, CowlHasKeyAxiom, cowl_has_key_axiom);
        GEN_CASE_SIG(CAT_ANNOT_ASSERTION, CowlAnnotAssertAxiom, cowl_annot_assert_axiom);
        GEN_CASE_SIG(CAT_SUB_ANNOT_PROP, CowlSubAnnotPropAxiom, cowl_sub_annot_prop_axiom);
        GEN_CASE_SIG(CAT_ANNOT_PROP_DOMAIN, CowlAnnotPropDomainAxiom, cowl_annot_prop_domain_axiom);
        GEN_CASE_SIG(CAT_ANNOT_PROP_RANGE, CowlAnnotPropRangeAxiom, cowl_annot_prop_range_axiom);

        default:
            return true;
    }
}
