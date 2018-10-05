/// @author Ivano Bilenchi

#ifndef COWL_NAMED_INDIVIDUAL_PRIVATE_H
#define COWL_NAMED_INDIVIDUAL_PRIVATE_H

#include "cowl_named_individual.h"
#include "cowl_individual_private.h"

COWL_BEGIN_DECLS

typedef struct CowlNamedIndividual {
    CowlIndividual super;
    CowlIRI const *iri;
} CowlNamedIndividual;

COWL_END_DECLS

#endif // COWL_NAMED_INDIVIDUAL_PRIVATE_H
