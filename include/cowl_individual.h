/// @author Ivano Bilenchi

#ifndef COWL_INDIVIDUAL_H
#define COWL_INDIVIDUAL_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlEntity CowlEntity;
typedef struct CowlString CowlString;

typedef struct CowlIndividual CowlIndividual;

bool cowl_individual_is_named(CowlIndividual const *individual);
CowlEntity const* cowl_individual_named(CowlIndividual const *individual);
CowlString const* cowl_individual_anonymous_id(CowlIndividual const *individual);

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_H
