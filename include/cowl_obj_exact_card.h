/// @author Ivano Bilenchi

#ifndef COWL_OBJ_EXACT_CARD_H
#define COWL_OBJ_EXACT_CARD_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp const CowlClsExp;
typedef struct CowlObjPropExp const CowlObjPropExp;

typedef struct CowlObjExactCard const CowlObjExactCard;

CowlObjExactCard* cowl_obj_exact_card_get(CowlObjPropExp *prop, CowlClsExp *filler,
                                          uint32_t cardinality);
CowlObjExactCard* cowl_obj_exact_card_retain(CowlObjExactCard *restr);
void cowl_obj_exact_card_release(CowlObjExactCard *restr);

CowlObjPropExp* cowl_obj_exact_card_get_prop(CowlObjExactCard *restr);
CowlClsExp* cowl_obj_exact_card_get_filler(CowlObjExactCard *restr);
uint32_t cowl_obj_exact_card_get_cardinality(CowlObjExactCard *restr);

bool cowl_obj_exact_card_equals(CowlObjExactCard *lhs, CowlObjExactCard *rhs);
uint32_t cowl_obj_exact_card_hash(CowlObjExactCard *restr);

bool cowl_obj_exact_card_iterate_signature(CowlObjExactCard *restr,
                                           void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_EXACT_CARD_H
