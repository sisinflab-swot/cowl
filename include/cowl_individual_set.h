/**
 * Declares CowlIndividualSet and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INDIVIDUAL_SET_H
#define COWL_INDIVIDUAL_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIndividual);

UHASH_DECL_SPEC(CowlIndividualSet, CowlIndividual*, UHASH_VAL_IGNORE, COWL_PUBLIC)
cowl_hash_decl(CowlIndividualSet);
/// @endcond

/**
 * UHash set of CowlIndividual * elements.
 *
 * @struct CowlIndividualSet
 * @extends UHash
 */

/**
 * Deallocates the specified set, releasing its elements.
 *
 * @param set The set.
 *
 * @public @memberof CowlIndividualSet
 */
COWL_PUBLIC
void cowl_individual_set_free(CowlIndividualSet *set);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlIndividualSet
 */
COWL_PUBLIC
bool cowl_individual_set_equals(CowlIndividualSet *lhs, CowlIndividualSet *rhs);

/**
 * Hash function.
 *
 * @param set The set.
 * @return The hash value.
 *
 * @public @memberof CowlIndividualSet
 */
COWL_PUBLIC
cowl_uint_t cowl_individual_set_hash(CowlIndividualSet *set);

/**
 * Iterates over the objects referenced by the specified set.
 *
 * @param set The set.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlIndividualSet
 */
COWL_PUBLIC
bool cowl_individual_set_iterate(CowlIndividualSet *set, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_SET_H
