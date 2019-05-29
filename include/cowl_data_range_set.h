/// @author Ivano Bilenchi

#ifndef COWL_DATA_RANGE_SET_H
#define COWL_DATA_RANGE_SET_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataRange);

UHASH_SET_DECL(CowlDataRangeSet, CowlDataRange*)
cowl_hash_decl(CowlDataRangeSet);

void cowl_data_range_set_free(CowlDataRangeSet *set);

COWL_END_DECLS

#endif // COWL_DATA_RANGE_SET_H
