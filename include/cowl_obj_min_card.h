/// @author Ivano Bilenchi

#ifndef COWL_OBJ_MIN_CARD_H
#define COWL_OBJ_MIN_CARD_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp const CowlClsExp;
typedef struct CowlObjPropExp const CowlObjPropExp;

typedef struct CowlObjMinCard const CowlObjMinCard;

CowlObjMinCard* cowl_obj_min_card_get(CowlObjPropExp *prop, CowlClsExp *filler,
                                      uint32_t cardinality);
CowlObjMinCard* cowl_obj_min_card_retain(CowlObjMinCard *restr);
void cowl_obj_min_card_release(CowlObjMinCard *restr);

CowlObjPropExp* cowl_obj_min_card_get_prop(CowlObjMinCard *restr);
CowlClsExp* cowl_obj_min_card_get_filler(CowlObjMinCard *restr);
uint32_t cowl_obj_min_card_get_cardinality(CowlObjMinCard *restr);

bool cowl_obj_min_card_equals(CowlObjMinCard *lhs, CowlObjMinCard *rhs);
uint32_t cowl_obj_min_card_hash(CowlObjMinCard *restr);

bool cowl_obj_min_card_iterate_signature(CowlObjMinCard *restr,
                                         void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_MIN_CARD_H
