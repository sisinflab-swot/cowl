/// @author Ivano Bilenchi

#ifndef COWL_DATA_HAS_VALUE_PRIVATE_H
#define COWL_DATA_HAS_VALUE_PRIVATE_H

#include "cowl_data_has_value.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDataHasValue) {
    CowlClsExp super;
    CowlDataPropExp *prop;
    CowlLiteral *value;
};

COWL_END_DECLS

#endif // COWL_DATA_HAS_VALUE_PRIVATE_H
