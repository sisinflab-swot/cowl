/// @author Ivano Bilenchi

#ifndef COWL_DATA_CARD_H
#define COWL_DATA_CARD_H

#include "cowl_std.h"
#include "cowl_card_type.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDataPropExp);

cowl_struct_decl(CowlDataCard);

CowlDataCard* cowl_data_card_get(CowlCardType type, CowlDataPropExp *prop,
                                 CowlDataRange *range, cowl_uint_t cardinality);
CowlDataCard* cowl_data_card_retain(CowlDataCard *restr);
void cowl_data_card_release(CowlDataCard *restr);

CowlCardType cowl_data_card_get_type(CowlDataCard *restr);
CowlDataPropExp* cowl_data_card_get_prop(CowlDataCard *restr);
CowlDataRange* cowl_data_card_get_range(CowlDataCard *restr);
cowl_uint_t cowl_data_card_get_cardinality(CowlDataCard *restr);

bool cowl_data_card_equals(CowlDataCard *lhs, CowlDataCard *rhs);
cowl_uint_t cowl_data_card_hash(CowlDataCard *restr);

bool cowl_data_card_iterate_signature(CowlDataCard *restr, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_DATA_CARD_H
