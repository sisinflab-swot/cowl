/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_bool_private.h"
#include "cowl_alloc.h"
#include "cowl_cls_exp_set.h"
#include "cowl_hash_utils.h"
#include "cowl_str_buf.h"

static CowlNAryBool* cowl_nary_bool_alloc(CowlClsExpType type, CowlClsExpSet *operands) {
    CowlNAryBool *exp = cowl_alloc(exp);
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_NARY_BOOL, type,
                                   uhset_hash(CowlClsExpSet, operands));

    *exp = (CowlNAryBool) {
        .super = COWL_CLS_EXP_INIT(type, hash),
        .operands = operands
    };

    return exp;
}

static void cowl_nary_bool_free(CowlNAryBool *exp) {
    if (!exp) return;
    cowl_cls_exp_set_free(exp->operands);
    cowl_free(exp);
}

CowlNAryBool* cowl_nary_bool_get(CowlNAryType type, CowlClsExpSet *operands) {
    return cowl_nary_bool_alloc((CowlClsExpType)type + COWL_CET_OBJ_INTERSECT, operands);
}

CowlNAryBool* cowl_nary_bool_retain(CowlNAryBool *exp) {
    return cowl_object_retain(exp);
}

void cowl_nary_bool_release(CowlNAryBool *exp) {
    if (exp && !cowl_object_release(exp)) {
        cowl_nary_bool_free(exp);
    }
}

CowlNAryType cowl_nary_bool_get_type(CowlNAryBool *exp) {
    return (CowlNAryType)(exp->super.type - COWL_CET_OBJ_INTERSECT);
}

CowlClsExpSet* cowl_nary_bool_get_operands(CowlNAryBool *exp) {
    return exp->operands;
}

CowlString* cowl_nary_bool_to_string(CowlNAryBool *exp) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_nary_bool(buf, exp);
    return cowl_str_buf_to_string(buf);
}

bool cowl_nary_bool_equals(CowlNAryBool *lhs, CowlNAryBool *rhs) {
    return (lhs->super.type == rhs->super.type &&
            uhset_equals(CowlClsExpSet, lhs->operands, rhs->operands));
}

cowl_uint_t cowl_nary_bool_hash(CowlNAryBool *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_nary_bool_iterate_signature(CowlNAryBool *exp, CowlEntityIterator *iter) {
    return cowl_cls_exp_set_iterate_signature(exp->operands, iter);
}

bool cowl_nary_bool_iterate_anon_inds(CowlNAryBool *exp, CowlAnonIndIterator *iter) {
    return cowl_cls_exp_set_iterate_anon_inds(exp->operands, iter);
}
