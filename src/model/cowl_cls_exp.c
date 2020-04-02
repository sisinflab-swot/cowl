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

    switch (exp->type) {
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
    return exp->type;
}

CowlString* cowl_cls_exp_to_string(CowlClsExp *exp)
    COWL_TO_STRING_IMPL(cls_exp, exp)

bool cowl_cls_exp_equals(CowlClsExp *lhs, CowlClsExp *rhs) {
    if (lhs == rhs) return true;
    if (lhs->type != rhs->type || lhs->super.hash != rhs->super.hash) return false;

#define GEN_EQUAL(UC, LC) return cowl_##LC##_equals((Cowl##UC *)lhs, (Cowl##UC *)rhs)

    switch (lhs->type) {
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

cowl_uint_t cowl_cls_exp_hash(CowlClsExp *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_cls_exp_iterate_signature(CowlClsExp *exp, CowlEntityIterator *iter) {

#define GEN_SIG(UC, LC) return cowl_##LC##_iterate_signature((Cowl##UC *)exp, iter)

    switch (exp->type) {
        case COWL_CET_CLASS: GEN_SIG(Class, class);
        case COWL_CET_OBJ_COMPL: GEN_SIG(ObjCompl, obj_compl);
        case COWL_CET_OBJ_INTERSECT:
        case COWL_CET_OBJ_UNION: GEN_SIG(NAryBool, nary_bool);
        case COWL_CET_OBJ_SOME:
        case COWL_CET_OBJ_ALL: GEN_SIG(ObjQuant, obj_quant);
        case COWL_CET_OBJ_MIN_CARD:
        case COWL_CET_OBJ_MAX_CARD:
        case COWL_CET_OBJ_EXACT_CARD: GEN_SIG(ObjCard, obj_card);
        case COWL_CET_OBJ_HAS_VALUE: GEN_SIG(ObjHasValue, obj_has_value);
        case COWL_CET_OBJ_HAS_SELF: GEN_SIG(ObjHasSelf, obj_has_self);
        case COWL_CET_DATA_SOME:
        case COWL_CET_DATA_ALL: GEN_SIG(DataQuant, data_quant);
        case COWL_CET_DATA_MIN_CARD:
        case COWL_CET_DATA_MAX_CARD:
        case COWL_CET_DATA_EXACT_CARD: GEN_SIG(DataCard, data_card);
        case COWL_CET_DATA_HAS_VALUE: GEN_SIG(DataHasValue, data_has_value);
        case COWL_CET_OBJ_ONE_OF: GEN_SIG(ObjOneOf, obj_one_of);
        default: return true;
    }
}

bool cowl_cls_exp_iterate_primitives(CowlClsExp *exp, CowlPrimitiveIterator *iter) {

#define GEN_PRIM(UC, LC) return cowl_##LC##_iterate_primitives((Cowl##UC *)exp, iter)

    switch (exp->type) {
        case COWL_CET_CLASS: GEN_PRIM(Class, class);
        case COWL_CET_OBJ_COMPL: GEN_PRIM(ObjCompl, obj_compl);
        case COWL_CET_OBJ_INTERSECT:
        case COWL_CET_OBJ_UNION: GEN_PRIM(NAryBool, nary_bool);
        case COWL_CET_OBJ_SOME:
        case COWL_CET_OBJ_ALL: GEN_PRIM(ObjQuant, obj_quant);
        case COWL_CET_OBJ_MIN_CARD:
        case COWL_CET_OBJ_MAX_CARD:
        case COWL_CET_OBJ_EXACT_CARD: GEN_PRIM(ObjCard, obj_card);
        case COWL_CET_OBJ_HAS_VALUE: GEN_PRIM(ObjHasValue, obj_has_value);
        case COWL_CET_OBJ_HAS_SELF: GEN_PRIM(ObjHasSelf, obj_has_self);
        case COWL_CET_DATA_SOME:
        case COWL_CET_DATA_ALL: GEN_PRIM(DataQuant, data_quant);
        case COWL_CET_DATA_MIN_CARD:
        case COWL_CET_DATA_MAX_CARD:
        case COWL_CET_DATA_EXACT_CARD: GEN_PRIM(DataCard, data_card);
        case COWL_CET_DATA_HAS_VALUE: GEN_PRIM(DataHasValue, data_has_value);
        case COWL_CET_OBJ_ONE_OF: GEN_PRIM(ObjOneOf, obj_one_of);
        default: return true;
    }
}
