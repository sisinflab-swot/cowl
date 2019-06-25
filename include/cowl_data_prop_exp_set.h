/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_EXP_SET_H
#define COWL_DATA_PROP_EXP_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataPropExp);

UHASH_SET_DECL(CowlDataPropExpSet, CowlDataPropExp*)
cowl_hash_decl(CowlDataPropExpSet);

void cowl_data_prop_exp_set_free(CowlDataPropExpSet *set);

bool cowl_data_prop_exp_set_equals(CowlDataPropExpSet *lhs, CowlDataPropExpSet *rhs);
cowl_uint_t cowl_data_prop_exp_set_hash(CowlDataPropExpSet *set);

bool cowl_data_prop_exp_set_iterate_signature(CowlDataPropExpSet *set, void *ctx,
                                              CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_DATA_PROP_EXP_SET_H
