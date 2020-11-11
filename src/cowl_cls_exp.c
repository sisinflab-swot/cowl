/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_cls_exp_private.h"
#include "cowl_class.h"
#include "cowl_data_card.h"
#include "cowl_data_has_value.h"
#include "cowl_data_quant.h"
#include "cowl_nary_bool.h"
#include "cowl_obj_card.h"
#include "cowl_obj_compl.h"
#include "cowl_obj_has_self.h"
#include "cowl_obj_has_value.h"
#include "cowl_obj_one_of.h"
#include "cowl_obj_quant.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlClsExp* cowl_cls_exp_retain(CowlClsExp *exp) {
    return cowl_object_retain(exp);
}

void cowl_cls_exp_release(CowlClsExp *exp) {
    if (!exp) return;

#define GEN_RELEASE(UC, LC) cowl_##LC##_release((Cowl##UC *)exp); break

    switch (cowl_cls_exp_get_type(exp)) {
        case COWL_CET_CLASS: GEN_RELEASE(Class, class);
        case COWL_CET_OBJ_COMPL: GEN_RELEASE(ObjCompl, obj_compl);
        case COWL_CET_OBJ_INTERSECT:
        case COWL_CET_OBJ_UNION: GEN_RELEASE(NAryBool, nary_bool);
        case COWL_CET_OBJ_SOME:
        case COWL_CET_OBJ_ALL: GEN_RELEASE(ObjQuant, obj_quant);
        case COWL_CET_OBJ_MIN_CARD:
        case COWL_CET_OBJ_MAX_CARD:
        case COWL_CET_OBJ_EXACT_CARD: GEN_RELEASE(ObjCard, obj_card);
        case COWL_CET_OBJ_HAS_VALUE: GEN_RELEASE(ObjHasValue, obj_has_value);
        case COWL_CET_OBJ_HAS_SELF: GEN_RELEASE(ObjHasSelf, obj_has_self);
        case COWL_CET_DATA_SOME:
        case COWL_CET_DATA_ALL: GEN_RELEASE(DataQuant, data_quant);
        case COWL_CET_DATA_MIN_CARD:
        case COWL_CET_DATA_MAX_CARD:
        case COWL_CET_DATA_EXACT_CARD: GEN_RELEASE(DataCard, data_card);
        case COWL_CET_DATA_HAS_VALUE: GEN_RELEASE(DataHasValue, data_has_value);
        case COWL_CET_OBJ_ONE_OF: GEN_RELEASE(ObjOneOf, obj_one_of);
        default: break;
    }
}

CowlClsExpType cowl_cls_exp_get_type(CowlClsExp *exp) {
    return (CowlClsExpType)(cowl_get_type(exp) - COWL_OT_CE_CLASS);
}

CowlString* cowl_cls_exp_to_string(CowlClsExp *exp)
    COWL_TO_STRING_IMPL(cls_exp, exp)

bool cowl_cls_exp_equals(CowlClsExp *lhs, CowlClsExp *rhs) {
    if (lhs == rhs) return true;
    if (!cowl_hash_object_equals_impl(lhs, rhs)) return false;

#define GEN_EQUAL(UC, LC) return cowl_##LC##_equals((Cowl##UC *)lhs, (Cowl##UC *)rhs)

    switch (cowl_cls_exp_get_type(lhs)) {
        case COWL_CET_CLASS: GEN_EQUAL(Class, class);
        case COWL_CET_OBJ_COMPL: GEN_EQUAL(ObjCompl, obj_compl);
        case COWL_CET_OBJ_INTERSECT:
        case COWL_CET_OBJ_UNION: GEN_EQUAL(NAryBool, nary_bool);
        case COWL_CET_OBJ_SOME:
        case COWL_CET_OBJ_ALL: GEN_EQUAL(ObjQuant, obj_quant);
        case COWL_CET_OBJ_MIN_CARD:
        case COWL_CET_OBJ_MAX_CARD:
        case COWL_CET_OBJ_EXACT_CARD: GEN_EQUAL(ObjCard, obj_card);
        case COWL_CET_OBJ_HAS_VALUE: GEN_EQUAL(ObjHasValue, obj_has_value);
        case COWL_CET_OBJ_HAS_SELF: GEN_EQUAL(ObjHasSelf, obj_has_self);
        case COWL_CET_DATA_SOME:
        case COWL_CET_DATA_ALL: GEN_EQUAL(DataQuant, data_quant);
        case COWL_CET_DATA_MIN_CARD:
        case COWL_CET_DATA_MAX_CARD:
        case COWL_CET_DATA_EXACT_CARD: GEN_EQUAL(DataCard, data_card);
        case COWL_CET_DATA_HAS_VALUE: GEN_EQUAL(DataHasValue, data_has_value);
        case COWL_CET_OBJ_ONE_OF: GEN_EQUAL(ObjOneOf, obj_one_of);
        default: return false;
    }
}

cowl_uint cowl_cls_exp_hash(CowlClsExp *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_cls_exp_iterate_primitives(CowlClsExp *exp, CowlIterator *iter,
                                     CowlPrimitiveFlags flags) {

#define GEN_ITER(UC, LC) return cowl_##LC##_iterate_primitives((Cowl##UC *)exp, iter, flags)

    switch (cowl_cls_exp_get_type(exp)) {
        case COWL_CET_CLASS: GEN_ITER(Class, class);
        case COWL_CET_OBJ_COMPL: GEN_ITER(ObjCompl, obj_compl);
        case COWL_CET_OBJ_INTERSECT:
        case COWL_CET_OBJ_UNION: GEN_ITER(NAryBool, nary_bool);
        case COWL_CET_OBJ_SOME:
        case COWL_CET_OBJ_ALL: GEN_ITER(ObjQuant, obj_quant);
        case COWL_CET_OBJ_MIN_CARD:
        case COWL_CET_OBJ_MAX_CARD:
        case COWL_CET_OBJ_EXACT_CARD: GEN_ITER(ObjCard, obj_card);
        case COWL_CET_OBJ_HAS_VALUE: GEN_ITER(ObjHasValue, obj_has_value);
        case COWL_CET_OBJ_HAS_SELF: GEN_ITER(ObjHasSelf, obj_has_self);
        case COWL_CET_DATA_SOME:
        case COWL_CET_DATA_ALL: GEN_ITER(DataQuant, data_quant);
        case COWL_CET_DATA_MIN_CARD:
        case COWL_CET_DATA_MAX_CARD:
        case COWL_CET_DATA_EXACT_CARD: GEN_ITER(DataCard, data_card);
        case COWL_CET_DATA_HAS_VALUE: GEN_ITER(DataHasValue, data_has_value);
        case COWL_CET_OBJ_ONE_OF: GEN_ITER(ObjOneOf, obj_one_of);
        default: return true;
    }
}
