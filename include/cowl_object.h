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

/**
 * Checks whether the specified object is an entity.
 *
 * @param object The object
 * @return True if the object is an entity, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_object_is_entity(CowlObject *object);

/**
 * Checks whether the specified object is an axiom.
 *
 * @param object The object
 * @return True if the object is an axiom, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_object_is_axiom(CowlObject *object);

/**
 * Checks whether the specified object is a class expression.
 *
 * @param object The object
 * @return True if the object is a class expression, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_object_is_cls_exp(CowlObject *object);

/**
 * Checks whether the specified object is an object property expression.
 *
 * @param object The object
 * @return True if the object is an object property expression, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_object_is_obj_prop_exp(CowlObject *object);

/**
 * Checks whether the specified object is a data property expression.
 *
 * @param object The object
 * @return True if the object is a data property expression, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_object_is_data_prop_exp(CowlObject *object);

/**
 * Checks whether the specified object is an individual.
 *
 * @param object The object
 * @return True if the object is an individual, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_object_is_individual(CowlObject *object);

/**
 * Checks whether the specified object is a data range.
 *
 * @param object The object
 * @return True if the object is a data range, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_object_is_data_range(CowlObject *object);

/**
 * Returns the string representation of the specified object.
 *
 * @param object The object.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
CowlString* cowl_object_to_string(CowlObject *object);

COWL_END_DECLS

#endif // COWL_OBJECT_H
