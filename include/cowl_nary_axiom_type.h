/// @author Ivano Bilenchi

#ifndef COWL_NARY_AXIOM_TYPE_H
#define COWL_NARY_AXIOM_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

typedef enum CowlNAryAxiomType {
    // Classes/properties
    CNAT_EQUIVALENT,
    CNAT_DISJOINT,

    // Individuals
    CNAT_SAME = CNAT_EQUIVALENT,
    CNAT_DIFFERENT = CNAT_DISJOINT
} CowlNAryAxiomType;

COWL_END_DECLS

#endif // COWL_NARY_AXIOM_TYPE_H
