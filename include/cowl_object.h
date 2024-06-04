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

COWL_BEGIN_DECLS

/**
 * The root pseudo-class.
 *
 * @struct CowlObject
 */
cowl_struct_decl(CowlObject);

/**
 * @defgroup CowlObject CowlObject API
 * @{
 */

/**
 * Retains the specified object.
 *
 * @param object The object.
 * @return Retained object.
 */
COWL_API
COWL_RETAINED
CowlAny *cowl_retain(CowlAny *object);

/**
 * Releases the specified object.
 *
 * @param object The object.
 */
COWL_API
void cowl_release(CowlAny *object);

/**
 * Gets the type of the specified object.
 *
 * @param object The object.
 * @return The type.
 */
COWL_API
COWL_PURE
CowlObjectType cowl_get_type(CowlAny *object);

/**
 * Checks whether the specified object is a primitive.
 *
 * @param object The object
 * @return True if the object is a primitive, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_is_primitive(CowlAny *object);

/**
 * Checks whether the specified object is an entity.
 *
 * @param object The object
 * @return True if the object is an entity, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_is_entity(CowlAny *object);

/**
 * Checks whether the specified object is an axiom.
 *
 * @param object The object
 * @return True if the object is an axiom, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_is_axiom(CowlAny *object);

/**
 * Checks whether the specified object is a class expression.
 *
 * @param object The object
 * @return True if the object is a class expression, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_is_cls_exp(CowlAny *object);

/**
 * Checks whether the specified object is an object property expression.
 *
 * @param object The object
 * @return True if the object is an object property expression, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_is_obj_prop_exp(CowlAny *object);

/**
 * Checks whether the specified object is a data property expression.
 *
 * @param object The object
 * @return True if the object is a data property expression, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_is_data_prop_exp(CowlAny *object);

/**
 * Checks whether the specified object is an individual.
 *
 * @param object The object
 * @return True if the object is an individual, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_is_individual(CowlAny *object);

/**
 * Checks whether the specified object is a data range.
 *
 * @param object The object
 * @return True if the object is a data range, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_is_data_range(CowlAny *object);

/**
 * Returns the IRI of the object, if it is identified by one.
 *
 * @param object The object.
 * @return IRI or NULL.
 */
COWL_API
COWL_PURE
CowlIRI *cowl_get_iri(CowlAny *object);

/**
 * Checks if the object has the specified IRI.
 *
 * @param object The object.
 * @param iri The IRI.
 * @return True if the object has the specified IRI, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_has_iri(CowlAny *object, CowlIRI *iri);

/**
 * Checks if the object has an IRI that matches the specified string.
 *
 * @param object The object.
 * @param iri_str IRI string.
 * @return True if the object has an IRI that matches the string, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_has_iri_string(CowlAny *object, UString iri_str);

/**
 * Returns the namespace of the object's IRI.
 *
 * @param object The object.
 * @return IRI namespace or NULL.
 */
COWL_API
COWL_PURE
CowlString *cowl_get_ns(CowlAny *object);

/**
 * Returns the remainder of the object's IRI.
 *
 * @param object The object.
 * @return IRI remainder or NULL.
 */
COWL_API
COWL_PURE
CowlString *cowl_get_rem(CowlAny *object);

/**
 * Returns the object's annotations.
 *
 * @param object The object.
 * @return The annotations, or NULL if the object has no annotations.
 */
COWL_API
COWL_PURE
CowlVector *cowl_get_annot(CowlAny *object);

/**
 * Returns the string representation of the specified object.
 *
 * @param object The object.
 * @return String representation, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlString *cowl_to_string(CowlAny *object);

/**
 * Returns the string representation of the specified object.
 *
 * @param object The object.
 * @return String representation, or @val{#ustring_null} on error.
 *
 * @destructor{ustring_deinit}
 */
COWL_API
UString cowl_to_ustring(CowlAny *object);

/**
 * Returns a debug string representation of the specified object.
 *
 * The debug string includes internal details such as the object's address,
 * type and reference count.
 *
 * @param object The object.
 * @return String representation, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlString *cowl_to_debug_string(CowlAny *object);

/**
 * Returns a debug string representation of the specified object.
 *
 * The debug string includes internal details such as the object's address,
 * type and reference count.
 *
 * @param object The object.
 * @return String representation, or @val{#ustring_null} on error.
 *
 * @destructor{ustring_deinit}
 */
COWL_API
UString cowl_to_debug_ustring(CowlAny *object);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_equals(CowlAny *lhs, CowlAny *rhs);

/**
 * Checks whether the object is reserved, i.e. if its IRI is in the reserved vocabulary.
 *
 * @param object The object.
 * @return True if the object is reserved, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_is_reserved(CowlAny *object);

/**
 * Hash function.
 *
 * @param object The object.
 * @return The hash value.
 */
COWL_API
COWL_PURE
ulib_uint cowl_hash(CowlAny *object);

/**
 * Checks whether the object references the specified primitive.
 *
 * @param object The object.
 * @param primitive The primitive.
 * @return True if the object references the primitive, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_has_primitive(CowlAny *object, CowlAnyPrimitive *primitive);

/**
 * Iterates over the primitives referenced by the specified object.
 *
 * @param object The object.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_API
bool cowl_iterate_primitives(CowlAny *object, CowlPrimitiveFlags flags, CowlIterator *iter);

/**
 * Releases the specified objects.
 *
 * @param ... The objects.
 * @alias void cowl_release_all(...);
 */
#define cowl_release_all(...)                                                                      \
    do {                                                                                           \
        CowlAny *p_cowl_release_all_##__LINE__[] = { __VA_ARGS__, NULL };                          \
        cowl_release_all_impl(p_cowl_release_all_##__LINE__);                                      \
    } while (0)

/// @}

COWL_END_DECLS

#endif // COWL_OBJECT_H
