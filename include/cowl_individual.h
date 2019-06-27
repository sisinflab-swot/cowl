/// @author Ivano Bilenchi

#ifndef COWL_INDIVIDUAL_H
#define COWL_INDIVIDUAL_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIndividual);

CowlIndividual* cowl_individual_retain(CowlIndividual *ind);
void cowl_individual_release(CowlIndividual *ind);

bool cowl_individual_is_named(CowlIndividual *ind);

bool cowl_individual_equals(CowlIndividual *lhs, CowlIndividual *rhs);
cowl_uint_t cowl_individual_hash(CowlIndividual *ind);

bool cowl_individual_iterate_signature(CowlIndividual *ind, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_H
