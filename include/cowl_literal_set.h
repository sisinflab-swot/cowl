/**
 * Declares CowlLiteralSet and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_LITERAL_SET_H
#define COWL_LITERAL_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlLiteral);

UHASH_DECL_SPEC(CowlLiteralSet, CowlLiteral*, UHASH_VAL_IGNORE, COWL_PUBLIC)
cowl_hash_decl(CowlLiteralSet);
/// @endcond

/**
 * UHash set of CowlLiteral * elements.
 *
 * @struct CowlLiteralSet
 * @extends UHash
 */

/**
 * Deallocates the specified set, releasing its elements.
 *
 * @param set The set.
 *
 * @public @memberof CowlLiteralSet
 */
COWL_PUBLIC
void cowl_literal_set_free(CowlLiteralSet *set);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlLiteralSet
 */
COWL_PUBLIC
bool cowl_literal_set_equals(CowlLiteralSet *lhs, CowlLiteralSet *rhs);

/**
 * Hash function.
 *
 * @param set The set.
 * @return The hash value.
 *
 * @public @memberof CowlLiteralSet
 */
COWL_PUBLIC
cowl_uint_t cowl_literal_set_hash(CowlLiteralSet *set);

/**
 * Iterates over the primitives referenced by the specified set.
 *
 * @param set The set.
 * @param iter The iterator.
 * @param flags Iteration flags.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlLiteralSet
 */
COWL_PUBLIC
bool cowl_literal_set_iterate_primitives(CowlLiteralSet *set, CowlIterator *iter,
                                         CowlPrimitiveFlags flags);

COWL_END_DECLS

#endif // COWL_LITERAL_SET_H
