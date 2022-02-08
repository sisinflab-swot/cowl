/**
 * Declares CowlObjProp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_H
#define COWL_OBJ_PROP_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlObjProp);
/// @endcond

/**
 * Represents an [ObjectProperty] in the OWL 2 specification.
 *
 * [ObjectProperty]: https://www.w3.org/TR/owl2-syntax/#Object_Properties
 *
 * @struct CowlObjProp
 * @extends CowlObjPropExp
 */

/**
 * Returns a retained object property.
 *
 * @param iri IRI of the object property.
 * @return Retained object property, or NULL on error.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
CowlObjProp* cowl_obj_prop_get(CowlIRI *iri);

/**
 * Returns a retained object property given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Retained object property, or NULL on error.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
CowlObjProp* cowl_obj_prop_from_string(UString string);

/**
 * Returns a retained object property given the static string representation of its IRI.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlObjProp *] Retained object property, or NULL on error.
 *
 * @public @related CowlObjProp
 */
#define cowl_obj_prop_from_static(CSTR) cowl_obj_prop_from_string(ustring_literal(CSTR))

/**
 * Retains the specified object property.
 *
 * @param prop The object property.
 * @return Retained object property.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
CowlObjProp* cowl_obj_prop_retain(CowlObjProp *prop);

/**
 * Releases the specified object property.
 *
 * @param prop The object property.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
void cowl_obj_prop_release(CowlObjProp *prop);

/**
 * Gets the IRI of the specified object property.
 *
 * @param prop The object property.
 * @return The IRI.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
CowlIRI* cowl_obj_prop_get_iri(CowlObjProp *prop);

/**
 * Returns the string representation of the specified object property.
 *
 * @param prop The object property.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
CowlString* cowl_obj_prop_to_string(CowlObjProp *prop);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
bool cowl_obj_prop_equals(CowlObjProp *lhs, CowlObjProp *rhs);

/**
 * Hash function.
 *
 * @param prop The property.
 * @return The hash value.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
ulib_uint cowl_obj_prop_hash(CowlObjProp *prop);

/**
 * Iterates over this object property.
 *
 * @param prop The object property.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
bool cowl_obj_prop_iterate_primitives(CowlObjProp *prop, CowlPrimitiveFlags flags,
                                      CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_H
