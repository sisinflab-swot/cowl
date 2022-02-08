/**
 * Declares CowlString and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STRING_H
#define COWL_STRING_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
/// @endcond

/**
 * The string type.
 *
 * @struct CowlString
 */

/**
 * Returns a retained string.
 *
 * @param string The underlying string object.
 * @return Retained string, or NULL on error.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
CowlString* cowl_string_get(UString string);

/**
 * Returns a retained string from the specified static string.
 *
 * @param CSTR [char const[]] The static string.
 * @return [CowlString *] Retained string, or NULL on error.
 *
 * @public @related CowlString
 */
#define cowl_string_from_static(CSTR) cowl_string_get(ustring_copy_literal(CSTR))

/**
 * Returns a retained empty string.
 *
 * @return Retained string, or NULL on error.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
CowlString* cowl_string_get_empty(void);

/**
 * Retains the specified string.
 *
 * @param string The string.
 * @return Retained string.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
CowlString* cowl_string_retain(CowlString *string);

/**
 * Releases the specified string.
 *
 * @param string The string.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
void cowl_string_release(CowlString *string);

/**
 * Releases the specified string, returning its buffer as a copy.
 *
 * @param string The string.
 * @return The copied buffer.
 *
 * @note As an optimization, if the string is deallocated due to the release call,
 *       then the original buffer is returned.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
char const* cowl_string_release_copying_cstring(CowlString *string);

/**
 * Gets the underlying string buffer.
 *
 * @param string The string.
 * @return The buffer.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
char const* cowl_string_get_cstring(CowlString *string);


/**
 * Gets the length of the string, excluding the NULL terminator.
 *
 * @param string The string.
 * @return The length.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
ulib_uint cowl_string_get_length(CowlString *string);

/**
 * Returns the string representation of the specified string.
 *
 * @param STR [CowlString] The string.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @related CowlString
 */
#define cowl_string_to_string(STR) cowl_string_retain(STR)

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
bool cowl_string_equals(CowlString *lhs, CowlString *rhs);

/**
 * Hash function.
 *
 * @param string The string.
 * @return The hash value.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
ulib_uint cowl_string_hash(CowlString *string);

/**
 * Returns a retained string with the specified format.
 *
 * @param format Format string.
 * @param ... Format arguments.
 * @return Retained string, or NULL on error.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
CowlString* cowl_string_with_format(char const *format, ...);

/**
 * Returns a retained string obtained by concatenating two strings.
 *
 * @param lhs LHS of the concatenation.
 * @param rhs RHS of the concatenation.
 * @return Retained string, or NULL on error.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
CowlString* cowl_string_concat(CowlString *lhs, CowlString *rhs);

COWL_END_DECLS

#endif // COWL_STRING_H
