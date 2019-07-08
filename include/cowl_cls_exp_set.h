/**
 * Declares CowlClsExpSet and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLS_EXP_SET_H
#define COWL_CLS_EXP_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);

UHASH_SET_DECL_SPEC(CowlClsExpSet, CowlClsExp*, COWL_PUBLIC)
cowl_hash_decl(CowlClsExpSet);
/// @endcond

/**
 * UHash set of CowlClsExp * elements.
 *
 * @struct CowlClsExpSet
 * @extends UHash
 */

/**
 * Deallocates the specified set, releasing its elements.
 *
 * @param set The set.
 *
 * @public @memberof CowlClsExpSet
 */
COWL_PUBLIC
void cowl_cls_exp_set_free(CowlClsExpSet *set);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlClsExpSet
 */
COWL_PUBLIC
bool cowl_cls_exp_set_equals(CowlClsExpSet *lhs, CowlClsExpSet *rhs);

/**
 * Hash function.
 *
 * @param set The set.
 * @return The hash value.
 *
 * @public @memberof CowlClsExpSet
 */
COWL_PUBLIC
cowl_uint_t cowl_cls_exp_set_hash(CowlClsExpSet *set);

/**
 * Iterates over the signature of the specified set.
 *
 * @param set The set.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlClsExpSet
 */
COWL_PUBLIC
bool cowl_cls_exp_set_iterate_signature(CowlClsExpSet *set, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_CLS_EXP_SET_H
