/**
 * Declares CowlDataRange and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_RANGE_H
#define COWL_DATA_RANGE_H

#include "cowl_data_range_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlDataRange);
/// @endcond

/**
 * Represents a [DataRange] in the OWL 2 specification.
 *
 * [DataRange]: https://www.w3.org/TR/owl2-syntax/#Data_Ranges
 *
 * @struct CowlDataRange
 * @extends CowlObject
 */

/**
 * Retains the specified data range.
 *
 * @param range The data range.
 * @return Retained data range.
 *
 * @public @memberof CowlDataRange
 */
COWL_INLINE
CowlAnyDataRange *cowl_data_range_retain(CowlAnyDataRange *range) {
    return cowl_retain(range);
}

/**
 * Releases the specified data range.
 *
 * @param range The data range.
 *
 * @public @memberof CowlDataRange
 */
COWL_INLINE
void cowl_data_range_release(CowlAnyDataRange *range) {
    cowl_release(range);
}

/**
 * Gets the type of the specified data range.
 *
 * @param range The data range.
 * @return The type.
 *
 * @public @memberof CowlDataRange
 */
COWL_INLINE
CowlDataRangeType cowl_data_range_get_type(CowlAnyDataRange *range) {
    return (CowlDataRangeType)(cowl_get_type(range) - COWL_OT_DR_DATATYPE);
}

/**
 * Returns the string representation of the specified data range.
 *
 * @param range The data range.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDataRange
 */
COWL_INLINE
CowlString *cowl_data_range_to_string(CowlAnyDataRange *range) {
    return cowl_to_string(range);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataRange
 */
COWL_INLINE
bool cowl_data_range_equals(CowlAnyDataRange *lhs, CowlAnyDataRange *rhs) {
    return cowl_equals(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param range The data range.
 * @return The hash value.
 *
 * @public @memberof CowlDataRange
 */
COWL_INLINE
ulib_uint cowl_data_range_hash(CowlAnyDataRange *range) {
    return cowl_hash(range);
}

/**
 * Iterates over the primitives referenced by the specified data range.
 *
 * @param range The data range.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataRange
 */
COWL_INLINE
bool cowl_data_range_iterate_primitives(CowlAnyDataRange *range, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return cowl_iterate_primitives(range, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DATA_RANGE_H
