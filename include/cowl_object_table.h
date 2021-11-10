/**
 * Declares CowlObjectTable and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
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
UHASH_DECL_PI_SPEC(CowlObjectTable, void*, void*, COWL_PUBLIC)
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
ulib_uint cowl_object_set_hash(CowlObjectTable *set);

/**
 * Inserts an element into the specified set and retains it.
 *
 * @param set The set.
 * @param object The object to insert.
 * @return Return code.
 *
 * @note The object is only retained if it is actually inserted into the set, which may not
 *       happen if an equal object is already present.
 *
 * @public @memberof CowlObjectTable
 */
COWL_PUBLIC
cowl_ret cowl_object_set_insert(UHash(CowlObjectTable) *set, CowlObject *object);

/**
 * Iterates over the primitives referenced by the specified set.
 *
 * @param set The set.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjectTable
 */
COWL_PUBLIC
bool cowl_object_set_iterate_primitives(CowlObjectTable *set, CowlPrimitiveFlags flags,
                                        CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJECT_TABLE_H
