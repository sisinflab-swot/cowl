/**
 * Defines #CowlNodeID and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
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
typedef cowl_uint_t CowlNodeID;

/**
 * Returns an unique node ID.
 *
 * @return Unique node ID.
 *
 * @public @related CowlAnonInd
 */
COWL_PUBLIC
CowlNodeID cowl_node_id_get_unique(void);

/**
 * Returns the string representation of the specified node ID.
 *
 * @param id The node ID.
 * @return String representation.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @related CowlAnonInd
 */
COWL_PUBLIC
CowlString* cowl_node_id_to_string(CowlNodeID id);

/**
 * Equality function.
 *
 * @param LHS [CowlNodeID] LHS of the equality relation.
 * @param RHS [CowlNodeID] RHS of the equality relation.
 * @return [bool] True if the equality relation holds, false otherwise.
 *
 * @public @related CowlAnonInd
 */
#define cowl_node_id_equals(LHS, RHS) ((LHS) == (RHS))

/**
 * Hash function.
 *
 * @param ID [CowlNodeID] The node ID.
 * @return [cowl_uint_t] The hash value.
 *
 * @public @related CowlAnonInd
 */
#define cowl_node_id_hash(ID) (ID)

COWL_END_DECLS

#endif // COWL_NODE_ID_H
