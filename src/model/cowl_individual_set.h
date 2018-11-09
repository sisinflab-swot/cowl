/// @author Ivano Bilenchi

#ifndef COWL_INDIVIDUAL_SET_H
#define COWL_INDIVIDUAL_SET_H

#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef struct CowlIndividual const CowlIndividual;

KHASH_SET_UTILS_DECL(CowlIndividualSet, CowlIndividual*);
typedef khash_struct(CowlIndividualSet) const CowlIndividualSet;
typedef khash_struct(CowlIndividualSet) CowlMutableIndividualSet;

bool cowl_individual_set_insert(CowlMutableIndividualSet *set, CowlIndividual *exp);
void cowl_individual_set_free(CowlIndividualSet *set);

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_SET_H
