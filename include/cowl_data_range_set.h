/**
 * Declares CowlDataRangeSet and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_RANGE_SET_H
#define COWL_DATA_RANGE_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);

UHASH_DECL_SPEC(CowlDataRangeSet, CowlDataRange*, UHASH_VAL_IGNORE, COWL_PUBLIC)
cowl_hash_decl(CowlDataRangeSet);
/// @endcond

/**
 * UHash set of CowlDataRange * elements.
 *
 * @struct CowlDataRangeSet
 * @extends UHash
 */

/**
 * Deallocates the specified set, releasing its elements.
 *
 * @param set The set.
 *
 * @public @memberof CowlDataRangeSet
 */
COWL_PUBLIC
void cowl_data_range_set_free(CowlDataRangeSet *set);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataRangeSet
 */
COWL_PUBLIC
bool cowl_data_range_set_equals(CowlDataRangeSet *lhs, CowlDataRangeSet *rhs);

/**
 * Hash function.
 *
 * @param set The set.
 * @return The hash value.
 *
 * @public @memberof CowlDataRangeSet
 */
COWL_PUBLIC
cowl_uint cowl_data_range_set_hash(CowlDataRangeSet *set);

/**
 * Iterates over the primitives referenced by the specified set.
 *
 * @param set The set.
 * @param iter The iterator.
 * @param flags Iteration flags.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataRangeSet
 */
COWL_PUBLIC
bool cowl_data_range_set_iterate_primitives(CowlDataRangeSet *set, CowlIterator *iter,
                                            CowlPrimitiveFlags flags);

COWL_END_DECLS

#endif // COWL_DATA_RANGE_SET_H
