/// @author Ivano Bilenchi

#ifndef COWL_DATA_RANGE_SET_H
#define COWL_DATA_RANGE_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataRange);

UHASH_SET_DECL(CowlDataRangeSet, CowlDataRange*)
cowl_hash_decl(CowlDataRangeSet);

void cowl_data_range_set_free(CowlDataRangeSet *set);

bool cowl_data_range_set_equals(CowlDataRangeSet *lhs, CowlDataRangeSet *rhs);
cowl_uint_t cowl_data_range_set_hash(CowlDataRangeSet *set);

bool cowl_data_range_set_iterate_signature(CowlDataRangeSet *set, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_DATA_RANGE_SET_H
