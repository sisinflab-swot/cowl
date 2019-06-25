/// @author Ivano Bilenchi

#ifndef COWL_ANNOT_VALUE_TYPE_H
#define COWL_ANNOT_VALUE_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

typedef enum CowlAnnotValueType {
    CAVT_IRI,
    CAVT_LITERAL,
    CAVT_ANON_IND
} CowlAnnotValueType;

COWL_END_DECLS

#endif // COWL_ANNOT_VALUE_TYPE_H
