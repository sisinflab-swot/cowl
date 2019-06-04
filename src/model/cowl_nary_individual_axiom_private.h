/// @author Ivano Bilenchi

#ifndef COWL_NARY_INDIVIDUAL_AXIOM_PRIVATE_H
#define COWL_NARY_INDIVIDUAL_AXIOM_PRIVATE_H

#include "cowl_nary_individual_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlNAryIndividualAxiom) {
    CowlAxiom super;
    CowlIndividualSet *operands;
};

COWL_END_DECLS

#endif // COWL_NARY_INDIVIDUAL_AXIOM_PRIVATE_H
