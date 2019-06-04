/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_EXP_SET_PRIVATE_H
#define COWL_DATA_PROP_EXP_SET_PRIVATE_H

#include "cowl_data_prop_exp_set.h"

COWL_BEGIN_DECLS

cowl_hash_decl_mutable(CowlDataPropExpSet, CowlMutableDataPropExpSet);

bool cowl_data_prop_exp_set_insert(CowlMutableDataPropExpSet *set, CowlDataPropExp *exp);

COWL_END_DECLS

#endif // COWL_DATA_PROP_EXP_SET_PRIVATE_H
