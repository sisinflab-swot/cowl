/**
 * Declares CowlObject and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_H
#define COWL_OBJECT_H

#include "cowl_iterator.h"
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
 * Retains the specified object.
 *
 * @param object The object.
 * @return Retained object.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
CowlObject* cowl_object_retain(CowlObject *object);

/**
 * Releases the specified object.
 *
 * @param object The object.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
void cowl_object_release(CowlObject *object);

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

/**
 * Returns a debug string representation of the specified object.
 *
 * The debug string includes internal details such as the object's address,
 * type and reference count.
 *
 * @param object The object.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
CowlString* cowl_object_to_debug_string(CowlObject *object);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_object_equals(CowlObject *lhs, CowlObject *rhs);

/**
 * Hash function.
 *
 * @param object The object.
 * @return The hash value.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
ulib_uint cowl_object_hash(CowlObject *object);

/**
 * Iterates over the primitives referenced by the specified object.
 *
 * @param object The object.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_object_iterate_primitives(CowlObject *object, CowlPrimitiveFlags flags,
                                    CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJECT_H
