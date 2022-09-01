/**
 * Defines CowlNodeId and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NODE_ID_H
#define COWL_NODE_ID_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
/// @endcond

/**
 * Represents the identifier of a CowlAnonInd.
 *
 * @public @memberof CowlAnonInd
 */
typedef uintptr_t CowlNodeId;

/**
 * Null node ID.
 *
 * @public @related CowlAnonInd
 */
#define COWL_NODE_ID_NULL ((CowlNodeId)NULL)

/**
 * Equality function.
 *
 * @param LHS [CowlNodeId] LHS of the equality relation.
 * @param RHS [CowlNodeId] RHS of the equality relation.
 * @return [bool] True if the equality relation holds, false otherwise.
 *
 * @public @related CowlAnonInd
 */
#define cowl_node_id_equals(LHS, RHS) ((LHS) == (RHS))

/**
 * Hash function.
 *
 * @param ID [CowlNodeId] The node ID.
 * @return [ulib_uint] The hash value.
 *
 * @public @related CowlAnonInd
 */
#define cowl_node_id_hash(ID) (uhash_ptr_hash(ID))

COWL_END_DECLS

#endif // COWL_NODE_ID_H
