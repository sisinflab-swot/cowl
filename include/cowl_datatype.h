/**
 * Declares CowlDatatype and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATATYPE_H
#define COWL_DATATYPE_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlDatatype);
/// @endcond

/**
 * Represents a [Datatype] in the OWL 2 specification.
 *
 * [Datatype]: https://www.w3.org/TR/owl2-syntax/#Datatypes
 *
 * @struct CowlDatatype
 * @extends CowlDataRange
 */

/**
 * Returns a retained datatype.
 *
 * @param iri IRI of the datatype.
 * @return Retained datatype, or NULL on error.
 *
 * @public @memberof CowlDatatype
 */
COWL_PUBLIC
CowlDatatype* cowl_datatype_get(CowlIRI *iri);

/**
 * Returns a retained datatype given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Retained datatype, or NULL on error.
 *
 * @public @memberof CowlDatatype
 */
COWL_PUBLIC
CowlDatatype* cowl_datatype_from_string(UString string);

/**
 * Returns a retained datatype given the static string representation of its IRI.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlDatatype *] Retained datatype, or NULL on error.
 *
 * @public @related CowlDatatype
 */
#define cowl_datatype_from_static(CSTR) cowl_datatype_from_string(ustring_literal(CSTR))

/**
 * Retains the specified datatype.
 *
 * @param dt The datatype.
 * @return Retained datatype.
 *
 * @public @memberof CowlDatatype
 */
COWL_PUBLIC
CowlDatatype* cowl_datatype_retain(CowlDatatype *dt);

/**
 * Releases the specified datatype.
 *
 * @param dt The datatype.
 *
 * @public @memberof CowlDatatype
 */
COWL_PUBLIC
void cowl_datatype_release(CowlDatatype *dt);

/**
 * Gets the IRI of the specified datatype.
 *
 * @param dt The datatype.
 * @return The IRI.
 *
 * @public @memberof CowlDatatype
 */
COWL_PUBLIC
CowlIRI* cowl_datatype_get_iri(CowlDatatype *dt);

/**
 * Returns the string representation of the specified datatype.
 *
 * @param dt The datatype.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDatatype
 */
COWL_PUBLIC
CowlString* cowl_datatype_to_string(CowlDatatype *dt);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDatatype
 */
COWL_PUBLIC
bool cowl_datatype_equals(CowlDatatype *lhs, CowlDatatype *rhs);

/**
 * Hash function.
 *
 * @param dt The datatype.
 * @return The hash value.
 *
 * @public @memberof CowlDatatype
 */
COWL_PUBLIC
ulib_uint cowl_datatype_hash(CowlDatatype *dt);

/**
 * Iterates over this datatype.
 *
 * @param dt The datatype.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDatatype
 */
COWL_PUBLIC
bool cowl_datatype_iterate_primitives(CowlDatatype *dt, CowlPrimitiveFlags flags,
                                      CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_DATATYPE_H
