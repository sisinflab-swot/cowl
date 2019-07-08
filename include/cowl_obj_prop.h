/**
 * Declares CowlObjProp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
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
 * @return Retained object property.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
CowlObjProp* cowl_obj_prop_get(CowlIRI *iri);

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
cowl_uint_t cowl_obj_prop_hash(CowlObjProp *prop);

/**
 * Iterates over the signature of the specified object property.
 *
 * @param prop The object property.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
bool cowl_obj_prop_iterate_signature(CowlObjProp *prop, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_H
