/// @author Ivano Bilenchi

#ifndef COWL_INDIVIDUAL_SET_H
#define COWL_INDIVIDUAL_SET_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlIndividual const CowlIndividual;

UHASH_SET_DECL(CowlIndividualSet, CowlIndividual*)
typedef struct UHash(CowlIndividualSet) const CowlIndividualSet;
typedef struct UHash(CowlIndividualSet) CowlMutableIndividualSet;

bool cowl_individual_set_insert(CowlMutableIndividualSet *set, CowlIndividual *exp);
void cowl_individual_set_free(CowlIndividualSet *set);

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_SET_H
