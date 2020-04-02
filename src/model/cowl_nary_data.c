/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_data_private.h"
#include "cowl_alloc.h"
#include "cowl_data_range_set.h"
#include "cowl_hash_utils.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlNAryData* cowl_nary_data_alloc(CowlDataRangeType type, CowlDataRangeSet *operands) {
    CowlNAryData *range = cowl_alloc(range);
    if (!range) return NULL;

    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_DATA_NARY, type,
                                   uhset_hash(CowlDataRangeSet, operands));

    *range = (CowlNAryData) {
        .super = COWL_DATA_RANGE_INIT(type, hash),
        .operands = operands
    };

    return range;
}

static void cowl_nary_data_free(CowlNAryData *range) {
    if (!range) return;
    cowl_data_range_set_free(range->operands);
    cowl_free(range);
}

CowlNAryData* cowl_nary_data_get(CowlNAryType type, CowlDataRangeSet *operands) {
    return cowl_nary_data_alloc((CowlDataRangeType)type + COWL_DRT_DATA_INTERSECT, operands);
}

CowlNAryData* cowl_nary_data_retain(CowlNAryData *range) {
    return cowl_object_retain(range);
}

void cowl_nary_data_release(CowlNAryData *range) {
    if (range && !cowl_object_release(range)) {
        cowl_nary_data_free(range);
    }
}

CowlNAryType cowl_nary_data_get_type(CowlNAryData *range) {
    return (CowlNAryType)(range->super.type - COWL_DRT_DATA_INTERSECT);
}

CowlDataRangeSet* cowl_nary_data_get_operands(CowlNAryData *range) {
    return range->operands;
}

CowlString* cowl_nary_data_to_string(CowlNAryData *range)
    COWL_TO_STRING_IMPL(nary_data, range)

bool cowl_nary_data_equals(CowlNAryData *lhs, CowlNAryData *rhs) {
    return (lhs->super.type == rhs->super.type &&
            uhset_equals(CowlDataRangeSet, lhs->operands, rhs->operands));
}

cowl_uint_t cowl_nary_data_hash(CowlNAryData *range) {
    return cowl_object_hash_get(range);
}

bool cowl_nary_data_iterate_signature(CowlNAryData *range, CowlEntityIterator *iter) {
    return cowl_data_range_set_iterate_signature(range->operands, iter);
}

bool cowl_nary_data_iterate_primitives(CowlNAryData *range, CowlPrimitiveIterator *iter) {
    return cowl_data_range_set_iterate_primitives(range->operands, iter);
}
