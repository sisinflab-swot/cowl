/// @author Ivano Bilenchi

#ifndef COWL_OBJ_CARD_H
#define COWL_OBJ_CARD_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp const CowlClsExp;
typedef struct CowlObjPropExp const CowlObjPropExp;

typedef struct CowlObjCard const CowlObjCard;

typedef enum CowlObjCardType {
    COCT_MIN,
    COCT_MAX,
    COCT_EXACT
} CowlObjCardType;

CowlObjCard *cowl_obj_card_get(CowlObjCardType type, CowlObjPropExp *prop,
                               CowlClsExp *filler, uint32_t cardinality);
CowlObjCard* cowl_obj_card_retain(CowlObjCard *restr);
void cowl_obj_card_release(CowlObjCard *restr);

CowlObjCardType cowl_obj_card_get_type(CowlObjCard *restr);
CowlObjPropExp* cowl_obj_card_get_prop(CowlObjCard *restr);
CowlClsExp* cowl_obj_card_get_filler(CowlObjCard *restr);
uint32_t cowl_obj_card_get_cardinality(CowlObjCard *restr);

bool cowl_obj_card_equals(CowlObjCard *lhs, CowlObjCard *rhs);
uint32_t cowl_obj_card_hash(CowlObjCard *restr);

bool cowl_obj_card_iterate_signature(CowlObjCard *restr,
                                     void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_CARD_H
