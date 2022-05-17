/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_data_private.h"
#include "cowl_hash_utils.h"
#include "cowl_macros.h"
#include "cowl_template.h"
#include "cowl_vector.h"

static CowlNAryData* cowl_nary_data_alloc(CowlObjectType type, CowlVector *operands) {
    CowlNAryData *range = ulib_alloc(range);
    if (!range) return NULL;

    *range = (CowlNAryData) {
        .super = COWL_OBJECT_INIT(type),
        .operands = cowl_vector_retain(operands)
    };

    return range;
}

static void cowl_nary_data_free(CowlNAryData *range) {
    cowl_vector_release(range->operands);
    ulib_free(range);
}

CowlNAryData* cowl_nary_data_get(CowlNAryType type, CowlVector *operands) {
    if (!(operands && cowl_enum_value_is_valid(NT, type))) return NULL;
    return cowl_nary_data_alloc(COWL_OT_DR_DATA_INTERSECT + type, operands);
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

CowlVector* cowl_nary_data_get_operands(CowlNAryData *range) {
    return range->operands;
}

CowlString* cowl_nary_data_to_string(CowlNAryData *range)
    COWL_TO_STRING_IMPL(nary_data, range)

bool cowl_nary_data_equals(CowlNAryData *lhs, CowlNAryData *rhs) {
    return cowl_object_type_equals(lhs, rhs) &&
           cowl_vector_equals_no_order(lhs->operands, rhs->operands);
}

ulib_uint cowl_nary_data_hash(CowlNAryData *range) {
    return cowl_hash_2(COWL_HASH_INIT_DATA_NARY,
                       cowl_nary_data_get_type(range),
                       cowl_vector_hash_no_order(range->operands));
}

bool cowl_nary_data_iterate_primitives(CowlNAryData *range, CowlPrimitiveFlags flags,
                                       CowlIterator *iter) {
    return cowl_vector_iterate_primitives(range->operands, flags, iter);
}
