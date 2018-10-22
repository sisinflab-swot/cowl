/// @author Ivano Bilenchi

#ifndef COWL_OBJ_MAX_CARD_PRIVATE_H
#define COWL_OBJ_MAX_CARD_PRIVATE_H

#include "cowl_obj_max_card.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

struct CowlObjMaxCard {
    CowlClsExp super;
    CowlObjPropExp *prop;
    CowlClsExp *filler;
    uint32_t cardinality;
};

COWL_END_DECLS

#endif // COWL_OBJ_MAX_CARD_PRIVATE_H
