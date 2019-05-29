/// @author Ivano Bilenchi

#ifndef COWL_DATA_RANGE_H
#define COWL_DATA_RANGE_H

#include "cowl_data_range_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlObjPropExp);

cowl_struct_decl(CowlDataRange);

CowlDataRange* cowl_data_range_retain(CowlDataRange *range);
void cowl_data_range_release(CowlDataRange *range);

CowlDataRangeType cowl_data_range_get_type(CowlDataRange *range);

bool cowl_data_range_equals(CowlDataRange *lhs, CowlDataRange *rhs);
cowl_uint_t cowl_data_range_hash(CowlDataRange *range);

bool cowl_data_range_iterate_signature(CowlDataRange *range, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_DATA_RANGE_H
