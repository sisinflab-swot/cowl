/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_EXP_PRIVATE_H
#define COWL_DATA_PROP_EXP_PRIVATE_H

#include "cowl_data_prop_exp.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDataPropExp) {
    CowlObject super;
};

#define COWL_DATA_PROP_EXP_INIT { .super = COWL_OBJECT_INIT }

COWL_END_DECLS

#endif // COWL_DATA_PROP_EXP_PRIVATE_H
