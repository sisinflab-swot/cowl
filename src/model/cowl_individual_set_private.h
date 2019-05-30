/// @author Ivano Bilenchi

#ifndef COWL_INDIVIDUAL_SET_PRIVATE_H
#define COWL_INDIVIDUAL_SET_PRIVATE_H

#include "cowl_individual_set.h"

COWL_BEGIN_DECLS

cowl_hash_decl_mutable(CowlIndividualSet, CowlMutableIndividualSet);

bool cowl_individual_set_insert(CowlMutableIndividualSet *set, CowlIndividual *exp);

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_SET_H
