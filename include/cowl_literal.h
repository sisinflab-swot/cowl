/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_LITERAL_H
#define COWL_LITERAL_H

#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_utils.h"
#include "ulib.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDatatype);
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
 * @param value The value.
 * @param dt_or_lang @ctype{optional} The datatype, language tag, or NULL for a plain literal.
 * @return Literal, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlLiteral *cowl_literal(CowlString *value, CowlAny *dt_or_lang);

/**
 * Returns a plain literal given the string representations of its value.
 *
 * @param value The value.
 * @return Literal, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlLiteral *cowl_literal_plain(UString value);

/**
 * Returns a typed literal given the string representation of its value and its datatype.
 *
 * @param value The value.
 * @param dt The datatype.
 * @return Literal, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlLiteral *cowl_literal_typed(UString value, CowlDatatype *dt);

/**
 * Returns a language-tagged literal given the string representations of its value and language tag.
 *
 * @param value The value.
 * @param lang The language tag.
 * @return Literal, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlLiteral *cowl_literal_lang(UString value, UString lang);

/**
 * Returns a plain literal given the string literal representing its value.
 *
 * @param value @ctype{char const[]} The value.
 * @return @ctype{#CowlLiteral *} Literal, or NULL on error.
 */
COWL_RETAINED
#define cowl_literal_plain_from_static(value) cowl_literal_plain(ustring_literal(value))

/**
 * Returns a typed literal given the string literal representing its value and its datatype.
 *
 * @param value @ctype{char const[]} The value.
 * @param dt @ctype{#CowlDatatype *} The datatype.
 * @return @ctype{#CowlLiteral *} Literal, or NULL on error.
 */
COWL_RETAINED
#define cowl_literal_typed_from_static(value, dt) cowl_literal_typed(ustring_literal(value), dt)

/**
 * Returns a language-tagged literal given the string literals representing its value
 * and language tag.
 *
 * @param value @ctype{char const[]} The value.
 * @param lang @ctype{char const[]} The language tag.
 * @return @ctype{#CowlLiteral *} Literal, or NULL on error.
 */
COWL_RETAINED
#define cowl_literal_lang_from_static(value, lang)                                                 \
    cowl_literal_lang(ustring_literal(value), ustring_literal(lang))

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
