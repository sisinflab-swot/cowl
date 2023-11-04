/**
 * Declares CowlPrimitive and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PRIMITIVE_H
#define COWL_PRIMITIVE_H

#include "cowl_object.h"
#include "cowl_primitive_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlPrimitive);
/// @endcond

/**
 * Represents a primitive, a collective term for entities, anonymous individuals, and IRIs.
 *
 * @struct CowlPrimitive
 * @extends CowlObject
 */

/**
 * Gets the type of the primitive.
 *
 * @param primitive The primitive.
 * @return The type.
 *
 * @public @memberof CowlPrimitive
 */
COWL_API
CowlPrimitiveType cowl_primitive_get_type(CowlAnyPrimitive *primitive);

/**
 * Checks whether the primitive is an entity.
 *
 * @param primitive The primitive.
 * @return True if the primitive is an entity,
 *
 * @public @memberof CowlPrimitive
 */
COWL_API
bool cowl_primitive_is_entity(CowlAnyPrimitive *primitive);

COWL_END_DECLS

#endif // COWL_PRIMITIVE_H
