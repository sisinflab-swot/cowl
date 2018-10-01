/// @author Ivano Bilenchi

#ifndef COWL_OBJ_EXACT_CARD_PRIVATE_H
#define COWL_OBJ_EXACT_CARD_PRIVATE_H

#include "cowl_obj_exact_card.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

typedef struct CowlObjExactCard {
    CowlClsExp super;
    CowlObjPropExp const *prop;
    CowlClsExp const *filler;
    uint32_t cardinality;
} CowlObjExactCard;

COWL_END_DECLS

#endif // COWL_OBJ_EXACT_CARD_PRIVATE_H
