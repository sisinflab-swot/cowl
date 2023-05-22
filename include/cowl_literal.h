/**
 * Declares CowlLiteral and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_LITERAL_H
#define COWL_LITERAL_H

#include "cowl_object.h"

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
 * @extends CowlAnnotValue
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
CowlLiteral *cowl_literal(CowlDatatype *dt, CowlString *value, CowlString *lang);

/**
 * Returns a retained literal given the string representations of its components.
 *
 * @param dt [optional] The datatype.
 * @param value The value.
 * @param lang [optional] The language tag.
 * @return Retained literal, or NULL on error.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
CowlLiteral *cowl_literal_from_string(UString dt, UString value, UString lang);

/**
 * Returns a retained literal given the static string representations of its components.
 *
 * @param DT [char const[], optional] The datatype.
 * @param VALUE [char const[]] The value.
 * @param LANG [char const[], optional] The language tag.
 * @return [CowlLiteral *] Retained literal, or NULL on error.
 *
 * @public @related CowlLiteral
 */
#define cowl_literal_from_static(DT, VALUE, LANG)                                                  \
    cowl_literal_from_string(ustring_literal(DT), ustring_literal(VALUE), ustring_literal(LANG))

/**
 * Gets the datatype.
 *
 * @param literal The literal.
 * @return The datatype.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
CowlDatatype *cowl_literal_get_datatype(CowlLiteral *literal);

/**
 * Gets the value.
 *
 * @param literal The literal.
 * @return The value.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
CowlString *cowl_literal_get_value(CowlLiteral *literal);

/**
 * Gets the language tag.
 *
 * @param literal The literal.
 * @return The language tag.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
CowlString *cowl_literal_get_lang(CowlLiteral *literal);

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
CowlString *cowl_literal_to_string(CowlLiteral *literal);

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

COWL_END_DECLS

#endif // COWL_LITERAL_H
