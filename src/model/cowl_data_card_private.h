/// @author Ivano Bilenchi

#ifndef COWL_DATA_CARD_PRIVATE_H
#define COWL_DATA_CARD_PRIVATE_H

#include "cowl_data_card.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDataCard) {
    CowlClsExp super;
    cowl_uint_t cardinality;
    CowlDataPropExp *prop;
    CowlDataRange *range;
};

COWL_END_DECLS

#endif // COWL_DATA_CARD_PRIVATE_H
