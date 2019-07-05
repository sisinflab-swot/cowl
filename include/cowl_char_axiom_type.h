/// @author Ivano Bilenchi

#ifndef COWL_CHAR_AXIOM_TYPE_H
#define COWL_CHAR_AXIOM_TYPE_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef enum CowlCharAxiomType {
    COWL_CAT_FUNC,
    COWL_CAT_INV_FUNC,
    COWL_CAT_SYMM,
    COWL_CAT_ASYMM,
    COWL_CAT_TRANS,
    COWL_CAT_REFL,
    COWL_CAT_IRREFL,
    COWL_CAT_COUNT,
    COWL_CAT_FIRST = COWL_CAT_FUNC
} CowlCharAxiomType;

COWL_END_DECLS

#endif // COWL_CHAR_AXIOM_TYPE_H
