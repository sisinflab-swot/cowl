/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_compl_private.h"
#include "cowl_hash_utils.h"
#include "cowl_template.h"

static CowlDataCompl* cowl_data_compl_alloc(CowlDataRange *operand) {
    CowlDataCompl *range = ulib_alloc(range);
    if (!range) return NULL;

    ulib_uint hash = cowl_hash_1(COWL_HASH_INIT_DATA_COMPL, cowl_data_range_hash(operand));

    *range = (CowlDataCompl) {
        .super = COWL_DATA_RANGE_INIT(COWL_DRT_DATA_COMPL, hash),
        .operand = cowl_data_range_retain(operand)
    };

    return range;
}

static void cowl_data_compl_free(CowlDataCompl *range) {
    cowl_data_range_release(range->operand);
    ulib_free(range);
}

CowlDataCompl* cowl_data_compl_get(CowlDataRange *operand) {
    if (!operand) return NULL;
    return cowl_data_compl_alloc(operand);
}

CowlDataCompl* cowl_data_compl_retain(CowlDataCompl *range) {
    return cowl_object_incr_ref(range);
}

void cowl_data_compl_release(CowlDataCompl *range) {
    if (range && !cowl_object_decr_ref(range)) {
        cowl_data_compl_free(range);
    }
}

CowlDataRange* cowl_data_compl_get_operand(CowlDataCompl *range) {
    return range->operand;
}

CowlString* cowl_data_compl_to_string(CowlDataCompl *range)
    COWL_TO_STRING_IMPL(data_compl, range)

bool cowl_data_compl_equals(CowlDataCompl *lhs, CowlDataCompl *rhs) {
    return cowl_object_hash_equals(lhs, rhs) && cowl_data_range_equals(lhs->operand, rhs->operand);
}

ulib_uint cowl_data_compl_hash(CowlDataCompl *range) {
    return cowl_object_hash_get(range);
}

bool cowl_data_compl_iterate_primitives(CowlDataCompl *range, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return cowl_data_range_iterate_primitives(range->operand, flags, iter);
}
