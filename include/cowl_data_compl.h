/// @author Ivano Bilenchi

#ifndef COWL_DATA_COMPL_H
#define COWL_DATA_COMPL_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataRange);

cowl_struct_decl(CowlDataCompl);

CowlDataCompl* cowl_data_compl_get(CowlDataRange *operand);
CowlDataCompl* cowl_data_compl_retain(CowlDataCompl *range);
void cowl_data_compl_release(CowlDataCompl *range);

CowlDataRange* cowl_data_compl_get_operand(CowlDataCompl *range);

bool cowl_data_compl_equals(CowlDataCompl *lhs, CowlDataCompl *rhs);
cowl_uint_t cowl_data_compl_hash(CowlDataCompl *range);

bool cowl_data_compl_iterate_signature(CowlDataCompl *range, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_DATA_COMPL_H
