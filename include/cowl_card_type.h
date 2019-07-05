/// @author Ivano Bilenchi

#ifndef COWL_CARD_TYPE_H
#define COWL_CARD_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

typedef enum CowlCardType {
    COWL_CT_MIN,
    COWL_CT_MAX,
    COWL_CT_EXACT,
    COWL_CT_COUNT,
    COWL_CT_FIRST = COWL_CT_MIN
} CowlCardType;

COWL_END_DECLS

#endif // COWL_CARD_TYPE_H
