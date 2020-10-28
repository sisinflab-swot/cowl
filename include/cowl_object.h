/**
 * Declares CowlObject and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_H
#define COWL_OBJECT_H

#include "cowl_std.h"
#include "cowl_object_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObject);
/// @endcond

/**
 * The root pseudo-class.
 *
 * @struct CowlObject
 */

/**
 * Gets the type of the specified object.
 *
 * @param object The object.
 * @return The type.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
CowlObjectType cowl_object_get_type(CowlObject *object);

COWL_END_DECLS

#endif // COWL_OBJECT_H
