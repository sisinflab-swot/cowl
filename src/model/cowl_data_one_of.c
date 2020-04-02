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
#include "cowl_alloc.h"
#include "cowl_hash_utils.h"
#include "cowl_literal.h"
#include "cowl_literal_set.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlDataOneOf* cowl_data_one_of_alloc(CowlLiteralSet *values) {
    CowlDataOneOf *range = cowl_alloc(range);
    if (!range) return NULL;

    cowl_uint_t hash = cowl_hash_1(COWL_HASH_INIT_DATA_ONE_OF, cowl_literal_set_hash(values));

    *range = (CowlDataOneOf) {
        .super = COWL_DATA_RANGE_INIT(COWL_DRT_DATA_ONE_OF, hash),
        .values = values
    };

    return range;
}

static void cowl_data_one_of_free(CowlDataOneOf *range) {
    if (!range) return;
    cowl_literal_set_free(range->values);
    cowl_free(range);
}

CowlDataOneOf* cowl_data_one_of_get(CowlLiteralSet *values) {
    return cowl_data_one_of_alloc(values);
}

CowlDataOneOf* cowl_data_one_of_retain(CowlDataOneOf *range) {
    return cowl_object_retain(range);
}

void cowl_data_one_of_release(CowlDataOneOf *range) {
    if (range && !cowl_object_release(range)) {
        cowl_data_one_of_free(range);
    }
}

CowlLiteralSet* cowl_data_one_of_get_values(CowlDataOneOf *range) {
    return range->values;
}

CowlString* cowl_data_one_of_to_string(CowlDataOneOf *range)
    COWL_TO_STRING_IMPL(data_one_of, range)

bool cowl_data_one_of_equals(CowlDataOneOf *lhs, CowlDataOneOf *rhs) {
    return cowl_literal_set_equals(lhs->values, rhs->values);
}

cowl_uint_t cowl_data_one_of_hash(CowlDataOneOf *range) {
    return cowl_object_hash_get(range);
}

bool cowl_data_one_of_iterate_signature(CowlDataOneOf *range, CowlEntityIterator *iter) {
    return cowl_literal_set_iterate_signature(range->values, iter);
}
