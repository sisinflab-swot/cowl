/// @author Ivano Bilenchi

#ifndef COWL_OBJ_MAX_CARD_H
#define COWL_OBJ_MAX_CARD_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;
typedef struct CowlObjPropExp CowlObjPropExp;

typedef struct CowlObjMaxCard CowlObjMaxCard;

CowlObjMaxCard const* cowl_obj_max_card_get(CowlObjPropExp const *prop,
                                            CowlClsExp const *filler, uint32_t cardinality);
CowlObjMaxCard const* cowl_obj_max_card_retain(CowlObjMaxCard const *restr);
void cowl_obj_max_card_release(CowlObjMaxCard const *restr);

CowlObjPropExp const* cowl_obj_max_card_get_prop(CowlObjMaxCard const *restr);
CowlClsExp const* cowl_obj_max_card_get_filler(CowlObjMaxCard const *restr);
uint32_t cowl_obj_max_card_get_cardinality(CowlObjMaxCard const *restr);

bool cowl_obj_max_card_equals(CowlObjMaxCard const *lhs, CowlObjMaxCard const *rhs);
uint32_t cowl_obj_max_card_hash(CowlObjMaxCard const *restr);

bool cowl_obj_max_card_iterate_signature(CowlObjMaxCard const *restr,
                                         void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_MAX_CARD_H