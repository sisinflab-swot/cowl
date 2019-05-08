/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_EXP_PRIVATE_H
#define COWL_DATA_PROP_EXP_PRIVATE_H

#include "cowl_data_prop_exp.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDataPropExp) {
    cowl_uint_t ref_count;
};

#define COWL_DATA_PROP_EXP_INIT { .ref_count = 1 }

#define cowl_data_prop_exp_ref_get(d) (((cowl_struct(CowlDataPropExp) *)(d))->ref_count)
#define cowl_data_prop_exp_ref_incr(d) (++cowl_data_prop_exp_ref_get(d), (d))
#define cowl_data_prop_exp_ref_decr(d) (--cowl_data_prop_exp_ref_get(d))

COWL_END_DECLS

#endif // COWL_DATA_PROP_EXP_PRIVATE_H
