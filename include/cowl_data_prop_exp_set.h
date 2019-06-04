/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_EXP_SET_H
#define COWL_DATA_PROP_EXP_SET_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataPropExp);

UHASH_SET_DECL(CowlDataPropExpSet, CowlDataPropExp*)
cowl_hash_decl(CowlDataPropExpSet);

void cowl_data_prop_exp_set_free(CowlDataPropExpSet *set);

COWL_END_DECLS

#endif // COWL_DATA_PROP_EXP_SET_H
