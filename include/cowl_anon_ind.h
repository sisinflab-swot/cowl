/**
 * Declares CowlAnonInd and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANON_IND_H
#define COWL_ANON_IND_H

#include "cowl_primitive.h"

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
 * @extends CowlPrimitive
 * @extends CowlAnnotValue
 */

/**
 * Returns a retained anonymous individual.
 *
 * @param id Anonymous individual identifier.
 * @return Retained anonymous individual, or NULL on error.
 *
 * @note By passing NULL as the identifier, a new identifier is randomly generated.
 *
 * @public @memberof CowlAnonInd
 */
COWL_PUBLIC
CowlAnonInd *cowl_anon_ind(CowlString *id);

/**
 * Returns a retained anonymous individual.
 *
 * @param string Anonymous individual identifier.
 * @return Retained anonymous individual, or NULL on error.
 *
 * @public @memberof CowlAnonInd
 */
COWL_PUBLIC
CowlAnonInd *cowl_anon_ind_from_string(UString string);

/**
 * Returns a retained anonymous individual given the static string representation of its identifier.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlAnonInd *] Retained anonymous individual, or NULL on error.
 *
 * @public @related CowlAnonInd
 */
#define cowl_anon_ind_from_static(CSTR) cowl_anon_ind_from_string(ustring_literal(CSTR))

/**
 * Gets the node ID of the specified anonymous individual.
 *
 * @param ind The anonymous individual.
 * @return Node ID.
 *
 * @public @memberof CowlAnonInd
 */
COWL_PUBLIC
CowlString *cowl_anon_ind_get_id(CowlAnonInd *ind);

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
COWL_INLINE
CowlString *cowl_anon_ind_to_string(CowlAnonInd *ind) {
    return cowl_primitive_to_string((CowlPrimitive *)ind);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnonInd
 */
COWL_INLINE
bool cowl_anon_ind_equals(CowlAnonInd *lhs, CowlAnonInd *rhs) {
    return lhs == rhs;
}

/**
 * Hash function.
 *
 * @param ind The anonymous individual.
 * @return The hash value.
 *
 * @public @memberof CowlAnonInd
 */
COWL_INLINE
ulib_uint cowl_anon_ind_hash(CowlAnonInd *ind) {
    return uhash_ptr_hash(ind);
}

/**
 * Iterates over this anonymous individual.
 *
 * @param ind The anonymous individual.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAnonInd
 */
COWL_INLINE
bool cowl_anon_ind_iterate_primitives(CowlAnonInd *ind, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    return cowl_iterate_primitives(ind, flags, iter);
}

COWL_END_DECLS

#endif // COWL_ANON_IND_H
