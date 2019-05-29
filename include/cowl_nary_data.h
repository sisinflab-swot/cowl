/// @author Ivano Bilenchi

#ifndef COWL_NARY_DATA_H
#define COWL_NARY_DATA_H

#include "cowl_std.h"
#include "cowl_iterator.h"
#include "cowl_nary_type.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlDataRangeSet);

cowl_struct_decl(CowlNAryData);

CowlNAryData* cowl_nary_data_get(CowlNAryType type, CowlDataRangeSet *operands);
CowlNAryData* cowl_nary_data_retain(CowlNAryData *exp);
void cowl_nary_data_release(CowlNAryData *exp);

CowlNAryType cowl_nary_data_get_type(CowlNAryData *exp);
CowlDataRangeSet* cowl_nary_data_get_operands(CowlNAryData *exp);

bool cowl_nary_data_equals(CowlNAryData *lhs, CowlNAryData *rhs);
cowl_uint_t cowl_nary_data_hash(CowlNAryData *exp);

bool cowl_nary_data_iterate_signature(CowlNAryData *exp, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_NARY_DATA_H
