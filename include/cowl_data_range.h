/**
 * Declares CowlDataRange and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_RANGE_H
#define COWL_DATA_RANGE_H

#include "cowl_data_range_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

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
 */

/**
 * Retains the specified data range.
 *
 * @param range The data range.
 * @return Retained data range.
 *
 * @public @memberof CowlDataRange
 */
COWL_PUBLIC
CowlDataRange* cowl_data_range_retain(CowlDataRange *range);

/**
 * Releases the specified data range.
 *
 * @param range The data range.
 *
 * @public @memberof CowlDataRange
 */
COWL_PUBLIC
void cowl_data_range_release(CowlDataRange *range);

/**
 * Gets the type of the specified data range.
 *
 * @param range The data range.
 * @return The type.
 *
 * @public @memberof CowlDataRange
 */
COWL_PUBLIC
CowlDataRangeType cowl_data_range_get_type(CowlDataRange *range);

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
COWL_PUBLIC
CowlString* cowl_data_range_to_string(CowlDataRange *range);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataRange
 */
COWL_PUBLIC
bool cowl_data_range_equals(CowlDataRange *lhs, CowlDataRange *rhs);

/**
 * Hash function.
 *
 * @param range The data range.
 * @return The hash value.
 *
 * @public @memberof CowlDataRange
 */
COWL_PUBLIC
cowl_uint cowl_data_range_hash(CowlDataRange *range);

/**
 * Iterates over the primitives referenced by the specified data range.
 *
 * @param range The data range.
 * @param iter The iterator.
 * @param flags Iteration flags.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataRange
 */
COWL_PUBLIC
bool cowl_data_range_iterate_primitives(CowlDataRange *range, CowlIterator *iter,
                                        CowlPrimitiveFlags flags);

COWL_END_DECLS

#endif // COWL_DATA_RANGE_H
