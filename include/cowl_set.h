/**
 * Declares CowlSet and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SET_H
#define COWL_SET_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
UHASH_DECL_PI_SPEC(CowlObjectTable, void*, void*, COWL_PUBLIC)
cowl_struct_decl(CowlSet);
/// @endcond

/**
 * Set of CowlObject * elements.
 *
 * @struct CowlSet
 * @extends CowlObject
 */

/**
 * Returns a retained set.
 *
 * @param set Underlying raw set.
 * @return Retained set, or NULL on error.
 *
 * @note You must not use the raw set after passing it to this function.
 *
 * @public @memberof CowlSet
 */
COWL_PUBLIC
CowlSet* cowl_set_get(UHash(CowlObjectTable) *set);

/**
 * Returns a retained set with no elements.
 *
 * @return [CowlSet*] Retained set, or NULL on error.
 *
 * @public @related CowlSet
 */
#define cowl_set_get_empty() cowl_set_get(NULL)

/**
 * Retains the specified set.
 *
 * @param set The set.
 * @return Retained set.
 *
 * @public @memberof CowlSet
 */
COWL_INLINE
CowlSet* cowl_set_retain(CowlSet *set) {
    return (CowlSet *)cowl_retain(set);
}

/**
 * Releases the specified set.
 *
 * @param set The set.
 *
 * @public @memberof CowlSet
 */
COWL_PUBLIC
void cowl_set_release(CowlSet *set);

/**
 * Returns the underlying raw set.
 *
 * @param set The set.
 * @return Underlying raw set.
 *
 * @public @memberof CowlSet
 */
COWL_PUBLIC
UHash(CowlObjectTable) const* cowl_set_get_data(CowlSet *set);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlSet
 */
COWL_PUBLIC
bool cowl_set_equals(CowlSet *lhs, CowlSet *rhs);

/**
 * Hash function.
 *
 * @param set The set.
 * @return The hash value.
 *
 * @public @memberof CowlSet
 */
COWL_PUBLIC
ulib_uint cowl_set_hash(CowlSet *set);

/**
 * Iterates over the primitives referenced by the specified set.
 *
 * @param set The set.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlSet
 */
COWL_PUBLIC
bool cowl_set_iterate_primitives(CowlSet *set, CowlPrimitiveFlags flags, CowlIterator *iter);

/**
 * Returns the number of elements in the set.
 *
 * @param set [CowlSet *] The set.
 * @return [ulib_uint] Number of elements in the set.
 *
 * @public @related CowlSet
 */
#define cowl_set_count(set) uhash_count(CowlObjectTable, cowl_set_get_data(set))

/**
 * Returns one of the elements in the set.
 *
 * @param set [CowlSet *] The set.
 * @return [CowlObject *] One of the elements in the set.
 *
 * @public @related CowlSet
 */
#define cowl_set_get_any(set) uhset_get_any(CowlObjectTable, cowl_set_get_data(set), NULL)

/**
 * Iterates over the entries in the set.
 *
 * @param set [CowlSet *] The set.
 * @param obj [symbol] Name of the variable holding the current index, key and value.
 *
 * @note Since this data structure is a set, the 'val' field is always NULL.
 *
 * @public @related CowlSet
 */
#define cowl_set_foreach(set, obj) uhash_foreach(CowlObjectTable, cowl_set_get_data(set), obj)

COWL_END_DECLS

#endif // COWL_SET_H
