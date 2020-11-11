/**
 * Declares CowlFacetRestrSet and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_FACET_RESTR_SET_H
#define COWL_FACET_RESTR_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlFacetRestr);

UHASH_DECL_SPEC(CowlFacetRestrSet, CowlFacetRestr*, UHASH_VAL_IGNORE, COWL_PUBLIC)
cowl_hash_decl(CowlFacetRestrSet);
/// @endcond

/**
 * UHash set of CowlFacetRestr * elements.
 *
 * @struct CowlFacetRestrSet
 * @extends UHash
 */

/**
 * Deallocates the specified set, releasing its elements.
 *
 * @param set The set.
 *
 * @public @memberof CowlFacetRestrSet
 */
COWL_PUBLIC
void cowl_facet_restr_set_free(CowlFacetRestrSet *set);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlFacetRestrSet
 */
COWL_PUBLIC
bool cowl_facet_restr_set_equals(CowlFacetRestrSet *lhs, CowlFacetRestrSet *rhs);

/**
 * Hash function.
 *
 * @param set The set.
 * @return The hash value.
 *
 * @public @memberof CowlFacetRestrSet
 */
COWL_PUBLIC
cowl_uint cowl_facet_restr_set_hash(CowlFacetRestrSet *set);

/**
 * Iterates over the primitives referenced by the specified set.
 *
 * @param set The set.
 * @param iter The iterator.
 * @param flags Iteration flags.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlFacetRestrSet
 */
COWL_PUBLIC
bool cowl_facet_restr_set_iterate_primitives(CowlFacetRestrSet *set, CowlIterator *iter,
                                             CowlPrimitiveFlags flags);

COWL_END_DECLS

#endif // COWL_FACET_RESTR_SET_H
