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

CowlClsExp* cowl_cls_exp_retain(CowlClsExp *exp) {
    return cowl_object_retain(exp);
}

void cowl_cls_exp_release(CowlClsExp *exp) {
    if (!exp) return;

#define GEN_CASE_RELEASE(CCET, TYPE, PREFIX) \
    case CCET: PREFIX##_release((TYPE *)exp); break

    switch (exp->type) {

        GEN_CASE_RELEASE(COWL_CET_CLASS, CowlClass, cowl_class);
        GEN_CASE_RELEASE(COWL_CET_OBJ_COMPL, CowlObjCompl, cowl_obj_compl);
        GEN_CASE_RELEASE(COWL_CET_OBJ_INTERSECT, CowlNAryBool, cowl_nary_bool);
        GEN_CASE_RELEASE(COWL_CET_OBJ_UNION, CowlNAryBool, cowl_nary_bool);
        GEN_CASE_RELEASE(COWL_CET_OBJ_SOME, CowlObjQuant, cowl_obj_quant);
        GEN_CASE_RELEASE(COWL_CET_OBJ_ALL, CowlObjQuant, cowl_obj_quant);
        GEN_CASE_RELEASE(COWL_CET_OBJ_MIN_CARD, CowlObjCard, cowl_obj_card);
        GEN_CASE_RELEASE(COWL_CET_OBJ_MAX_CARD, CowlObjCard, cowl_obj_card);
        GEN_CASE_RELEASE(COWL_CET_OBJ_EXACT_CARD, CowlObjCard, cowl_obj_card);
        GEN_CASE_RELEASE(COWL_CET_OBJ_HAS_VALUE, CowlObjHasValue, cowl_obj_has_value);
        GEN_CASE_RELEASE(COWL_CET_OBJ_HAS_SELF, CowlObjHasSelf, cowl_obj_has_self);
        GEN_CASE_RELEASE(COWL_CET_DATA_SOME, CowlDataQuant, cowl_data_quant);
        GEN_CASE_RELEASE(COWL_CET_DATA_ALL, CowlDataQuant, cowl_data_quant);
        GEN_CASE_RELEASE(COWL_CET_DATA_MIN_CARD, CowlDataCard, cowl_data_card);
        GEN_CASE_RELEASE(COWL_CET_DATA_MAX_CARD, CowlDataCard, cowl_data_card);
        GEN_CASE_RELEASE(COWL_CET_DATA_EXACT_CARD, CowlDataCard, cowl_data_card);
        GEN_CASE_RELEASE(COWL_CET_DATA_HAS_VALUE, CowlDataHasValue, cowl_data_has_value);
        GEN_CASE_RELEASE(COWL_CET_OBJ_ONE_OF, CowlObjOneOf, cowl_obj_one_of);

        default:
            break;
    }
}

CowlClsExpType cowl_cls_exp_get_type(CowlClsExp *exp) {
    return exp->type;
}

