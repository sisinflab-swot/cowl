/**
 * Declares CowlDataOneOf and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_COWL_DATA_ONE_OF_H
#define COWL_COWL_DATA_ONE_OF_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlDataOneOf);
/// @endcond

/**
 * Represents [DataOneOf] in the OWL 2 specification.
 *
 * [DataOneOf]: https://www.w3.org/TR/owl2-syntax/#Enumeration_of_Literals
 *
 * @struct CowlDataOneOf
 * @extends CowlDataRange
 */

/**
 * Returns a retained literal enumeration.
 *
 * @param values The enumeration values.
 * @return Retained literal enumeration, or NULL on error.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_INLINE
CowlDataOneOf* cowl_data_one_of_get(CowlVector *values) {
    return (CowlDataOneOf *)cowl_get_impl_1(COWL_OT_DR_DATA_ONE_OF, values);
}

/**
 * Retains the specified literal enumeration.
 *
 * @param range The literal enumeration.
 * @return Retained literal enumeration.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_INLINE
CowlDataOneOf* cowl_data_one_of_retain(CowlDataOneOf *range) {
    return (CowlDataOneOf *)cowl_retain(range);
}

/**
 * Releases the specified literal enumeration.
 *
 * @param range The literal enumeration.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_INLINE
void cowl_data_one_of_release(CowlDataOneOf *range) {
    cowl_release_impl(range);
}

/**
 * Gets the values of the specified literal enumeration.
 *
 * @param range The literal enumeration.
 * @return The values.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_INLINE
CowlVector* cowl_data_one_of_get_values(CowlDataOneOf *range) {
    return (CowlVector *)cowl_get_field(range, 0);
}

/**
 * Returns the string representation of the specified literal enumeration.
 *
 * @param range The literal enumeration.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_INLINE
CowlString* cowl_data_one_of_to_string(CowlDataOneOf *range) {
    return cowl_to_string_impl(range);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_INLINE
bool cowl_data_one_of_equals(CowlDataOneOf *lhs, CowlDataOneOf *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param range The literal enumeration.
 * @return The hash value.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_INLINE
ulib_uint cowl_data_one_of_hash(CowlDataOneOf *range) {
    return cowl_hash_impl(range);
}

/**
 * Iterates over the primitives referenced by the specified literal enumeration.
 *
 * @param range The literal enumeration.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_INLINE
bool cowl_data_one_of_iterate_primitives(CowlDataOneOf *range, CowlPrimitiveFlags flags,
                                         CowlIterator *iter) {
    return cowl_iterate_primitives_impl(range, flags, iter);
}

COWL_END_DECLS

#endif // COWL_COWL_DATA_ONE_OF_H
