/**
 * Declares CowlLiteral and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_LITERAL_H
#define COWL_LITERAL_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlLiteral);
/// @endcond

/**
 * Represents a [Literal] in the OWL 2 specification.
 *
 * [Literal]: https://www.w3.org/TR/owl2-syntax/#Literals
 *
 * @struct CowlLiteral
 */

/**
 * Returns a retained literal.
 *
 * @param dt [optional] The datatype.
 * @param value The value.
 * @param lang [optional] The language tag.
 * @return Retained literal, or NULL on error.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
CowlLiteral* cowl_literal_get(CowlDatatype *dt, CowlString *value, CowlString *lang);

/**
 * Retains the specified literal.
 *
 * @param literal The literal.
 * @return Retained literal.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
CowlLiteral* cowl_literal_retain(CowlLiteral *literal);

/**
 * Releases the specified literal.
 *
 * @param literal The literal.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
void cowl_literal_release(CowlLiteral *literal);

/**
 * Gets the datatype.
 *
 * @param literal The literal.
 * @return The datatype.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
CowlDatatype* cowl_literal_get_datatype(CowlLiteral *literal);

/**
 * Gets the value.
 *
 * @param literal The literal.
 * @return The value.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
CowlString* cowl_literal_get_value(CowlLiteral *literal);

/**
 * Gets the language tag.
 *
 * @param literal The literal.
 * @return The language tag.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
CowlString* cowl_literal_get_lang(CowlLiteral *literal);

/**
 * Returns the string representation of the specified literal.
 *
 * @param literal The literal.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
CowlString* cowl_literal_to_string(CowlLiteral *literal);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
bool cowl_literal_equals(CowlLiteral *lhs, CowlLiteral *rhs);

/**
 * Hash function.
 *
 * @param literal The literal.
 * @return The hash value.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
ulib_uint cowl_literal_hash(CowlLiteral *literal);

/**
 * Iterates over the primitives referenced by the specified literal.
 *
 * @param literal The literal.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
bool cowl_literal_iterate_primitives(CowlLiteral *literal, CowlPrimitiveFlags flags,
                                     CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_LITERAL_H
