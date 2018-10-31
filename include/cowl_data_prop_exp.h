/// @author Ivano Bilenchi

#ifndef COWL_COWL_DATA_PROP_EXP_H
#define COWL_COWL_DATA_PROP_EXP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlDataProp const CowlDataProp;

typedef struct CowlDataPropExp const CowlDataPropExp;

CowlDataPropExp* cowl_data_prop_exp_retain(CowlDataPropExp *prop);
void cowl_data_prop_exp_release(CowlDataPropExp *prop);

CowlDataProp* cowl_data_prop_exp_get_prop(CowlDataPropExp *exp);

bool cowl_data_prop_exp_equals(CowlDataPropExp *lhs, CowlDataPropExp *rhs);
uint32_t cowl_data_prop_exp_hash(CowlDataPropExp *exp);

bool cowl_data_prop_exp_iterate_signature(CowlDataPropExp *prop, void *ctx,
                                          CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_COWL_DATA_PROP_EXP_H
