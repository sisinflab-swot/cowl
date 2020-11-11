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
#include "cowl_cls_exp_set.h"
#include "cowl_hash_utils.h"
#include "cowl_macros.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlNAryBool* cowl_nary_bool_alloc(CowlClsExpType type, CowlClsExpSet *operands) {
    CowlNAryBool *exp = cowl_alloc(exp);
    if (!exp) return NULL;

    cowl_uint hash = cowl_hash_2(COWL_HASH_INIT_NARY_BOOL, type,
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
    if (!(operands && cowl_enum_value_is_valid(NT, type))) return NULL;
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
    return (CowlNAryType)(cowl_get_type(exp) - COWL_OT_CE_OBJ_INTERSECT);
}

CowlClsExpSet* cowl_nary_bool_get_operands(CowlNAryBool *exp) {
    return exp->operands;
}

CowlString* cowl_nary_bool_to_string(CowlNAryBool *exp)
    COWL_TO_STRING_IMPL(nary_bool, exp)

bool cowl_nary_bool_equals(CowlNAryBool *lhs, CowlNAryBool *rhs) {
    return (cowl_hash_object_equals_impl(lhs, rhs) &&
            uhset_equals(CowlClsExpSet, lhs->operands, rhs->operands));
}

cowl_uint cowl_nary_bool_hash(CowlNAryBool *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_nary_bool_iterate_primitives(CowlNAryBool *exp, CowlIterator *iter,
                                       CowlPrimitiveFlags flags) {
    return cowl_cls_exp_set_iterate_primitives(exp->operands, iter, flags);
}
