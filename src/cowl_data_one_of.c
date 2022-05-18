/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_one_of_private.h"
#include "cowl_hash_utils.h"
#include "cowl_template.h"
#include "cowl_vector.h"

static CowlDataOneOf* cowl_data_one_of_alloc(CowlVector *values) {
    CowlDataOneOf *range = ulib_alloc(range);
    if (!range) return NULL;

    *range = (CowlDataOneOf) {
        .super = COWL_OBJECT_INIT(COWL_OT_DR_DATA_ONE_OF),
        .values = cowl_vector_retain(values)
    };

    return range;
}

static void cowl_data_one_of_free(CowlDataOneOf *range) {
    cowl_vector_release(range->values);
    ulib_free(range);
}

CowlDataOneOf* cowl_data_one_of_get(CowlVector *values) {
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

CowlVector* cowl_data_one_of_get_values(CowlDataOneOf *range) {
    return range->values;
}

CowlString* cowl_data_one_of_to_string(CowlDataOneOf *range)
    COWL_TO_STRING_IMPL(data_one_of, range)

bool cowl_data_one_of_equals(CowlDataOneOf *lhs, CowlDataOneOf *rhs) {
    return cowl_vector_equals(lhs->values, rhs->values);
}

ulib_uint cowl_data_one_of_hash(CowlDataOneOf *range) {
    return cowl_hash_1(COWL_HASH_INIT_DATA_ONE_OF, cowl_vector_hash(range->values));
}

bool cowl_data_one_of_iterate_primitives(CowlDataOneOf *range, CowlPrimitiveFlags flags,
                                         CowlIterator *iter) {
    return cowl_vector_iterate_primitives(range->values, flags, iter);
}
