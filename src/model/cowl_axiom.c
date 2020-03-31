/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

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
#include "cowl_str_buf.h"
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

#define GEN_RELEASE(UC, LC) cowl_##LC##_axiom_release((Cowl##UC##Axiom *)axiom); break

    switch (cowl_axiom_flags_get_type(axiom->flags)) {
        case COWL_AT_DECL: GEN_RELEASE(Decl, decl);
        case COWL_AT_DATATYPE_DEF: GEN_RELEASE(DatatypeDef, datatype_def);
        case COWL_AT_SUB_CLASS: GEN_RELEASE(SubCls, sub_cls);
        case COWL_AT_EQUIV_CLASSES:
        case COWL_AT_DISJ_CLASSES: GEN_RELEASE(NAryCls, nary_cls);
        case COWL_AT_DISJ_UNION: GEN_RELEASE(DisjUnion, disj_union);
        case COWL_AT_CLASS_ASSERT: GEN_RELEASE(ClsAssert, cls_assert);
        case COWL_AT_SAME_IND:
        case COWL_AT_DIFF_IND: GEN_RELEASE(NAryInd, nary_ind);
        case COWL_AT_OBJ_PROP_ASSERT:
        case COWL_AT_NEG_OBJ_PROP_ASSERT: GEN_RELEASE(ObjPropAssert, obj_prop_assert);
        case COWL_AT_DATA_PROP_ASSERT:
        case COWL_AT_NEG_DATA_PROP_ASSERT: GEN_RELEASE(DataPropAssert, data_prop_assert);
        case COWL_AT_SUB_OBJ_PROP: GEN_RELEASE(SubObjProp, sub_obj_prop);
        case COWL_AT_SUB_OBJ_PROP_CHAIN: GEN_RELEASE(SubObjPropChain, sub_obj_prop_chain);
        case COWL_AT_INV_OBJ_PROP: GEN_RELEASE(InvObjProp, inv_obj_prop);
        case COWL_AT_EQUIV_OBJ_PROP:
        case COWL_AT_DISJ_OBJ_PROP: GEN_RELEASE(NAryObjProp, nary_obj_prop);
        case COWL_AT_FUNC_OBJ_PROP:
        case COWL_AT_INV_FUNC_OBJ_PROP:
        case COWL_AT_SYMM_OBJ_PROP:
        case COWL_AT_ASYMM_OBJ_PROP:
        case COWL_AT_REFL_OBJ_PROP:
        case COWL_AT_IRREFL_OBJ_PROP:
        case COWL_AT_TRANS_OBJ_PROP: GEN_RELEASE(ObjPropChar, obj_prop_char);
        case COWL_AT_OBJ_PROP_DOMAIN: GEN_RELEASE(ObjPropDomain, obj_prop_domain);
        case COWL_AT_OBJ_PROP_RANGE: GEN_RELEASE(ObjPropRange, obj_prop_range);
        case COWL_AT_SUB_DATA_PROP: GEN_RELEASE(SubDataProp, sub_data_prop);
        case COWL_AT_EQUIV_DATA_PROP:
        case COWL_AT_DISJ_DATA_PROP: GEN_RELEASE(NAryDataProp, nary_data_prop);
        case COWL_AT_FUNC_DATA_PROP: GEN_RELEASE(FuncDataProp, func_data_prop);
        case COWL_AT_DATA_PROP_DOMAIN: GEN_RELEASE(DataPropDomain, data_prop_domain);
        case COWL_AT_DATA_PROP_RANGE: GEN_RELEASE(DataPropRange, data_prop_range);
        case COWL_AT_HAS_KEY: GEN_RELEASE(HasKey, has_key);
        case COWL_AT_ANNOT_ASSERT: GEN_RELEASE(AnnotAssert, annot_assert);
        case COWL_AT_SUB_ANNOT_PROP: GEN_RELEASE(SubAnnotProp, sub_annot_prop);
        case COWL_AT_ANNOT_PROP_DOMAIN: GEN_RELEASE(AnnotPropDomain, annot_prop_domain);
        case COWL_AT_ANNOT_PROP_RANGE: GEN_RELEASE(AnnotPropRange, annot_prop_range);
        default: break;
    }
}

CowlAxiomType cowl_axiom_get_type(CowlAxiom *axiom) {
    return cowl_axiom_flags_get_type(axiom->flags);
}

