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
/// @endcond

/**
 * Represents a [Literal] in the OWL 2 specification.
 *
 * [Literal]: https://www.w3.org/TR/owl2-syntax/#Literals
 *
 * @superstruct{CowlAnnotValue}
 * @struct CowlLiteral
 */
cowl_struct_decl(CowlLiteral);

/**
 * @defgroup CowlLiteral CowlLiteral API
 * @{
 */

/**
 * Returns a literal.
 *
 * @param dt @type{optional} The datatype.
 * @param value The value.
 * @param lang @type{optional} The language tag.
 * @return Literal, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlLiteral *cowl_literal(CowlDatatype *dt, CowlString *value, CowlString *lang);

/**
 * Returns a literal given the string representations of its components.
 *
 * @param dt @type{optional} The datatype.
 * @param value The value.
 * @param lang @type{optional} The language tag.
 * @return Literal, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlLiteral *cowl_literal_from_string(UString dt, UString value, UString lang);

/**
 * Returns a literal given the string literals representing its components.
 *
 * @param dt @type{char const[], optional} The datatype.
 * @param value @type{char const []} The value.
 * @param lang @type{char const[], optional} The language tag.
 * @return @type{#CowlLiteral *} Literal, or NULL on error.
 */
COWL_RETAINED
#define cowl_literal_from_static(dt, value, lang)                                                  \
    cowl_literal_from_string(ustring_literal(dt), ustring_literal(value), ustring_literal(lang))

/**
 * Gets the datatype.
 *
 * @param literal The literal.
 * @return The datatype.
 */
COWL_API
COWL_PURE
CowlDatatype *cowl_literal_get_datatype(CowlLiteral *literal);

/**
 * Gets the value.
 *
 * @param literal The literal.
 * @return The value.
 */
COWL_API
COWL_PURE
CowlString *cowl_literal_get_value(CowlLiteral *literal);

/**
 * Gets the language tag.
 *
 * @param literal The literal.
 * @return The language tag.
 */
COWL_API
COWL_PURE
CowlString *cowl_literal_get_lang(CowlLiteral *literal);

/// @}

COWL_END_DECLS

#endif // COWL_LITERAL_H
