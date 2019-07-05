/// @author Ivano Bilenchi

#ifndef COWL_ANNOT_VALUE_TYPE_H
#define COWL_ANNOT_VALUE_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

typedef enum CowlAnnotValueType {
    COWL_AVT_IRI,
    COWL_AVT_LITERAL,
    COWL_AVT_ANON_IND,
    COWL_AVT_COUNT,
    COWL_AVT_FIRST = COWL_AVT_IRI
} CowlAnnotValueType;

COWL_END_DECLS

#endif // COWL_ANNOT_VALUE_TYPE_H
