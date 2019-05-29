/// @author Ivano Bilenchi

#ifndef COWL_DATA_QUANT_PRIVATE_H
#define COWL_DATA_QUANT_PRIVATE_H

#include "cowl_data_quant.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDataQuant) {
    CowlClsExp super;
    CowlDataPropExp *prop;
    CowlDataRange *range;
};

COWL_END_DECLS

#endif // COWL_DATA_QUANT_PRIVATE_H
