/// @author Ivano Bilenchi

#ifndef COWL_OBJ_MIN_CARD_H
#define COWL_OBJ_MIN_CARD_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;
typedef struct CowlObjPropExp CowlObjPropExp;

typedef struct CowlObjMinCard CowlObjMinCard;

CowlObjPropExp const* cowl_obj_min_card_get_prop(CowlObjMinCard const *restr);
CowlClsExp const* cowl_obj_min_card_get_filler(CowlObjMinCard const *restr);
uint32_t cowl_obj_min_card_get_cardinality(CowlObjMinCard const *restr);

bool cowl_obj_min_card_enum_signature(CowlObjMinCard const *restr, void *ctx,
                                      CowlEntityIterator iter);

bool cowl_obj_min_card_equals(CowlObjMinCard const *lhs, CowlObjMinCard const *rhs);
uint32_t cowl_obj_min_card_hash(CowlObjMinCard const *restr);

COWL_END_DECLS

#endif // COWL_OBJ_MIN_CARD_H
