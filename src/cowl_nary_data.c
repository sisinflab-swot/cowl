/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_data_private.h"
#include "cowl_hash_utils.h"
#include "cowl_macros.h"
#include "cowl_object_table.h"
#include "cowl_template.h"

static CowlNAryData* cowl_nary_data_alloc(CowlDataRangeType type, CowlObjectTable *operands) {
    CowlNAryData *range = ulib_alloc(range);
    if (!range) return NULL;

    ulib_uint hash = cowl_hash_2(COWL_HASH_INIT_DATA_NARY, type,
                                 cowl_object_set_hash(operands));

    *range = (CowlNAryData) {
        .super = COWL_DATA_RANGE_INIT(type, hash),
        .operands = operands
    };

    return range;
}

static void cowl_nary_data_free(CowlNAryData *range) {
    cowl_object_set_free(range->operands);
    ulib_free(range);
}

CowlNAryData* cowl_nary_data_get(CowlNAryType type, CowlObjectTable *operands) {
    if (!(operands && cowl_enum_value_is_valid(NT, type))) return NULL;
    return cowl_nary_data_alloc((CowlDataRangeType)type + COWL_DRT_DATA_INTERSECT, operands);
}

CowlNAryData* cowl_nary_data_retain(CowlNAryData *range) {
    return cowl_object_incr_ref(range);
}

void cowl_nary_data_release(CowlNAryData *range) {
    if (range && !cowl_object_decr_ref(range)) {
        cowl_nary_data_free(range);
    }
}

CowlNAryType cowl_nary_data_get_type(CowlNAryData *range) {
    return (CowlNAryType)(cowl_get_type(range) - COWL_OT_DR_DATA_INTERSECT);
}

CowlObjectTable* cowl_nary_data_get_operands(CowlNAryData *range) {
    return range->operands;
}

CowlString* cowl_nary_data_to_string(CowlNAryData *range)
    COWL_TO_STRING_IMPL(nary_data, range)

bool cowl_nary_data_equals(CowlNAryData *lhs, CowlNAryData *rhs) {
    return cowl_object_type_equals(lhs, rhs) &&
           cowl_object_hash_equals(lhs, rhs) &&
           cowl_object_set_equals(lhs->operands, rhs->operands);
}

ulib_uint cowl_nary_data_hash(CowlNAryData *range) {
    return cowl_object_hash_get(range);
}

bool cowl_nary_data_iterate_primitives(CowlNAryData *range, CowlPrimitiveFlags flags,
                                       CowlIterator *iter) {
    return cowl_object_set_iterate_primitives(range->operands, flags, iter);
}
