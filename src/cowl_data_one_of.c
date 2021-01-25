/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_one_of_private.h"
#include "cowl_hash_utils.h"
#include "cowl_literal.h"
#include "cowl_object_table.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlDataOneOf* cowl_data_one_of_alloc(CowlObjectTable *values) {
    CowlDataOneOf *range = cowl_alloc(range);
    if (!range) return NULL;

    cowl_uint hash = cowl_hash_1(COWL_HASH_INIT_DATA_ONE_OF, cowl_object_set_hash(values));

    *range = (CowlDataOneOf) {
        .super = COWL_DATA_RANGE_INIT(COWL_DRT_DATA_ONE_OF, hash),
        .values = values
    };

    return range;
}

static void cowl_data_one_of_free(CowlDataOneOf *range) {
    if (!range) return;
    cowl_object_set_free(range->values);
    cowl_free(range);
}

CowlDataOneOf* cowl_data_one_of_get(CowlObjectTable *values) {
    if (!values) return NULL;
    return cowl_data_one_of_alloc(values);
}

CowlDataOneOf* cowl_data_one_of_retain(CowlDataOneOf *range) {
    return cowl_object_incr_ref(range);
}

void cowl_data_one_of_release(CowlDataOneOf *range) {
    if (range && !cowl_object_decr_ref(range)) {
        cowl_data_one_of_free(range);
    }
}

CowlObjectTable* cowl_data_one_of_get_values(CowlDataOneOf *range) {
    return range->values;
}

CowlString* cowl_data_one_of_to_string(CowlDataOneOf *range)
    COWL_TO_STRING_IMPL(data_one_of, range)

bool cowl_data_one_of_equals(CowlDataOneOf *lhs, CowlDataOneOf *rhs) {
    return cowl_object_hash_equals(lhs, rhs) && cowl_object_set_equals(lhs->values, rhs->values);
}

cowl_uint cowl_data_one_of_hash(CowlDataOneOf *range) {
    return cowl_object_hash_get(range);
}

bool cowl_data_one_of_iterate_primitives(CowlDataOneOf *range, CowlIterator *iter,
                                         CowlPrimitiveFlags flags) {
    return cowl_object_set_iterate_primitives(range->values, iter, flags);
}
