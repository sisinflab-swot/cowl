/// @author Ivano Bilenchi

#ifndef COWL_NAMED_IND_PRIVATE_H
#define COWL_NAMED_IND_PRIVATE_H

#include "cowl_named_ind.h"
#include "cowl_individual_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlNamedInd) {
    CowlIndividual super;
    CowlIRI *iri;
};

COWL_END_DECLS

#endif //COWL_NAMED_IND_PRIVATE_H
