/**
 * Declares CowlDataOneOf and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_COWL_DATA_ONE_OF_H
#define COWL_COWL_DATA_ONE_OF_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_hash_decl(CowlLiteralSet);
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
 * @return Retained literal enumeration.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_PUBLIC
CowlDataOneOf* cowl_data_one_of_get(CowlLiteralSet *values);

/**
 * Retains the specified literal enumeration.
 *
 * @param range The literal enumeration.
 * @return Retained literal enumeration.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_PUBLIC
CowlDataOneOf* cowl_data_one_of_retain(CowlDataOneOf *range);

/**
 * Releases the specified literal enumeration.
 *
 * @param range The literal enumeration.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_PUBLIC
void cowl_data_one_of_release(CowlDataOneOf *range);

/**
 * Gets the values of the specified literal enumeration.
 *
 * @param range The literal enumeration.
 * @return The values.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_PUBLIC
CowlLiteralSet* cowl_data_one_of_get_values(CowlDataOneOf *range);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_PUBLIC
bool cowl_data_one_of_equals(CowlDataOneOf *lhs, CowlDataOneOf *rhs);

/**
 * Hash function.
 *
 * @param range The literal enumeration.
 * @return The hash value.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_PUBLIC
cowl_uint_t cowl_data_one_of_hash(CowlDataOneOf *range);

/**
 * Iterates over the signature of the specified literal enumeration.
 *
 * @param range The literal enumeration.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataOneOf
 */
COWL_PUBLIC
bool cowl_data_one_of_iterate_signature(CowlDataOneOf *range, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_COWL_DATA_ONE_OF_H
