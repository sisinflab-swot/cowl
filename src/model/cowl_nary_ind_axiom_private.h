/// @author Ivano Bilenchi

#ifndef COWL_NARY_IND_AXIOM_PRIVATE_H
#define COWL_NARY_IND_AXIOM_PRIVATE_H

#include "cowl_nary_ind_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlNAryIndAxiom,
    CowlIndividualSet *operands;
);

COWL_END_DECLS

#endif // COWL_NARY_IND_AXIOM_PRIVATE_H
