/**
 * Declares CowlIRI and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_IRI_H
#define COWL_IRI_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlIRI);
/// @endcond

/**
 * Represents [International Resource Identifiers].
 *
 * [International Resource Identifiers]: https://www.w3.org/TR/owl2-syntax/#IRIs
 *
 * @struct CowlIRI
 */

/**
 * Returns a retained IRI whose string representation is the concatenation of
 * the specified strings.
 *
 * @param prefix The prefix.
 * @param suffix The suffix.
 * @return Retained IRI, or NULL on error
 *
 * @public @memberof CowlIRI
 */
COWL_PUBLIC
CowlIRI* cowl_iri_get(CowlString *prefix, CowlString *suffix);

/**
 * Returns a retained IRI given its string representation.
 *
 * @param string String representation of the IRI.
 * @return Retained IRI, or NULL on error
 *
 * @public @memberof CowlIRI
 */
COWL_PUBLIC
CowlIRI* cowl_iri_from_string(UString string);

/**
 * Returns a retained IRI given its static string representation.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlIRI *] Retained IRI, or NULL on error
 *
 * @public @related CowlIRI
 */
#define cowl_iri_from_static(CSTR) (cowl_iri_from_string(ustring_literal(CSTR)))

/**
 * Retains the specified IRI.
 *
 * @param iri The IRI.
 * @return Retained IRI.
 *
 * @public @memberof CowlIRI
 */
COWL_PUBLIC
CowlIRI* cowl_iri_retain(CowlIRI *iri);

/**
 * Releases the specified IRI.
 *
 * @param iri The IRI.
 *
 * @public @memberof CowlIRI
 */
COWL_PUBLIC
void cowl_iri_release(CowlIRI *iri);

/**
 * Gets the namespace of the specified IRI.
 *
 * @param iri The IRI.
 * @return The namespace.
 *
 * @public @memberof CowlIRI
 */
COWL_PUBLIC
CowlString* cowl_iri_get_ns(CowlIRI *iri);

/**
 * Gets the remainder of the specified IRI.
 *
 * @param iri The IRI.
 * @return The remainder.
 *
 * @public @memberof CowlIRI
 */
COWL_PUBLIC
CowlString* cowl_iri_get_rem(CowlIRI *iri);

/**
 * Returns the string representation of the specified IRI.
 *
 * @param iri The IRI.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlIRI
 */
COWL_PUBLIC
CowlString* cowl_iri_to_string(CowlIRI *iri);

/**
 * Returns the string representation of the specified IRI, omitting the enclosing angular brackets.
 *
 * @param iri The IRI.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlIRI
 */
COWL_PUBLIC
CowlString* cowl_iri_to_string_no_brackets(CowlIRI *iri);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlIRI
 */
COWL_PUBLIC
bool cowl_iri_equals(CowlIRI *lhs, CowlIRI *rhs);

/**
 * Hash function.
 *
 * @param iri The IRI.
 * @return The hash value.
 *
 * @public @memberof CowlIRI
 */
COWL_PUBLIC
ulib_uint cowl_iri_hash(CowlIRI *iri);

COWL_END_DECLS

#endif // COWL_IRI_H
