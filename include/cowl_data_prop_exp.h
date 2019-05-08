/// @author Ivano Bilenchi

#ifndef COWL_COWL_DATA_PROP_EXP_H
#define COWL_COWL_DATA_PROP_EXP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataProp);

cowl_struct_decl(CowlDataPropExp);

CowlDataPropExp* cowl_data_prop_exp_retain(CowlDataPropExp *prop);
void cowl_data_prop_exp_release(CowlDataPropExp *prop);

CowlDataProp* cowl_data_prop_exp_get_prop(CowlDataPropExp *exp);

bool cowl_data_prop_exp_equals(CowlDataPropExp *lhs, CowlDataPropExp *rhs);
cowl_uint_t cowl_data_prop_exp_hash(CowlDataPropExp *exp);

bool cowl_data_prop_exp_iterate_signature(CowlDataPropExp *prop, void *ctx,
                                          CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_COWL_DATA_PROP_EXP_H
