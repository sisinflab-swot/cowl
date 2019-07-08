/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_compl_private.h"
#include "cowl_hash_utils.h"

static CowlDataCompl* cowl_data_compl_alloc(CowlDataRange *operand) {
    cowl_uint_t hash = cowl_hash_1(COWL_HASH_INIT_DATA_COMPL, cowl_data_range_hash(operand));

    CowlDataCompl init = {
        .super = COWL_DATA_RANGE_INIT(COWL_DRT_DATA_COMPL, hash),
        .operand = cowl_data_range_retain(operand)
    };

    cowl_struct(CowlDataCompl) *exp = malloc(sizeof(*exp));
    memcpy(exp, &init, sizeof(*exp));
    return exp;
}

static void cowl_data_compl_free(CowlDataCompl *exp) {
    if (!exp) return;
    cowl_data_range_release(exp->operand);
    free((void *)exp);
}

CowlDataCompl* cowl_data_compl_get(CowlDataRange *operand) {
    return cowl_data_compl_alloc(operand);
}

CowlDataCompl* cowl_data_compl_retain(CowlDataCompl *exp) {
    return cowl_object_retain(exp);
}

void cowl_data_compl_release(CowlDataCompl *exp) {
    if (exp && !cowl_object_release(exp)) {
        cowl_data_compl_free(exp);
    }
}

CowlDataRange* cowl_data_compl_get_operand(CowlDataCompl *exp) {
    return exp->operand;
}

bool cowl_data_compl_equals(CowlDataCompl *lhs, CowlDataCompl *rhs) {
    return cowl_data_range_equals(lhs->operand, rhs->operand);
}

cowl_uint_t cowl_data_compl_hash(CowlDataCompl *exp) {
    return cowl_object_hash_get(exp);
}

bool cowl_data_compl_iterate_signature(CowlDataCompl *exp, CowlEntityIterator *iter) {
    return cowl_data_range_iterate_signature(exp->operand, iter);
}
