/**
 * Declares CowlNAryData and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_DATA_H
#define COWL_NARY_DATA_H

#include "cowl_std.h"
#include "cowl_iterator.h"
#include "cowl_nary_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_hash_decl(CowlObjectTable);
cowl_struct_decl(CowlNAryData);
/// @endcond

/**
 * Represents [DataIntersectionOf] and [DataUnionOf] in the OWL 2 specification.
 *
 * [DataIntersectionOf]: https://www.w3.org/TR/owl2-syntax/#Intersection_of_Data_Ranges
 * [DataUnionOf]: https://www.w3.org/TR/owl2-syntax/#Union_of_Data_Ranges
 *
 * @struct CowlNAryData
 * @extends CowlDataRange
 */

/**
 * Returns a retained N-ary data range.
 *
 * @param type N-ary data range type.
 * @param operands The operands.
 * @return Retained N-ary data range, or NULL on error.
 *
 * @public @memberof CowlNAryData
 */
COWL_PUBLIC
CowlNAryData* cowl_nary_data_get(CowlNAryType type, CowlObjectTable *operands);

/**
 * Retains the specified N-ary data range.
 *
 * @param range The data range.
 * @return Retained N-ary data range.
 *
 * @public @memberof CowlNAryData
 */
COWL_PUBLIC
CowlNAryData* cowl_nary_data_retain(CowlNAryData *range);

/**
 * Releases the specified N-ary data range.
 *
 * @param range The data range.
 *
 * @public @memberof CowlNAryData
 */
COWL_PUBLIC
void cowl_nary_data_release(CowlNAryData *range);

/**
 * Gets the type of the specified N-ary data range.
 * @param range The data range.
 * @return The type.
 *
 * @public @memberof CowlNAryData
 */
COWL_PUBLIC
CowlNAryType cowl_nary_data_get_type(CowlNAryData *range);

/**
 * Gets the operands of the specified N-ary data range.
 *
 * @param range The data range.
 * @return The operands.
 *
 * @public @memberof CowlNAryData
 */
COWL_PUBLIC
CowlObjectTable* cowl_nary_data_get_operands(CowlNAryData *range);

/**
 * Returns the string representation of the specified N-ary data range.
 *
 * @param range The data range.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlNAryData
 */
COWL_PUBLIC
CowlString* cowl_nary_data_to_string(CowlNAryData *range);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNAryData
 */
COWL_PUBLIC
bool cowl_nary_data_equals(CowlNAryData *lhs, CowlNAryData *rhs);

/**
 * Hash function.
 *
 * @param range The data range.
 * @return The hash value.
 *
 * @public @memberof CowlNAryData
 */
COWL_PUBLIC
ulib_uint cowl_nary_data_hash(CowlNAryData *range);

/**
 * Iterates over the primitives referenced by the specified N-ary data range.
 *
 * @param range The data range.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlNAryData
 */
COWL_PUBLIC
bool cowl_nary_data_iterate_primitives(CowlNAryData *range, CowlPrimitiveFlags flags,
                                       CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_NARY_DATA_H
