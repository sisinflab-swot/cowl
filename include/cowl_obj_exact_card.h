/// @author Ivano Bilenchi

#ifndef COWL_OBJ_EXACT_CARD_H
#define COWL_OBJ_EXACT_CARD_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;
typedef struct CowlObjPropExp CowlObjPropExp;

typedef struct CowlObjExactCard CowlObjExactCard;

CowlObjExactCard const* cowl_obj_exact_card_get(CowlObjPropExp const *prop,
                                                CowlClsExp const *filler, uint32_t cardinality);
CowlObjExactCard const* cowl_obj_exact_card_retain(CowlObjExactCard const *restr);
void cowl_obj_exact_card_release(CowlObjExactCard const *restr);

CowlObjPropExp const* cowl_obj_exact_card_get_prop(CowlObjExactCard const *restr);
CowlClsExp const* cowl_obj_exact_card_get_filler(CowlObjExactCard const *restr);
uint32_t cowl_obj_exact_card_get_cardinality(CowlObjExactCard const *restr);

bool cowl_obj_exact_card_equals(CowlObjExactCard const *lhs, CowlObjExactCard const *rhs);
uint32_t cowl_obj_exact_card_hash(CowlObjExactCard const *restr);

bool cowl_obj_exact_card_iterate_signature(CowlObjExactCard const *restr,
                                           void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_EXACT_CARD_H
