/// @author Ivano Bilenchi

#ifndef COWL_INDIVIDUAL_H
#define COWL_INDIVIDUAL_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlIndividual CowlIndividual;

bool cowl_individual_is_named(CowlIndividual const *ind);

bool cowl_individual_equals(CowlIndividual const *lhs, CowlIndividual const *rhs);
uint32_t cowl_individual_hash(CowlIndividual const *ind);

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_H
