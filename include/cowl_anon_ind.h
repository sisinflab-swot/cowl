/**
 * Declares CowlAnonInd and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANON_IND_H
#define COWL_ANON_IND_H

#include "cowl_iterator.h"
#include "cowl_node_id.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlAnonInd);
/// @endcond

/**
 * Represents an [AnonymousIndividual] in the OWL 2 specification.
 *
 * [AnonymousIndividual]: https://www.w3.org/TR/owl2-syntax/#Anonymous_Individuals
 *
 * @struct CowlAnonInd
 * @extends CowlIndividual
 */

/**
 * Returns a retained anonymous individual.
 *
 * @return Retained anonymous individual, or NULL on error.
 *
 * @public @memberof CowlAnonInd
 */
COWL_PUBLIC
CowlAnonInd* cowl_anon_ind_get(void);

/**
 * Retains the specified anonymous individual.
 *
 * @param ind The anonymous individual.
 * @return Retained anonymous individual.
 *
 * @public @memberof CowlAnonInd
 */
COWL_PUBLIC
CowlAnonInd* cowl_anon_ind_retain(CowlAnonInd *ind);

/**
 * Releases the specified anonymous individual.
 *
 * @param ind The anonymous individual.
 *
 * @public @memberof CowlAnonInd
 */
COWL_PUBLIC
void cowl_anon_ind_release(CowlAnonInd *ind);

/**
 * Gets the node ID of the specified anonymous individual.
 *
 * @param ind The anonymous individual.
 * @return Node ID.
 *
 * @public @memberof CowlAnonInd
 */
COWL_PUBLIC
CowlNodeId cowl_anon_ind_get_id(CowlAnonInd *ind);

/**
 * Returns the string representation of the specified anonymous individual.
 *
 * @param ind The anonymous individual.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlAnonInd
 */
COWL_PUBLIC
CowlString* cowl_anon_ind_to_string(CowlAnonInd *ind);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnonInd
 */
COWL_PUBLIC
bool cowl_anon_ind_equals(CowlAnonInd *lhs, CowlAnonInd *rhs);

/**
 * Hash function.
 *
 * @param ind The anonymous individual.
 * @return The hash value.
 *
 * @public @memberof CowlAnonInd
 */
COWL_PUBLIC
ulib_uint cowl_anon_ind_hash(CowlAnonInd *ind);

/**
 * Iterates over the primitives referenced by this anonymous individual.
 *
 * @param ind The anonymous individual.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAnonInd
 */
COWL_PUBLIC
bool cowl_anon_ind_iterate_primitives(CowlAnonInd *ind, CowlPrimitiveFlags flags,
                                      CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_ANON_IND_H
