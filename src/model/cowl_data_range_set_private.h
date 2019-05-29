/// @author Ivano Bilenchi

#ifndef COWL_DATA_RANGE_SET_PRIVATE_H
#define COWL_DATA_RANGE_SET_PRIVATE_H

#include "cowl_data_range_set.h"

COWL_BEGIN_DECLS

cowl_hash_decl_mutable(CowlDataRangeSet, CowlMutableDataRangeSet);

bool cowl_data_range_set_insert(CowlMutableDataRangeSet *set, CowlDataRange *range);

COWL_END_DECLS

#endif // COWL_DATA_RANGE_SET_PRIVATE_H
