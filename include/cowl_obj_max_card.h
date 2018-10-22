/// @author Ivano Bilenchi

#ifndef COWL_OBJ_MAX_CARD_H
#define COWL_OBJ_MAX_CARD_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp const CowlClsExp;
typedef struct CowlObjPropExp const CowlObjPropExp;

typedef struct CowlObjMaxCard const CowlObjMaxCard;

CowlObjMaxCard* cowl_obj_max_card_get(CowlObjPropExp *prop, CowlClsExp *filler,
                                      uint32_t cardinality);
CowlObjMaxCard* cowl_obj_max_card_retain(CowlObjMaxCard *restr);
void cowl_obj_max_card_release(CowlObjMaxCard *restr);

CowlObjPropExp* cowl_obj_max_card_get_prop(CowlObjMaxCard *restr);
CowlClsExp* cowl_obj_max_card_get_filler(CowlObjMaxCard *restr);
uint32_t cowl_obj_max_card_get_cardinality(CowlObjMaxCard *restr);

bool cowl_obj_max_card_equals(CowlObjMaxCard *lhs, CowlObjMaxCard *rhs);
uint32_t cowl_obj_max_card_hash(CowlObjMaxCard *restr);

bool cowl_obj_max_card_iterate_signature(CowlObjMaxCard *restr,
                                         void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_MAX_CARD_H
