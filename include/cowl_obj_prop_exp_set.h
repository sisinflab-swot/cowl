/**
 * Declares CowlObjPropExpSet and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_EXP_SET_H
#define COWL_OBJ_PROP_EXP_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);

UHASH_DECL_SPEC(CowlObjPropExpSet, CowlObjPropExp*, UHASH_VAL_IGNORE, COWL_PUBLIC)
cowl_hash_decl(CowlObjPropExpSet);
/// @endcond

/**
 * UHash set of CowlObjPropExp * elements.
 *
 * @struct CowlObjPropExpSet
 * @extends UHash
 */

/**
 * Deallocates the specified set, releasing its elements.
 *
 * @param set The set.
 *
 * @public @memberof CowlObjPropExpSet
 */
COWL_PUBLIC
void cowl_obj_prop_exp_set_free(CowlObjPropExpSet *set);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjPropExpSet
 */
COWL_PUBLIC
bool cowl_obj_prop_exp_set_equals(CowlObjPropExpSet *lhs, CowlObjPropExpSet *rhs);

/**
 * Hash function.
 *
 * @param set The set.
 * @return The hash value.
 *
 * @public @memberof CowlObjPropExpSet
 */
COWL_PUBLIC
cowl_uint cowl_obj_prop_exp_set_hash(CowlObjPropExpSet *set);

/**
 * Iterates over the primitives referenced by the specified set.
 *
 * @param set The set.
 * @param iter The iterator.
 * @param flags Iteration flags.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjPropExpSet
 */
COWL_PUBLIC
bool cowl_obj_prop_exp_set_iterate_primitives(CowlObjPropExpSet *set, CowlIterator *iter,
                                              CowlPrimitiveFlags flags);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_SET_H
