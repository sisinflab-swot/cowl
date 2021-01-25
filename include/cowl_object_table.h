/**
 * Declares CowlObjectTable and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_TABLE_H
#define COWL_OBJECT_TABLE_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
UHASH_DECL_SPEC(CowlObjectTable, void*, void*, COWL_PUBLIC)
cowl_hash_decl(CowlObjectTable);
/// @endcond

/**
 * UHash table of CowlObject * elements.
 *
 * @struct CowlObjectTable
 * @extends UHash
 */

/**
 * Deallocates the specified set, releasing its elements.
 *
 * @param set The set.
 *
 * @public @memberof CowlObjectTable
 */
COWL_PUBLIC
void cowl_object_set_free(CowlObjectTable *set);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjectTable
 */
COWL_PUBLIC
bool cowl_object_set_equals(CowlObjectTable *lhs, CowlObjectTable *rhs);

/**
 * Hash function.
 *
 * @param set The set.
 * @return The hash value.
 *
 * @public @memberof CowlObjectTable
 */
COWL_PUBLIC
cowl_uint cowl_object_set_hash(CowlObjectTable *set);

/**
 * Iterates over the primitives referenced by the specified set.
 *
 * @param set The set.
 * @param iter The iterator.
 * @param flags Iteration flags.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjectTable
 */
COWL_PUBLIC
bool cowl_object_set_iterate_primitives(CowlObjectTable *set, CowlIterator *iter,
                                        CowlPrimitiveFlags flags);

COWL_END_DECLS

#endif // COWL_OBJECT_TABLE_H
