/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_compl_private.h"
#include "cowl_alloc.h"
#include "cowl_hash_utils.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlObjCompl* cowl_obj_compl_alloc(CowlClsExp *operand) {
    CowlObjCompl *exp = cowl_alloc(exp);
    if (!exp) return NULL;

    cowl_uint_t hash = cowl_hash_1(COWL_HASH_INIT_OBJ_COMPL, cowl_cls_exp_hash(operand));

    *exp = (CowlObjCompl) {
        .super = COWL_CLS_EXP_INIT(COWL_CET_OBJ_COMPL, hash),
        .operand = cowl_cls_exp_retain(operand)
    };

    return exp;
}

static void cowl_obj_compl_free(CowlObjCompl *exp) {
    if (!exp) return;
    cowl_cls_exp_release(exp->operand);
    cowl_free(exp);
}

CowlObjCompl* cowl_obj_compl_get(CowlClsExp *operand) {
    if (!operand) return NULL;
    return cowl_obj_compl_alloc(operand);
}

CowlObjCompl* cowl_obj_compl_retain(CowlObjCompl *exp) {
    return cowl_object_retain(exp);
}

void cowl_obj_compl_release(CowlObjCompl *exp) {
    if (exp && !cowl_object_release(exp)) {
        cowl_obj_compl_free(exp);
    }
}

CowlClsExp* cowl_obj_compl_get_operand(CowlObjCompl *exp) {
    return exp->operand;
}

CowlString* cowl_obj_compl_to_string(CowlObjCompl *exp)
    COWL_TO_STRING_IMPL(obj_compl, exp)

bool cowl_obj_compl_equals(CowlObjCompl *lhs, CowlObjCompl *rhs) {
    return cowl_cls_exp_equals(lhs->operand, rhs->operand);
}

cowl_uint_t cowl_obj_compl_hash(CowlObjCompl *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_obj_compl_iterate_signature(CowlObjCompl *exp, CowlEntityIterator *iter) {
    return cowl_cls_exp_iterate_signature(exp->operand, iter);
}

bool cowl_obj_compl_iterate_primitives(CowlObjCompl *exp, CowlPrimitiveIterator *iter) {
    return cowl_cls_exp_iterate_primitives(exp->operand, iter);
}