CowlString* cowl_axiom_to_string(CowlAxiom *axiom) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_axiom(buf, axiom);
    return cowl_str_buf_to_string(buf);
}

bool cowl_axiom_equals(CowlAxiom *lhs, CowlAxiom *rhs) {
    if (lhs == rhs) return true;
    if (lhs->flags != rhs->flags || lhs->super.hash != rhs->super.hash) return false;

#define GEN_EQUAL(UC, LC) \
    return cowl_##LC##_axiom_equals((Cowl##UC##Axiom *)lhs, (Cowl##UC##Axiom *)rhs)

    switch (cowl_axiom_flags_get_type(lhs->flags)) {
        case COWL_AT_DECL: GEN_EQUAL(Decl, decl);
        case COWL_AT_DATATYPE_DEF: GEN_EQUAL(DatatypeDef, datatype_def);
        case COWL_AT_SUB_CLASS: GEN_EQUAL(SubCls, sub_cls);
        case COWL_AT_EQUIV_CLASSES:
        case COWL_AT_DISJ_CLASSES: GEN_EQUAL(NAryCls, nary_cls);
        case COWL_AT_DISJ_UNION: GEN_EQUAL(DisjUnion, disj_union);
        case COWL_AT_CLASS_ASSERT: GEN_EQUAL(ClsAssert, cls_assert);
        case COWL_AT_SAME_IND:
        case COWL_AT_DIFF_IND: GEN_EQUAL(NAryInd, nary_ind);
        case COWL_AT_OBJ_PROP_ASSERT:
        case COWL_AT_NEG_OBJ_PROP_ASSERT: GEN_EQUAL(ObjPropAssert, obj_prop_assert);
        case COWL_AT_DATA_PROP_ASSERT:
        case COWL_AT_NEG_DATA_PROP_ASSERT: GEN_EQUAL(DataPropAssert, data_prop_assert);
        case COWL_AT_SUB_OBJ_PROP: GEN_EQUAL(SubObjProp, sub_obj_prop);
        case COWL_AT_SUB_OBJ_PROP_CHAIN: GEN_EQUAL(SubObjPropChain, sub_obj_prop_chain);
        case COWL_AT_INV_OBJ_PROP: GEN_EQUAL(InvObjProp, inv_obj_prop);
        case COWL_AT_EQUIV_OBJ_PROP:
        case COWL_AT_DISJ_OBJ_PROP: GEN_EQUAL(NAryObjProp, nary_obj_prop);
        case COWL_AT_FUNC_OBJ_PROP:
        case COWL_AT_INV_FUNC_OBJ_PROP:
        case COWL_AT_SYMM_OBJ_PROP:
        case COWL_AT_ASYMM_OBJ_PROP:
        case COWL_AT_REFL_OBJ_PROP:
        case COWL_AT_IRREFL_OBJ_PROP:
        case COWL_AT_TRANS_OBJ_PROP: GEN_EQUAL(ObjPropChar, obj_prop_char);
        case COWL_AT_OBJ_PROP_DOMAIN: GEN_EQUAL(ObjPropDomain, obj_prop_domain);
        case COWL_AT_OBJ_PROP_RANGE: GEN_EQUAL(ObjPropRange, obj_prop_range);
        case COWL_AT_SUB_DATA_PROP: GEN_EQUAL(SubDataProp, sub_data_prop);
        case COWL_AT_EQUIV_DATA_PROP:
        case COWL_AT_DISJ_DATA_PROP: GEN_EQUAL(NAryDataProp, nary_data_prop);
        case COWL_AT_FUNC_DATA_PROP: GEN_EQUAL(FuncDataProp, func_data_prop);
        case COWL_AT_DATA_PROP_DOMAIN: GEN_EQUAL(DataPropDomain, data_prop_domain);
        case COWL_AT_DATA_PROP_RANGE: GEN_EQUAL(DataPropRange, data_prop_range);
        case COWL_AT_HAS_KEY: GEN_EQUAL(HasKey, has_key);
        case COWL_AT_ANNOT_ASSERT: GEN_EQUAL(AnnotAssert, annot_assert);
        case COWL_AT_SUB_ANNOT_PROP: GEN_EQUAL(SubAnnotProp, sub_annot_prop);
        case COWL_AT_ANNOT_PROP_DOMAIN: GEN_EQUAL(AnnotPropDomain, annot_prop_domain);
        case COWL_AT_ANNOT_PROP_RANGE: GEN_EQUAL(AnnotPropRange, annot_prop_range);
        default: return false;
    }
}

