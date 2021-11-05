/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_range_private.h"
#include "cowl_template.h"

CowlDataRange* cowl_data_range_retain(CowlDataRange *range) {
    return cowl_object_incr_ref(range);
}

void cowl_data_range_release(CowlDataRange *range) {
    cowl_object_release((CowlObject *)range);
}

CowlDataRangeType cowl_data_range_get_type(CowlDataRange *range) {
    return (CowlDataRangeType)(cowl_get_type(range) - COWL_OT_DR_DATATYPE);
}

CowlString* cowl_data_range_to_string(CowlDataRange *range)
    COWL_TO_STRING_IMPL(data_range, range)

bool cowl_data_range_equals(CowlDataRange *lhs, CowlDataRange *rhs) {
    return cowl_object_equals((CowlObject *)lhs, (CowlObject *)rhs);
}

ulib_uint cowl_data_range_hash(CowlDataRange *range) {
    return cowl_object_hash_get(range);
}

bool cowl_data_range_iterate_primitives(CowlDataRange *range, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return cowl_object_iterate_primitives((CowlObject *)range, flags, iter);
}
