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
#include "cowl_nary_ind_axiom.h"
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

        GEN_CASE_RELEASE(COWL_AT_DECL, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_RELEASE(COWL_AT_DATATYPE_DEF, CowlDatatypeDefAxiom, cowl_datatype_def_axiom);
        GEN_CASE_RELEASE(COWL_AT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_RELEASE(COWL_AT_EQUIV_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_RELEASE(COWL_AT_DISJ_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_RELEASE(COWL_AT_DISJ_UNION, CowlDisjUnionAxiom, cowl_disj_union_axiom);
        GEN_CASE_RELEASE(COWL_AT_CLASS_ASSERT, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_RELEASE(COWL_AT_SAME_IND, CowlNAryIndAxiom, cowl_nary_ind_axiom);
        GEN_CASE_RELEASE(COWL_AT_DIFF_IND, CowlNAryIndAxiom, cowl_nary_ind_axiom);
        GEN_CASE_RELEASE(COWL_AT_OBJ_PROP_ASSERT, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_RELEASE(COWL_AT_NEG_OBJ_PROP_ASSERT, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_RELEASE(COWL_AT_DATA_PROP_ASSERT, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_RELEASE(COWL_AT_NEG_DATA_PROP_ASSERT, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_RELEASE(COWL_AT_SUB_OBJ_PROP, CowlSubObjPropAxiom, cowl_sub_obj_prop_axiom);
        GEN_CASE_RELEASE(COWL_AT_SUB_OBJ_PROP_CHAIN, CowlSubObjPropChainAxiom, cowl_sub_obj_prop_chain_axiom);
        GEN_CASE_RELEASE(COWL_AT_INV_OBJ_PROP, CowlInvObjPropAxiom, cowl_inv_obj_prop_axiom);
        GEN_CASE_RELEASE(COWL_AT_EQUIV_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_RELEASE(COWL_AT_DISJ_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_RELEASE(COWL_AT_FUNC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(COWL_AT_INV_FUNC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(COWL_AT_SYMM_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(COWL_AT_ASYMM_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(COWL_AT_REFL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(COWL_AT_IRREFL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(COWL_AT_TRANS_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_RELEASE(COWL_AT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_RELEASE(COWL_AT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_RELEASE(COWL_AT_SUB_DATA_PROP, CowlSubDataPropAxiom, cowl_sub_data_prop_axiom);
        GEN_CASE_RELEASE(COWL_AT_EQUIV_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_RELEASE(COWL_AT_DISJ_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_RELEASE(COWL_AT_FUNC_DATA_PROP, CowlFuncDataPropAxiom, cowl_func_data_prop_axiom);
        GEN_CASE_RELEASE(COWL_AT_DATA_PROP_DOMAIN, CowlDataPropDomainAxiom, cowl_data_prop_domain_axiom);
        GEN_CASE_RELEASE(COWL_AT_DATA_PROP_RANGE, CowlDataPropRangeAxiom, cowl_data_prop_range_axiom);
        GEN_CASE_RELEASE(COWL_AT_HAS_KEY, CowlHasKeyAxiom, cowl_has_key_axiom);
        GEN_CASE_RELEASE(COWL_AT_ANNOT_ASSERT, CowlAnnotAssertAxiom, cowl_annot_assert_axiom);
        GEN_CASE_RELEASE(COWL_AT_SUB_ANNOT_PROP, CowlSubAnnotPropAxiom, cowl_sub_annot_prop_axiom);
        GEN_CASE_RELEASE(COWL_AT_ANNOT_PROP_DOMAIN, CowlAnnotPropDomainAxiom, cowl_annot_prop_domain_axiom);
        GEN_CASE_RELEASE(COWL_AT_ANNOT_PROP_RANGE, CowlAnnotPropRangeAxiom, cowl_annot_prop_range_axiom);

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

        GEN_CASE_EQUAL(COWL_AT_DECL, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_EQUAL(COWL_AT_DATATYPE_DEF, CowlDatatypeDefAxiom, cowl_datatype_def_axiom);
        GEN_CASE_EQUAL(COWL_AT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_EQUAL(COWL_AT_EQUIV_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_EQUAL(COWL_AT_DISJ_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_EQUAL(COWL_AT_DISJ_UNION, CowlDisjUnionAxiom, cowl_disj_union_axiom);
        GEN_CASE_EQUAL(COWL_AT_CLASS_ASSERT, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_EQUAL(COWL_AT_SAME_IND, CowlNAryIndAxiom, cowl_nary_ind_axiom);
        GEN_CASE_EQUAL(COWL_AT_DIFF_IND, CowlNAryIndAxiom, cowl_nary_ind_axiom);
        GEN_CASE_EQUAL(COWL_AT_OBJ_PROP_ASSERT, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_EQUAL(COWL_AT_NEG_OBJ_PROP_ASSERT, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_EQUAL(COWL_AT_DATA_PROP_ASSERT, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_EQUAL(COWL_AT_NEG_DATA_PROP_ASSERT, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_EQUAL(COWL_AT_SUB_OBJ_PROP, CowlSubObjPropAxiom, cowl_sub_obj_prop_axiom);
        GEN_CASE_EQUAL(COWL_AT_SUB_OBJ_PROP_CHAIN, CowlSubObjPropChainAxiom, cowl_sub_obj_prop_chain_axiom);
        GEN_CASE_EQUAL(COWL_AT_INV_OBJ_PROP, CowlInvObjPropAxiom, cowl_inv_obj_prop_axiom);
        GEN_CASE_EQUAL(COWL_AT_EQUIV_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_EQUAL(COWL_AT_DISJ_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_EQUAL(COWL_AT_FUNC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(COWL_AT_INV_FUNC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(COWL_AT_SYMM_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(COWL_AT_ASYMM_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(COWL_AT_REFL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(COWL_AT_IRREFL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(COWL_AT_TRANS_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_EQUAL(COWL_AT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_EQUAL(COWL_AT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_EQUAL(COWL_AT_SUB_DATA_PROP, CowlSubDataPropAxiom, cowl_sub_data_prop_axiom);
        GEN_CASE_EQUAL(COWL_AT_EQUIV_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_EQUAL(COWL_AT_DISJ_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_EQUAL(COWL_AT_FUNC_DATA_PROP, CowlFuncDataPropAxiom, cowl_func_data_prop_axiom);
        GEN_CASE_EQUAL(COWL_AT_DATA_PROP_DOMAIN, CowlDataPropDomainAxiom, cowl_data_prop_domain_axiom);
        GEN_CASE_EQUAL(COWL_AT_DATA_PROP_RANGE, CowlDataPropRangeAxiom, cowl_data_prop_range_axiom);
        GEN_CASE_EQUAL(COWL_AT_HAS_KEY, CowlHasKeyAxiom, cowl_has_key_axiom);
        GEN_CASE_EQUAL(COWL_AT_ANNOT_ASSERT, CowlAnnotAssertAxiom, cowl_annot_assert_axiom);
        GEN_CASE_EQUAL(COWL_AT_SUB_ANNOT_PROP, CowlSubAnnotPropAxiom, cowl_sub_annot_prop_axiom);
        GEN_CASE_EQUAL(COWL_AT_ANNOT_PROP_DOMAIN, CowlAnnotPropDomainAxiom, cowl_annot_prop_domain_axiom);
        GEN_CASE_EQUAL(COWL_AT_ANNOT_PROP_RANGE, CowlAnnotPropRangeAxiom, cowl_annot_prop_range_axiom);

        default:
            return false;
    }
}

cowl_uint_t cowl_axiom_hash(CowlAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_axiom_iterate_signature(CowlAxiom *axiom, CowlEntityIterator *iter) {

#define GEN_CASE_SIG(CAT, TYPE, PREFIX) \
    case CAT: return PREFIX##_iterate_signature((TYPE *)axiom, iter)

    switch (cowl_axiom_flags_get_type(axiom->flags)) {

        GEN_CASE_SIG(COWL_AT_DECL, CowlDeclAxiom, cowl_decl_axiom);
        GEN_CASE_SIG(COWL_AT_DATATYPE_DEF, CowlDatatypeDefAxiom, cowl_datatype_def_axiom);
        GEN_CASE_SIG(COWL_AT_SUB_CLASS, CowlSubClsAxiom, cowl_sub_cls_axiom);
        GEN_CASE_SIG(COWL_AT_EQUIV_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_SIG(COWL_AT_DISJ_CLASSES, CowlNAryClsAxiom, cowl_nary_cls_axiom);
        GEN_CASE_SIG(COWL_AT_DISJ_UNION, CowlDisjUnionAxiom, cowl_disj_union_axiom);
        GEN_CASE_SIG(COWL_AT_CLASS_ASSERT, CowlClsAssertAxiom, cowl_cls_assert_axiom);
        GEN_CASE_SIG(COWL_AT_SAME_IND, CowlNAryIndAxiom, cowl_nary_ind_axiom);
        GEN_CASE_SIG(COWL_AT_DIFF_IND, CowlNAryIndAxiom, cowl_nary_ind_axiom);
        GEN_CASE_SIG(COWL_AT_OBJ_PROP_ASSERT, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_SIG(COWL_AT_NEG_OBJ_PROP_ASSERT, CowlObjPropAssertAxiom, cowl_obj_prop_assert_axiom);
        GEN_CASE_SIG(COWL_AT_DATA_PROP_ASSERT, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_SIG(COWL_AT_NEG_DATA_PROP_ASSERT, CowlDataPropAssertAxiom, cowl_data_prop_assert_axiom);
        GEN_CASE_SIG(COWL_AT_SUB_OBJ_PROP, CowlSubObjPropAxiom, cowl_sub_obj_prop_axiom);
        GEN_CASE_SIG(COWL_AT_SUB_OBJ_PROP_CHAIN, CowlSubObjPropChainAxiom, cowl_sub_obj_prop_chain_axiom);
        GEN_CASE_SIG(COWL_AT_INV_OBJ_PROP, CowlInvObjPropAxiom, cowl_inv_obj_prop_axiom);
        GEN_CASE_SIG(COWL_AT_EQUIV_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_SIG(COWL_AT_DISJ_OBJ_PROP, CowlNAryObjPropAxiom, cowl_nary_obj_prop_axiom);
        GEN_CASE_SIG(COWL_AT_FUNC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(COWL_AT_INV_FUNC_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(COWL_AT_SYMM_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(COWL_AT_ASYMM_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(COWL_AT_REFL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(COWL_AT_IRREFL_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(COWL_AT_TRANS_OBJ_PROP, CowlObjPropCharAxiom, cowl_obj_prop_char_axiom);
        GEN_CASE_SIG(COWL_AT_OBJ_PROP_DOMAIN, CowlObjPropDomainAxiom, cowl_obj_prop_domain_axiom);
        GEN_CASE_SIG(COWL_AT_OBJ_PROP_RANGE, CowlObjPropRangeAxiom, cowl_obj_prop_range_axiom);
        GEN_CASE_SIG(COWL_AT_SUB_DATA_PROP, CowlSubDataPropAxiom, cowl_sub_data_prop_axiom);
        GEN_CASE_SIG(COWL_AT_EQUIV_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_SIG(COWL_AT_DISJ_DATA_PROP, CowlNAryDataPropAxiom, cowl_nary_data_prop_axiom);
        GEN_CASE_SIG(COWL_AT_FUNC_DATA_PROP, CowlFuncDataPropAxiom, cowl_func_data_prop_axiom);
        GEN_CASE_SIG(COWL_AT_DATA_PROP_DOMAIN, CowlDataPropDomainAxiom, cowl_data_prop_domain_axiom);
        GEN_CASE_SIG(COWL_AT_DATA_PROP_RANGE, CowlDataPropRangeAxiom, cowl_data_prop_range_axiom);
        GEN_CASE_SIG(COWL_AT_HAS_KEY, CowlHasKeyAxiom, cowl_has_key_axiom);
        GEN_CASE_SIG(COWL_AT_ANNOT_ASSERT, CowlAnnotAssertAxiom, cowl_annot_assert_axiom);
        GEN_CASE_SIG(COWL_AT_SUB_ANNOT_PROP, CowlSubAnnotPropAxiom, cowl_sub_annot_prop_axiom);
        GEN_CASE_SIG(COWL_AT_ANNOT_PROP_DOMAIN, CowlAnnotPropDomainAxiom, cowl_annot_prop_domain_axiom);
        GEN_CASE_SIG(COWL_AT_ANNOT_PROP_RANGE, CowlAnnotPropRangeAxiom, cowl_annot_prop_range_axiom);

        default:
            return true;
    }
}
