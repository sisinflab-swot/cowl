/// @author Ivano Bilenchi

#ifndef COWL_INDIVIDUAL_PRIVATE_H
#define COWL_INDIVIDUAL_PRIVATE_H

#include "cowl_individual.h"

COWL_BEGIN_DECLS

typedef struct CowlIndividual {
    bool is_named;

    union {
        CowlEntity const *named;
        CowlString const *anonymous_id;
    };
} CowlIndividual;

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_PRIVATE_H
