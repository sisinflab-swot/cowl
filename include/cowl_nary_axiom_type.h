/// @author Ivano Bilenchi

#ifndef COWL_NARY_AXIOM_TYPE_H
#define COWL_NARY_AXIOM_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

typedef enum CowlNAryAxiomType {
    // Classes/properties
    COWL_NAT_EQUIV,
    COWL_NAT_DISJ,

    COWL_NAT_COUNT,
    COWL_NAT_FIRST = COWL_NAT_EQUIV,

    // Individuals
    CNAT_SAME = COWL_NAT_EQUIV,
    CNAT_DIFFERENT = COWL_NAT_DISJ
} CowlNAryAxiomType;

COWL_END_DECLS

#endif // COWL_NARY_AXIOM_TYPE_H
