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
#include "cowl_template.h"

CowlAxiom* cowl_axiom_retain(CowlAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_axiom_release(CowlAxiom *axiom) {
    if (!axiom) return;

#define GEN_RELEASE(UC, LC) cowl_##LC##_axiom_release((Cowl##UC##Axiom *)axiom); break

    switch (cowl_axiom_get_type(axiom)) {
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
    return (CowlAxiomType)(cowl_get_type(axiom) - COWL_OT_A_DECL);
}

CowlString* cowl_axiom_to_string(CowlAxiom *axiom)
    COWL_TO_STRING_IMPL(axiom, axiom)

bool cowl_axiom_equals(CowlAxiom *lhs, CowlAxiom *rhs) {
    if (lhs == rhs) return true;
    if (!cowl_hash_object_equals_impl(lhs, rhs)) return false;

#define GEN_EQUAL(UC, LC) \
    return cowl_##LC##_axiom_equals((Cowl##UC##Axiom *)lhs, (Cowl##UC##Axiom *)rhs)

    switch (cowl_axiom_get_type(lhs)) {
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

cowl_uint cowl_axiom_hash(CowlAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_axiom_iterate_primitives(CowlAxiom *axiom, CowlIterator *iter, CowlPrimitiveFlags flags) {

#define GEN_ITER(UC, LC) \
    return cowl_##LC##_axiom_iterate_primitives((Cowl##UC##Axiom *)axiom, iter, flags)

    switch (cowl_axiom_get_type(axiom)) {
        case COWL_AT_DECL: GEN_ITER(Decl, decl);
        case COWL_AT_DATATYPE_DEF: GEN_ITER(DatatypeDef, datatype_def);
        case COWL_AT_SUB_CLASS: GEN_ITER(SubCls, sub_cls);
        case COWL_AT_EQUIV_CLASSES:
        case COWL_AT_DISJ_CLASSES: GEN_ITER(NAryCls, nary_cls);
        case COWL_AT_DISJ_UNION: GEN_ITER(DisjUnion, disj_union);
        case COWL_AT_CLASS_ASSERT: GEN_ITER(ClsAssert, cls_assert);
        case COWL_AT_SAME_IND:
        case COWL_AT_DIFF_IND: GEN_ITER(NAryInd, nary_ind);
        case COWL_AT_OBJ_PROP_ASSERT:
        case COWL_AT_NEG_OBJ_PROP_ASSERT: GEN_ITER(ObjPropAssert, obj_prop_assert);
        case COWL_AT_DATA_PROP_ASSERT:
        case COWL_AT_NEG_DATA_PROP_ASSERT: GEN_ITER(DataPropAssert, data_prop_assert);
        case COWL_AT_SUB_OBJ_PROP: GEN_ITER(SubObjProp, sub_obj_prop);
        case COWL_AT_SUB_OBJ_PROP_CHAIN: GEN_ITER(SubObjPropChain, sub_obj_prop_chain);
        case COWL_AT_INV_OBJ_PROP: GEN_ITER(InvObjProp, inv_obj_prop);
        case COWL_AT_EQUIV_OBJ_PROP:
        case COWL_AT_DISJ_OBJ_PROP: GEN_ITER(NAryObjProp, nary_obj_prop);
        case COWL_AT_FUNC_OBJ_PROP:
        case COWL_AT_INV_FUNC_OBJ_PROP:
        case COWL_AT_SYMM_OBJ_PROP:
        case COWL_AT_ASYMM_OBJ_PROP:
        case COWL_AT_REFL_OBJ_PROP:
        case COWL_AT_IRREFL_OBJ_PROP:
        case COWL_AT_TRANS_OBJ_PROP: GEN_ITER(ObjPropChar, obj_prop_char);
        case COWL_AT_OBJ_PROP_DOMAIN: GEN_ITER(ObjPropDomain, obj_prop_domain);
        case COWL_AT_OBJ_PROP_RANGE: GEN_ITER(ObjPropRange, obj_prop_range);
        case COWL_AT_SUB_DATA_PROP: GEN_ITER(SubDataProp, sub_data_prop);
        case COWL_AT_EQUIV_DATA_PROP:
        case COWL_AT_DISJ_DATA_PROP: GEN_ITER(NAryDataProp, nary_data_prop);
        case COWL_AT_FUNC_DATA_PROP: GEN_ITER(FuncDataProp, func_data_prop);
        case COWL_AT_DATA_PROP_DOMAIN: GEN_ITER(DataPropDomain, data_prop_domain);
        case COWL_AT_DATA_PROP_RANGE: GEN_ITER(DataPropRange, data_prop_range);
        case COWL_AT_HAS_KEY: GEN_ITER(HasKey, has_key);
        case COWL_AT_ANNOT_ASSERT: GEN_ITER(AnnotAssert, annot_assert);
        case COWL_AT_SUB_ANNOT_PROP: GEN_ITER(SubAnnotProp, sub_annot_prop);
        case COWL_AT_ANNOT_PROP_DOMAIN: GEN_ITER(AnnotPropDomain, annot_prop_domain);
        case COWL_AT_ANNOT_PROP_RANGE: GEN_ITER(AnnotPropRange, annot_prop_range);
        default: return true;
    }
}
