/**
 * Declares CowlIndividual and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INDIVIDUAL_H
#define COWL_INDIVIDUAL_H

#include "cowl_object.h"

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
 * @extends CowlPrimitive
 */

/**
 * Retains the specified individual.
 *
 * @param ind The individual.
 * @return Retained individual.
 *
 * @public @memberof CowlIndividual
 */
COWL_INLINE
CowlAnyIndividual* cowl_individual_retain(CowlAnyIndividual *ind) {
    return cowl_retain(ind);
}

/**
 * Releases the specified individual.
 * @param ind The individual.
 *
 * @public @memberof CowlIndividual
 */
COWL_INLINE
void cowl_individual_release(CowlAnyIndividual *ind) {
    cowl_release(ind);
}

/**
 * Returns true if the underlying individual is named.
 *
 * @param ind The individual.
 * @return True if the underlying individual is named, false otherwise.
 *
 * @public @memberof CowlIndividual
 */
COWL_INLINE
bool cowl_individual_is_named(CowlAnyIndividual *ind) {
    return cowl_get_type(ind) == COWL_OT_I_NAMED;
}

/**
 * Returns the string representation of the specified individual.
 *
 * @param ind The individual.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlIndividual
 */
COWL_INLINE
CowlString* cowl_individual_to_string(CowlAnyIndividual *ind) {
    return cowl_to_string(ind);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlIndividual
 */
COWL_INLINE
bool cowl_individual_equals(CowlAnyIndividual *lhs, CowlAnyIndividual *rhs) {
    return lhs == rhs;
}

/**
 * Hash function.
 *
 * @param ind The individual.
 * @return The hash value.
 *
 * @public @memberof CowlIndividual
 */
COWL_INLINE
ulib_uint cowl_individual_hash(CowlAnyIndividual *ind) {
    return uhash_ptr_hash(ind);
}

/**
 * Iterates over this individual.
 *
 * @param ind The individual.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlIndividual
 */
COWL_INLINE
bool cowl_individual_iterate_primitives(CowlAnyIndividual *ind, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return cowl_iterate_primitives(ind, flags, iter);
}

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_H
