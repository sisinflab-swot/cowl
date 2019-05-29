/// @author Ivano Bilenchi

#include "cowl_nary_data_private.h"
#include "cowl_data_range_set.h"
#include "cowl_hash_utils.h"

static CowlNAryData* cowl_nary_data_alloc(CowlDataRangeType type, CowlDataRangeSet *operands) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_DATA_NARY, type,
                                   uhset_hash(CowlDataRangeSet, operands));

    CowlNAryData init = {
        .super = COWL_DATA_RANGE_INIT(type, hash),
        .operands = operands
    };

    cowl_struct(CowlNAryData) *range = malloc(sizeof(*range));
    memcpy(range, &init, sizeof(*range));
    return range;
}

static void cowl_nary_data_free(CowlNAryData *range) {
    if (!range) return;
    cowl_data_range_set_free(range->operands);
    free((void *)range);
}

CowlNAryData* cowl_nary_data_get(CowlNAryType type, CowlDataRangeSet *operands) {
    return cowl_nary_data_alloc((CowlDataRangeType)type + CDRT_DATA_INTERSECTION, operands);
}

CowlNAryData* cowl_nary_data_retain(CowlNAryData *range) {
    return cowl_data_range_ref_incr(range);
}

void cowl_nary_data_release(CowlNAryData *range) {
    if (range && !cowl_data_range_ref_decr(range)) {
        cowl_nary_data_free(range);
    }
}

CowlNAryType cowl_nary_data_get_type(CowlNAryData *range) {
    return (CowlNAryType)(range->super.type - CDRT_DATA_INTERSECTION);
}

CowlDataRangeSet* cowl_nary_data_get_operands(CowlNAryData *range) {
    return range->operands;
}

bool cowl_nary_data_equals(CowlNAryData *lhs, CowlNAryData *rhs) {
    return (lhs->super.type == rhs->super.type &&
            uhset_equals(CowlDataRangeSet, lhs->operands, rhs->operands));
}

cowl_uint_t cowl_nary_data_hash(CowlNAryData *range) {
    return cowl_data_range_hash_get(range);
}

bool cowl_nary_data_iterate_signature(CowlNAryData *range,
                                      void *ctx, CowlEntityIterator iter) {
    uhash_foreach_key(CowlDataRangeSet, range->operands, operand, {
        if (!cowl_data_range_iterate_signature(operand, ctx, iter)) return false;
    });
    return true;
}
