/**
 * Declares CowlObject and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_H
#define COWL_OBJECT_H

#include "cowl_impl.h"
#include "cowl_std.h"

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
CowlAny *cowl_retain(CowlAny *object);

/**
 * Releases the specified object.
 *
 * @param object The object.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
void cowl_release(CowlAny *object);

/**
 * Gets the type of the specified object.
 *
 * @param object The object.
 * @return The type.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
CowlObjectType cowl_get_type(CowlAny *object);

/**
 * Checks whether the specified object is an entity.
 *
 * @param object The object
 * @return True if the object is an entity, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_entity(CowlAny *object);

/**
 * Checks whether the specified object is an axiom.
 *
 * @param object The object
 * @return True if the object is an axiom, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_axiom(CowlAny *object);

/**
 * Checks whether the specified object is a class expression.
 *
 * @param object The object
 * @return True if the object is a class expression, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_cls_exp(CowlAny *object);

/**
 * Checks whether the specified object is an object property expression.
 *
 * @param object The object
 * @return True if the object is an object property expression, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_obj_prop_exp(CowlAny *object);

/**
 * Checks whether the specified object is a data property expression.
 *
 * @param object The object
 * @return True if the object is a data property expression, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_data_prop_exp(CowlAny *object);

/**
 * Checks whether the specified object is an individual.
 *
 * @param object The object
 * @return True if the object is an individual, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_individual(CowlAny *object);

/**
 * Checks whether the specified object is a data range.
 *
 * @param object The object
 * @return True if the object is a data range, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_is_data_range(CowlAny *object);

/**
 * If the object is an entity, returns its IRI, otherwise returns NULL.
 *
 * @param object The object.
 * @return IRI or NULL.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
CowlIRI *cowl_get_iri(CowlAny *object);

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
CowlString *cowl_to_string(CowlAny *object);

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
CowlString *cowl_to_debug_string(CowlAny *object);

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
bool cowl_equals(CowlAny *lhs, CowlAny *rhs);

/**
 * Checks if the object is an entity and its IRI matches the specified string.
 *
 * @param object The object.
 * @param iri_str IRI string.
 * @return True if the object is an entity and its IRI matches the string, false otherwise.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
bool cowl_equals_iri_string(CowlAny *object, UString iri_str);

/**
 * Hash function.
 *
 * @param object The object.
 * @return The hash value.
 *
 * @public @memberof CowlObject
 */
COWL_PUBLIC
ulib_uint cowl_hash(CowlAny *object);

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
bool cowl_iterate_primitives(CowlAny *object, CowlPrimitiveFlags flags, CowlIterator *iter);

/**
 * Releases the specified objects.
 *
 * @param ... The objects.
 *
 * @public @related CowlObject
 */
#define cowl_release_all(...)                                                                      \
    do {                                                                                           \
        CowlAny *p_cowl_release_all_##__LINE__[] = { __VA_ARGS__, NULL };                          \
        cowl_release_all_impl(p_cowl_release_all_##__LINE__);                                      \
    } while (0)

COWL_END_DECLS

#endif // COWL_OBJECT_H
