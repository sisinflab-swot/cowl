/**
 * Declares CowlDataProp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_H
#define COWL_DATA_PROP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlDataProp);
/// @endcond

/**
 * Represents a [DataProperty] in the OWL 2 specification.
 *
 * [DataProperty]: https://www.w3.org/TR/owl2-syntax/#Data_Properties
 *
 * @struct CowlDataProp
 * @extends CowlDataPropExp
 */

/**
 * Returns a retained data property.
 *
 * @param iri IRI of the data property.
 * @return Retained data property, or NULL on error.
 *
 * @public @memberof CowlDataProp
 */
COWL_PUBLIC
CowlDataProp* cowl_data_prop_get(CowlIRI *iri);

/**
 * Returns a retained data property given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Retained data property, or NULL on error.
 *
 * @public @memberof CowlDataProp
 */
COWL_PUBLIC
CowlDataProp* cowl_data_prop_from_string(UString string);

/**
 * Returns a retained data property given the static string representation of its IRI.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlDataProp *] Retained data property, or NULL on error.
 *
 * @public @related CowlDataProp
 */
#define cowl_data_prop_from_static(CSTR) cowl_data_prop_from_string(ustring_literal(CSTR))

/**
 * Retains the specified data property.
 *
 * @param prop The data property.
 * @return Retained data property.
 *
 * @public @memberof CowlDataProp
 */
COWL_PUBLIC
CowlDataProp* cowl_data_prop_retain(CowlDataProp *prop);

/**
 * Releases the specified data property.
 *
 * @param prop The data property.
 *
 * @public @memberof CowlDataProp
 */
COWL_PUBLIC
void cowl_data_prop_release(CowlDataProp *prop);

/**
 * Gets the IRI of the specified data property.
 *
 * @param prop The data property.
 * @return The IRI.
 *
 * @public @memberof CowlDataProp
 */
COWL_PUBLIC
CowlIRI* cowl_data_prop_get_iri(CowlDataProp *prop);

/**
 * Returns the string representation of the specified data property.
 *
 * @param prop The data property.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjProp
 */
COWL_PUBLIC
CowlString* cowl_data_prop_to_string(CowlDataProp *prop);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataProp
 */
COWL_PUBLIC
bool cowl_data_prop_equals(CowlDataProp *lhs, CowlDataProp *rhs);

/**
 * Hash function.
 *
 * @param prop The property.
 * @return The hash value.
 *
 * @public @memberof CowlDataProp
 */
COWL_PUBLIC
ulib_uint cowl_data_prop_hash(CowlDataProp *prop);

/**
 * Iterates over this data property.
 *
 * @param prop The data property.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataProp
 */
COWL_PUBLIC
bool cowl_data_prop_iterate_primitives(CowlDataProp *prop, CowlPrimitiveFlags flags,
                                       CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_DATA_PROP_H