bool cowl_cls_exp_equals(CowlClsExp *lhs, CowlClsExp *rhs) {
    if (lhs == rhs) return true;
    if (lhs->type != rhs->type || lhs->super.hash != rhs->super.hash) return false;

#define GEN_CASE_EQUAL(CCET, TYPE, PREFIX) \
    case CCET: return PREFIX##_equals((TYPE *)lhs, (TYPE *)rhs)

    switch (lhs->type) {

        GEN_CASE_EQUAL(COWL_CET_CLASS, CowlClass, cowl_class);
        GEN_CASE_EQUAL(COWL_CET_OBJ_COMPL, CowlObjCompl, cowl_obj_compl);
        GEN_CASE_EQUAL(COWL_CET_OBJ_INTERSECT, CowlNAryBool, cowl_nary_bool);
        GEN_CASE_EQUAL(COWL_CET_OBJ_UNION, CowlNAryBool, cowl_nary_bool);
        GEN_CASE_EQUAL(COWL_CET_OBJ_SOME, CowlObjQuant, cowl_obj_quant);
        GEN_CASE_EQUAL(COWL_CET_OBJ_ALL, CowlObjQuant, cowl_obj_quant);
        GEN_CASE_EQUAL(COWL_CET_OBJ_MIN_CARD, CowlObjCard, cowl_obj_card);
        GEN_CASE_EQUAL(COWL_CET_OBJ_MAX_CARD, CowlObjCard, cowl_obj_card);
        GEN_CASE_EQUAL(COWL_CET_OBJ_EXACT_CARD, CowlObjCard, cowl_obj_card);
        GEN_CASE_EQUAL(COWL_CET_OBJ_HAS_VALUE, CowlObjHasValue, cowl_obj_has_value);
        GEN_CASE_EQUAL(COWL_CET_OBJ_HAS_SELF, CowlObjHasSelf, cowl_obj_has_self);
        GEN_CASE_EQUAL(COWL_CET_DATA_SOME, CowlDataQuant, cowl_data_quant);
        GEN_CASE_EQUAL(COWL_CET_DATA_ALL, CowlDataQuant, cowl_data_quant);
        GEN_CASE_EQUAL(COWL_CET_DATA_MIN_CARD, CowlDataCard, cowl_data_card);
        GEN_CASE_EQUAL(COWL_CET_DATA_MAX_CARD, CowlDataCard, cowl_data_card);
        GEN_CASE_EQUAL(COWL_CET_DATA_EXACT_CARD, CowlDataCard, cowl_data_card);
        GEN_CASE_EQUAL(COWL_CET_DATA_HAS_VALUE, CowlDataHasValue, cowl_data_has_value);
        GEN_CASE_EQUAL(COWL_CET_OBJ_ONE_OF, CowlObjOneOf, cowl_obj_one_of);

        default:
            return false;
    }
}

cowl_uint_t cowl_cls_exp_hash(CowlClsExp *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_cls_exp_iterate_signature(CowlClsExp *exp, CowlEntityIterator *iter) {

#define GEN_CASE_SIG(CCET, TYPE, PREFIX) \
    case CCET: return PREFIX##_iterate_signature((TYPE *)exp, iter)

    switch (exp->type) {

        GEN_CASE_SIG(COWL_CET_CLASS, CowlClass, cowl_class);
        GEN_CASE_SIG(COWL_CET_OBJ_COMPL, CowlObjCompl, cowl_obj_compl);
        GEN_CASE_SIG(COWL_CET_OBJ_INTERSECT, CowlNAryBool, cowl_nary_bool);
        GEN_CASE_SIG(COWL_CET_OBJ_UNION, CowlNAryBool, cowl_nary_bool);
        GEN_CASE_SIG(COWL_CET_OBJ_SOME, CowlObjQuant, cowl_obj_quant);
        GEN_CASE_SIG(COWL_CET_OBJ_ALL, CowlObjQuant, cowl_obj_quant);
        GEN_CASE_SIG(COWL_CET_OBJ_MIN_CARD, CowlObjCard, cowl_obj_card);
        GEN_CASE_SIG(COWL_CET_OBJ_MAX_CARD, CowlObjCard, cowl_obj_card);
        GEN_CASE_SIG(COWL_CET_OBJ_EXACT_CARD, CowlObjCard, cowl_obj_card);
        GEN_CASE_SIG(COWL_CET_OBJ_HAS_VALUE, CowlObjHasValue, cowl_obj_has_value);
        GEN_CASE_SIG(COWL_CET_OBJ_HAS_SELF, CowlObjHasSelf, cowl_obj_has_self);
        GEN_CASE_SIG(COWL_CET_DATA_SOME, CowlDataQuant, cowl_data_quant);
        GEN_CASE_SIG(COWL_CET_DATA_ALL, CowlDataQuant, cowl_data_quant);
        GEN_CASE_SIG(COWL_CET_DATA_MIN_CARD, CowlDataCard, cowl_data_card);
        GEN_CASE_SIG(COWL_CET_DATA_MAX_CARD, CowlDataCard, cowl_data_card);
        GEN_CASE_SIG(COWL_CET_DATA_EXACT_CARD, CowlDataCard, cowl_data_card);
        GEN_CASE_SIG(COWL_CET_DATA_HAS_VALUE, CowlDataHasValue, cowl_data_has_value);
        GEN_CASE_SIG(COWL_CET_OBJ_ONE_OF, CowlObjOneOf, cowl_obj_one_of);

        default:
            return true;
    }
}
