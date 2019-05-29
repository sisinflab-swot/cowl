/// @author Ivano Bilenchi

#include "cowl_data_range_set_private.h"
#include "cowl_data_range.h"

UHASH_SET_IMPL(CowlDataRangeSet, CowlDataRange*, cowl_data_range_hash, cowl_data_range_equals)

bool cowl_data_range_set_insert(CowlMutableDataRangeSet *set, CowlDataRange *range) {
    return uhset_insert(CowlDataRangeSet, set, cowl_data_range_retain(range)) == UHASH_INSERTED;
}

void cowl_data_range_set_free(CowlDataRangeSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlDataRangeSet, set, range, cowl_data_range_release(range));
    uhash_free(CowlDataRangeSet, (UHash(CowlDataRangeSet) *)set);
}
