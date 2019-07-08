/**
 * Declares CowlInvObjProp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INV_OBJ_PROP_H
#define COWL_INV_OBJ_PROP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjProp);
cowl_struct_decl(CowlInvObjProp);
/// @endcond

/**
 * Represents an [InverseObjectProperty] in the OWL 2 specification.
 *
 * [InverseObjectProperty]: https://www.w3.org/TR/owl2-syntax/#Inverse_Object_Properties
 *
 * @struct CowlInvObjProp
 * @extends CowlObjPropExp
 */

/**
 * Returns a retained inverse object property.
 *
 * @param prop The object property of which the expression is the inverse of.
 * @return Retained inverse object property.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_PUBLIC
CowlInvObjProp* cowl_inv_obj_prop_get(CowlObjProp *prop);

/**
 * Retains the specified inverse object property.
 *
 * @param inv The inverse object property.
 * @return Retained inverse object property.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_PUBLIC
CowlInvObjProp* cowl_inv_obj_prop_retain(CowlInvObjProp *inv);

/**
 * Releases the specified inverse object property.
 *
 * @param inv The inverse object property.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_PUBLIC
void cowl_inv_obj_prop_release(CowlInvObjProp *inv);

/**
 * Gets the property of which the expression is the inverse of.
 *
 * @param inv The inverse object property.
 * @return The property.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_PUBLIC
CowlObjProp* cowl_inv_obj_prop_get_prop(CowlInvObjProp *inv);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_PUBLIC
bool cowl_inv_obj_prop_equals(CowlInvObjProp *lhs, CowlInvObjProp *rhs);

/**
 * Hash function.
 *
 * @param inv The inverse object property.
 * @return The hash value.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_PUBLIC
cowl_uint_t cowl_inv_obj_prop_hash(CowlInvObjProp *inv);

/**
 * Iterates over the signature of the specified inverse object property.
 *
 * @param inv The inverse object property.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_PUBLIC
bool cowl_inv_obj_prop_iterate_signature(CowlInvObjProp *inv, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_INV_OBJ_PROP_H
