/**
 * Declares CowlIndividual and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INDIVIDUAL_H
#define COWL_INDIVIDUAL_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIndividual);
/// @endcond

/**
 * Represents an [Individual] in the OWL 2 specification.
 *
 * [Individual]: https://www.w3.org/TR/owl2-syntax/#Individuals
 *
 * @struct CowlIndividual
 */

/**
 * Retains the specified individual.
 *
 * @param ind The individual.
 * @return Retained individual.
 *
 * @public @memberof CowlIndividual
 */
COWL_PUBLIC
CowlIndividual* cowl_individual_retain(CowlIndividual *ind);

/**
 * Releases the specified individual.
 * @param ind The individual.
 *
 * @public @memberof CowlIndividual
 */
COWL_PUBLIC
void cowl_individual_release(CowlIndividual *ind);

/**
 * Returns true if the underlying individual is named.
 *
 * @param ind The individual.
 * @return True if the underlying individual is named, false otherwise.
 *
 * @public @memberof CowlIndividual
 */
COWL_PUBLIC
bool cowl_individual_is_named(CowlIndividual *ind);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlIndividual
 */
COWL_PUBLIC
bool cowl_individual_equals(CowlIndividual *lhs, CowlIndividual *rhs);

/**
 * Hash function.
 *
 * @param ind The individual.
 * @return The hash value.
 *
 * @public @memberof CowlIndividual
 */
COWL_PUBLIC
cowl_uint_t cowl_individual_hash(CowlIndividual *ind);

/**
 * Iterates over the signature of the specified individual.
 *
 * @param ind The individual.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlIndividual
 */
COWL_PUBLIC
bool cowl_individual_iterate_signature(CowlIndividual *ind, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_H
