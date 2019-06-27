/// @author Ivano Bilenchi

#ifndef COWL_INDIVIDUAL_SET_H
#define COWL_INDIVIDUAL_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIndividual);

UHASH_SET_DECL(CowlIndividualSet, CowlIndividual*)
cowl_hash_decl(CowlIndividualSet);

void cowl_individual_set_free(CowlIndividualSet *set);

bool cowl_individual_set_equals(CowlIndividualSet *lhs, CowlIndividualSet *rhs);
cowl_uint_t cowl_individual_set_hash(CowlIndividualSet *set);

bool cowl_individual_set_iterate_signature(CowlIndividualSet *set, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_SET_H
