/**
 * Declares CowlDataCompl and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_COMPL_H
#define COWL_DATA_COMPL_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDataCompl);
/// @endcond

/**
 * Represents [DataComplementOf] the OWL 2 specification.
 *
 * [DataComplementOf]: https://www.w3.org/TR/owl2-syntax/#Complement_of_Data_Ranges
 *
 * @struct CowlDataCompl
 * @extends CowlDataRange
 */

/**
 * Returns a retained data range complement.
 *
 * @param operand The data range which this data range is a complement of.
 * @return Retained data range complement, or NULL on error.
 *
 * @public @memberof CowlDataCompl
 */
COWL_PUBLIC
CowlDataCompl* cowl_data_compl_get(CowlDataRange *operand);

/**
 * Retains the specified data range complement.
 *
 * @param range The data range complement.
 * @return Retained data range complement.
 *
 * @public @memberof CowlDataCompl
 */
COWL_PUBLIC
CowlDataCompl* cowl_data_compl_retain(CowlDataCompl *range);

/**
 * Releases the specified data range complement.
 *
 * @param range The data range complement.
 *
 * @public @memberof CowlDataCompl
 */
COWL_PUBLIC
void cowl_data_compl_release(CowlDataCompl *range);

/**
 * Gets the data range which this data range is a complement of.
 *
 * @param range The data range complement.
 * @return The operand.
 *
 * @public @memberof CowlDataCompl
 */
COWL_PUBLIC
CowlDataRange* cowl_data_compl_get_operand(CowlDataCompl *range);

/**
 * Returns the string representation of the specified data range complement.
 *
 * @param range The data range complement.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDataCompl
 */
COWL_PUBLIC
CowlString* cowl_data_compl_to_string(CowlDataCompl *range);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataCompl
 */
COWL_PUBLIC
bool cowl_data_compl_equals(CowlDataCompl *lhs, CowlDataCompl *rhs);

/**
 * Hash function.
 *
 * @param range The data range complement.
 * @return The hash value.
 *
 * @public @memberof CowlDataCompl
 */
COWL_PUBLIC
ulib_uint cowl_data_compl_hash(CowlDataCompl *range);

/**
 * Iterates over the primitives referenced by the specified data range complement.
 *
 * @param range The data range complement.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataCompl
 */
COWL_PUBLIC
bool cowl_data_compl_iterate_primitives(CowlDataCompl *range, CowlPrimitiveFlags flags,
                                        CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_DATA_COMPL_H
