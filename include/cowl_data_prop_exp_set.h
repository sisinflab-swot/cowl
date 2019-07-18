/**
 * Declares CowlDataPropExpSet and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_EXP_SET_H
#define COWL_DATA_PROP_EXP_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataPropExp);

UHASH_DECL_SPEC(CowlDataPropExpSet, CowlDataPropExp*, UHASH_VAL_IGNORE, COWL_PUBLIC)
cowl_hash_decl(CowlDataPropExpSet);
/// @endcond

/**
 * UHash set of CowlDataPropExp * elements.
 *
 * @struct CowlDataPropExpSet
 * @extends UHash
 */

/**
 * Deallocates the specified set, releasing its elements.
 *
 * @param set The set.
 *
 * @public @memberof CowlDataPropExpSet
 */
COWL_PUBLIC
void cowl_data_prop_exp_set_free(CowlDataPropExpSet *set);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataPropExpSet
 */
COWL_PUBLIC
bool cowl_data_prop_exp_set_equals(CowlDataPropExpSet *lhs, CowlDataPropExpSet *rhs);

/**
 * Hash function.
 *
 * @param set The set.
 * @return The hash value.
 *
 * @public @memberof CowlDataPropExpSet
 */
COWL_PUBLIC
cowl_uint_t cowl_data_prop_exp_set_hash(CowlDataPropExpSet *set);

/**
 * Iterates over the signature of the specified set.
 *
 * @param set The set.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataPropExpSet
 */
COWL_PUBLIC
bool cowl_data_prop_exp_set_iterate_signature(CowlDataPropExpSet *set, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_DATA_PROP_EXP_SET_H
