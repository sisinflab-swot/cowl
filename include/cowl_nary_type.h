/// @author Ivano Bilenchi

#ifndef COWL_NARY_TYPE_H
#define COWL_NARY_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

typedef enum CowlNAryType {
    COWL_NT_INTERSECT,
    COWL_NT_UNION,
    COWL_NT_COUNT,
    COWL_NT_FIRST = COWL_NT_INTERSECT
} CowlNAryType;

COWL_END_DECLS

#endif // COWL_NARY_TYPE_H