cowl_uint_t cowl_axiom_hash(CowlAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_axiom_iterate_signature(CowlAxiom *axiom, CowlEntityIterator *iter) {

#define GEN_SIG(UC, LC) return cowl_##LC##_axiom_iterate_signature((Cowl##UC##Axiom *)axiom, iter)

    switch (cowl_axiom_flags_get_type(axiom->flags)) {
        case COWL_AT_DECL: GEN_SIG(Decl, decl);
        case COWL_AT_DATATYPE_DEF: GEN_SIG(DatatypeDef, datatype_def);
        case COWL_AT_SUB_CLASS: GEN_SIG(SubCls, sub_cls);
        case COWL_AT_EQUIV_CLASSES:
        case COWL_AT_DISJ_CLASSES: GEN_SIG(NAryCls, nary_cls);
        case COWL_AT_DISJ_UNION: GEN_SIG(DisjUnion, disj_union);
        case COWL_AT_CLASS_ASSERT: GEN_SIG(ClsAssert, cls_assert);
        case COWL_AT_SAME_IND:
        case COWL_AT_DIFF_IND: GEN_SIG(NAryInd, nary_ind);
        case COWL_AT_OBJ_PROP_ASSERT:
        case COWL_AT_NEG_OBJ_PROP_ASSERT: GEN_SIG(ObjPropAssert, obj_prop_assert);
        case COWL_AT_DATA_PROP_ASSERT:
        case COWL_AT_NEG_DATA_PROP_ASSERT: GEN_SIG(DataPropAssert, data_prop_assert);
        case COWL_AT_SUB_OBJ_PROP: GEN_SIG(SubObjProp, sub_obj_prop);
        case COWL_AT_SUB_OBJ_PROP_CHAIN: GEN_SIG(SubObjPropChain, sub_obj_prop_chain);
        case COWL_AT_INV_OBJ_PROP: GEN_SIG(InvObjProp, inv_obj_prop);
        case COWL_AT_EQUIV_OBJ_PROP:
        case COWL_AT_DISJ_OBJ_PROP: GEN_SIG(NAryObjProp, nary_obj_prop);
        case COWL_AT_FUNC_OBJ_PROP:
        case COWL_AT_INV_FUNC_OBJ_PROP:
        case COWL_AT_SYMM_OBJ_PROP:
        case COWL_AT_ASYMM_OBJ_PROP:
        case COWL_AT_REFL_OBJ_PROP:
        case COWL_AT_IRREFL_OBJ_PROP:
        case COWL_AT_TRANS_OBJ_PROP: GEN_SIG(ObjPropChar, obj_prop_char);
        case COWL_AT_OBJ_PROP_DOMAIN: GEN_SIG(ObjPropDomain, obj_prop_domain);
        case COWL_AT_OBJ_PROP_RANGE: GEN_SIG(ObjPropRange, obj_prop_range);
        case COWL_AT_SUB_DATA_PROP: GEN_SIG(SubDataProp, sub_data_prop);
        case COWL_AT_EQUIV_DATA_PROP:
        case COWL_AT_DISJ_DATA_PROP: GEN_SIG(NAryDataProp, nary_data_prop);
        case COWL_AT_FUNC_DATA_PROP: GEN_SIG(FuncDataProp, func_data_prop);
        case COWL_AT_DATA_PROP_DOMAIN: GEN_SIG(DataPropDomain, data_prop_domain);
        case COWL_AT_DATA_PROP_RANGE: GEN_SIG(DataPropRange, data_prop_range);
        case COWL_AT_HAS_KEY: GEN_SIG(HasKey, has_key);
        case COWL_AT_ANNOT_ASSERT: GEN_SIG(AnnotAssert, annot_assert);
        case COWL_AT_SUB_ANNOT_PROP: GEN_SIG(SubAnnotProp, sub_annot_prop);
        case COWL_AT_ANNOT_PROP_DOMAIN: GEN_SIG(AnnotPropDomain, annot_prop_domain);
        case COWL_AT_ANNOT_PROP_RANGE: GEN_SIG(AnnotPropRange, annot_prop_range);
        default: return true;
    }
}

bool cowl_axiom_iterate_anon_inds(CowlAxiom *axiom, CowlAnonIndIterator *iter) {

#define GEN_ANON(UC, LC) return cowl_##LC##_axiom_iterate_anon_inds((Cowl##UC##Axiom *)axiom, iter)

    switch (cowl_axiom_flags_get_type(axiom->flags)) {
        case COWL_AT_DECL: GEN_ANON(Decl, decl);
        case COWL_AT_DATATYPE_DEF: GEN_ANON(DatatypeDef, datatype_def);
        case COWL_AT_SUB_CLASS: GEN_ANON(SubCls, sub_cls);
        case COWL_AT_EQUIV_CLASSES:
        case COWL_AT_DISJ_CLASSES: GEN_ANON(NAryCls, nary_cls);
        case COWL_AT_DISJ_UNION: GEN_ANON(DisjUnion, disj_union);
        case COWL_AT_CLASS_ASSERT: GEN_ANON(ClsAssert, cls_assert);
        case COWL_AT_SAME_IND:
        case COWL_AT_DIFF_IND: GEN_ANON(NAryInd, nary_ind);
        case COWL_AT_OBJ_PROP_ASSERT:
        case COWL_AT_NEG_OBJ_PROP_ASSERT: GEN_ANON(ObjPropAssert, obj_prop_assert);
        case COWL_AT_DATA_PROP_ASSERT:
        case COWL_AT_NEG_DATA_PROP_ASSERT: GEN_ANON(DataPropAssert, data_prop_assert);
        case COWL_AT_SUB_OBJ_PROP: GEN_ANON(SubObjProp, sub_obj_prop);
        case COWL_AT_SUB_OBJ_PROP_CHAIN: GEN_ANON(SubObjPropChain, sub_obj_prop_chain);
        case COWL_AT_INV_OBJ_PROP: GEN_ANON(InvObjProp, inv_obj_prop);
        case COWL_AT_EQUIV_OBJ_PROP:
        case COWL_AT_DISJ_OBJ_PROP: GEN_ANON(NAryObjProp, nary_obj_prop);
        case COWL_AT_FUNC_OBJ_PROP:
        case COWL_AT_INV_FUNC_OBJ_PROP:
        case COWL_AT_SYMM_OBJ_PROP:
        case COWL_AT_ASYMM_OBJ_PROP:
        case COWL_AT_REFL_OBJ_PROP:
        case COWL_AT_IRREFL_OBJ_PROP:
        case COWL_AT_TRANS_OBJ_PROP: GEN_ANON(ObjPropChar, obj_prop_char);
        case COWL_AT_OBJ_PROP_DOMAIN: GEN_ANON(ObjPropDomain, obj_prop_domain);
        case COWL_AT_OBJ_PROP_RANGE: GEN_ANON(ObjPropRange, obj_prop_range);
        case COWL_AT_SUB_DATA_PROP: GEN_ANON(SubDataProp, sub_data_prop);
        case COWL_AT_EQUIV_DATA_PROP:
        case COWL_AT_DISJ_DATA_PROP: GEN_ANON(NAryDataProp, nary_data_prop);
        case COWL_AT_FUNC_DATA_PROP: GEN_ANON(FuncDataProp, func_data_prop);
        case COWL_AT_DATA_PROP_DOMAIN: GEN_ANON(DataPropDomain, data_prop_domain);
        case COWL_AT_DATA_PROP_RANGE: GEN_ANON(DataPropRange, data_prop_range);
        case COWL_AT_HAS_KEY: GEN_ANON(HasKey, has_key);
        case COWL_AT_ANNOT_ASSERT: GEN_ANON(AnnotAssert, annot_assert);
        case COWL_AT_SUB_ANNOT_PROP: GEN_ANON(SubAnnotProp, sub_annot_prop);
        case COWL_AT_ANNOT_PROP_DOMAIN: GEN_ANON(AnnotPropDomain, annot_prop_domain);
        case COWL_AT_ANNOT_PROP_RANGE: GEN_ANON(AnnotPropRange, annot_prop_range);
        default: return true;
    }
}
