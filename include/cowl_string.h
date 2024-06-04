/**
 * Declares CowlString and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STRING_H
#define COWL_STRING_H

#include "cowl_object.h"
#include "cowl_ret.h"
#include "cowl_string_opts.h" // IWYU pragma: export

COWL_BEGIN_DECLS

/**
 * The string type.
 *
 * @superstruct{CowlObject}
 * @struct CowlString
 */
cowl_struct_decl(CowlString);

/**
 * @defgroup CowlString CowlString
 * @{
 */

/**
 * Returns a string.
 *
 * @param string The underlying string object.
 * @return String, or NULL on error.
 *
 * @note The buffer of the raw string must have been dynamically allocated.
 * @note Ownership of the raw string is transferred to the newly created @type{#CowlString},
 *       meaning you must not deinitialize it.
 * @note Equivalent to calling @func{#cowl_string_opt()} with @val{#COWL_SO_NONE}.
 */
COWL_API
COWL_RETAINED
CowlString *cowl_string(UString string);

/**
 * Returns a string.
 *
 * String creation is governed by the following options:
 *
 * - @val{#COWL_SO_COPY}: if set, the raw string is copied internally, otherwise it is directly
 *                        assigned. Note that in the latter case the raw string must have been
 *                        dynamically allocated, and you must not deinitialize it after passing it
 *                        to this method.
 * - @val{#COWL_SO_INTERN}: if set, the CowlString is either created and added to an internal
 *                          instance pool, or if an instance with the same raw string already
 *                          exists in the pool, that instance is retained and returned.
 *                          This entails that all instances created with this flag are guaranteed
 *                          to be unique in memory.
 *
 * @param string The underlying string object.
 * @param opts String creation options.
 * @return String, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlString *cowl_string_opt(UString string, CowlStringOpts opts);

/**
 * Returns a string from the specified literal string.
 *
 * @param str @type{char const []} String literal.
 * @return @type{#CowlString *} String, or NULL on error.
 */
COWL_RETAINED
#define cowl_string_from_static(str) cowl_string_opt(ustring_literal(str), COWL_SO_COPY)

/**
 * Returns an empty string.
 *
 * @return String, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlString *cowl_string_empty(void);

/**
 * Interns the specified string.
 *
 * The string is either added to an internal instance pool, or if an instance with the same
 * raw string already exists in the pool, that instance is returned.
 *
 * @param string The string.
 * @return Interned string.
 *
 * @note The reference counts of the original string and that of the returned instance are not
 *       changed. This means you are still responsible for releasing the original string if
 *       you created it, and you should retain the returned string if you need to keep it alive.
 */
COWL_API
CowlString *cowl_string_intern(CowlString *string);

/**
 * Releases the specified string, returning its raw string as a copy.
 *
 * @param string The string.
 * @return Copy of the underlying string object.
 *
 * @destructor{ustring_deinit}
 * @note As an optimization, if the string is deallocated due to the release call,
 *       then the original raw string is returned.
 */
COWL_API
UString cowl_string_release_copying_raw(CowlString *string);

/**
 * Releases the specified string, returning its buffer as a copy.
 *
 * @param string The string.
 * @return The copied buffer.
 *
 * @destructor{ulib_free}
 * @note As an optimization, if the string is deallocated due to the release call,
 *       then the original buffer is returned.
 */
COWL_API
char *cowl_string_release_copying_cstring(CowlString *string);

/**
 * Gets the underlying string buffer.
 *
 * @param string The string.
 * @return The buffer.
 */
COWL_API
COWL_PURE
char const *cowl_string_get_cstring(CowlString *string);

/**
 * Gets the length of the string, excluding the NULL terminator.
 *
 * @param string The string.
 * @return The length.
 */
COWL_API
COWL_PURE
ulib_uint cowl_string_get_length(CowlString *string);

/**
 * Gets the underlying string object.
 *
 * @param string The string.
 * @return Underlying string object.
 */
COWL_API
COWL_PURE
UString const *cowl_string_get_raw(CowlString *string);

/**
 * Returns a string with the specified format.
 *
 * @param format Format string.
 * @param ... Format arguments.
 * @return String, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlString *cowl_string_with_format(char const *format, ...);

/**
 * Returns a string obtained by concatenating two strings.
 *
 * @param lhs LHS of the concatenation.
 * @param rhs RHS of the concatenation.
 * @return String, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlString *cowl_string_concat(CowlString *lhs, CowlString *rhs);

/**
 * Converts the string into an integer.
 *
 * @param string The string.
 * @param out Output value.
 * @param base Numeric base.
 * @return Return code.
 */
COWL_INLINE
cowl_ret cowl_string_to_int(CowlString *string, ulib_int *out, unsigned base) {
    return ustring_to_int(*cowl_string_get_raw(string), out, base) == ULIB_OK ? COWL_OK : COWL_ERR;
}

/**
 * Converts the string into an unsigned integer.
 *
 * @param string The string.
 * @param out Output value.
 * @param base Numeric base.
 * @return Return code.
 */
COWL_INLINE
cowl_ret cowl_string_to_uint(CowlString *string, ulib_uint *out, unsigned base) {
    return ustring_to_uint(*cowl_string_get_raw(string), out, base) == ULIB_OK ? COWL_OK : COWL_ERR;
}

/**
 * Converts the string into a float.
 *
 * @param string The string.
 * @param out Output value.
 * @return Return code.
 */
COWL_INLINE
cowl_ret cowl_string_to_float(CowlString *string, ulib_float *out) {
    return ustring_to_float(*cowl_string_get_raw(string), out) == ULIB_OK ? COWL_OK : COWL_ERR;
}

/// @}

COWL_END_DECLS

#endif // COWL_STRING_H
