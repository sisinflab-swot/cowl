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
 * Returns a literal.
 *
 * @param dt [optional] The datatype.
 * @param value The value.
 * @param lang [optional] The language tag.
 * @return Literal, or NULL on error.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
COWL_RETAINED
CowlLiteral *cowl_literal(CowlDatatype *dt, CowlString *value, CowlString *lang);

/**
 * Returns a literal given the string representations of its components.
 *
 * @param dt [optional] The datatype.
 * @param value The value.
 * @param lang [optional] The language tag.
 * @return Literal, or NULL on error.
 *
 * @public @memberof CowlLiteral
 */
COWL_PUBLIC
COWL_RETAINED
CowlLiteral *cowl_literal_from_string(UString dt, UString value, UString lang);

/**
 * Returns a literal given the static string representations of its components.
 *
 * @param DT [char const[], optional] The datatype.
 * @param VALUE [char const[]] The value.
 * @param LANG [char const[], optional] The language tag.
 * @return [CowlLiteral *] Literal, or NULL on error.
 *
 * @public @related CowlLiteral
 */
COWL_RETAINED
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

COWL_END_DECLS

#endif // COWL_LITERAL_H
