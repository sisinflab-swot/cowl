/// @author Ivano Bilenchi

#ifndef COWL_QUANT_TYPE_H
#define COWL_QUANT_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

typedef enum CowlQuantType {
    COWL_QT_SOME,
    COWL_QT_ALL,
    COWL_QT_COUNT,
    COWL_QT_FIRST = COWL_QT_SOME
} CowlQuantType;

COWL_END_DECLS

#endif // COWL_QUANT_TYPE_H
