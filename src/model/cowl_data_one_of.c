/// @author Ivano Bilenchi

#include "cowl_data_one_of_private.h"
#include "cowl_hash_utils.h"
#include "cowl_literal.h"
#include "cowl_literal_set.h"

static CowlDataOneOf* cowl_data_one_of_alloc(CowlLiteralSet *values) {
    cowl_uint_t hash = cowl_hash_1(COWL_HASH_INIT_DATA_ONE_OF, cowl_literal_set_hash(values));

    CowlDataOneOf init = {
        .super = COWL_DATA_RANGE_INIT(COWL_DRT_DATA_ONE_OF, hash),
        .values = values
    };

    cowl_struct(CowlDataOneOf) *range = malloc(sizeof(*range));
    memcpy(range, &init, sizeof(*range));
    return range;
}

static void cowl_data_one_of_free(CowlDataOneOf *range) {
    if (!range) return;
    cowl_literal_set_free(range->values);
    free((void *)range);
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

bool cowl_data_one_of_equals(CowlDataOneOf *lhs, CowlDataOneOf *rhs) {
    return cowl_literal_set_equals(lhs->values, rhs->values);
}

cowl_uint_t cowl_data_one_of_hash(CowlDataOneOf *range) {
    return cowl_object_hash_get(range);
}

bool cowl_data_one_of_iterate_signature(CowlDataOneOf *range, CowlEntityIterator *iter) {
    return cowl_literal_set_iterate_signature(range->values, iter);
}
