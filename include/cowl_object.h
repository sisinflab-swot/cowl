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

#include "cowl_std.h"
#include "cowl_impl.h"

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
void* cowl_retain(void *object);

/**
 * Releases the specified object.
 *
 * @param object The object.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
void cowl_release(void *object);

/**
 * Gets the type of the specified object.
 *
 * @param object The object.
 * @return The type.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
CowlObjectType cowl_get_type(void *object);

/**
 * Checks whether the specified object is an entity.
 *
 * @param object The object
 * @return True if the object is an entity, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_entity(void *object);

/**
 * Checks whether the specified object is an axiom.
 *
 * @param object The object
 * @return True if the object is an axiom, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_axiom(void *object);

/**
 * Checks whether the specified object is a class expression.
 *
 * @param object The object
 * @return True if the object is a class expression, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_cls_exp(void *object);

/**
 * Checks whether the specified object is an object property expression.
 *
 * @param object The object
 * @return True if the object is an object property expression, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_obj_prop_exp(void *object);

/**
 * Checks whether the specified object is a data property expression.
 *
 * @param object The object
 * @return True if the object is a data property expression, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_data_prop_exp(void *object);

/**
 * Checks whether the specified object is an individual.
 *
 * @param object The object
 * @return True if the object is an individual, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_individual(void *object);

/**
 * Checks whether the specified object is a data range.
 *
 * @param object The object
 * @return True if the object is a data range, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_data_range(void *object);

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
CowlString* cowl_to_string(void *object);

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
CowlString* cowl_to_debug_string(void *object);

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
bool cowl_equals(void *lhs, void *rhs);

/**
 * Hash function.
 *
 * @param object The object.
 * @return The hash value.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
ulib_uint cowl_hash(void *object);

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
bool cowl_iterate_primitives(void *object, CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJECT_H
