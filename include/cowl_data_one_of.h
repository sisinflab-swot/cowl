/// @author Ivano Bilenchi

#ifndef COWL_COWL_DATA_ONE_OF_H
#define COWL_COWL_DATA_ONE_OF_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlLiteralSet);

cowl_struct_decl(CowlDataOneOf);

CowlDataOneOf* cowl_data_one_of_get(CowlLiteralSet *values);
CowlDataOneOf* cowl_data_one_of_retain(CowlDataOneOf *range);
void cowl_data_one_of_release(CowlDataOneOf *range);

CowlLiteralSet* cowl_data_one_of_get_values(CowlDataOneOf *range);

bool cowl_data_one_of_equals(CowlDataOneOf *lhs, CowlDataOneOf *rhs);
cowl_uint_t cowl_data_one_of_hash(CowlDataOneOf *range);

bool cowl_data_one_of_iterate_signature(CowlDataOneOf *range, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_COWL_DATA_ONE_OF_H
