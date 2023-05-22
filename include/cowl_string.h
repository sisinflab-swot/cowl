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
#include "cowl_string_opts.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
/// @endcond

/**
 * The string type.
 *
 * @struct CowlString
 * @extends CowlObject
 */

/**
 * Returns a retained string.
 *
 * @param string The underlying string object.
 * @return Retained string, or NULL on error.
 *
 * @note The buffer of the raw string must have been dynamically allocated.
 * @note Ownership of the raw string is transferred to the newly created CowlString,
 *       meaning you must not deinitialize it.
 * @note Equivalent to `cowl_string_opt(string, COWL_SO_NONE)`.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
CowlString *cowl_string(UString string);

/**
 * Returns a retained string.
 *
 * String creation is governed by the following options:
 *
 * - COWL_SO_COPY: if set, the raw string is copied internally, otherwise it is directly assigned.
 *                 Note that in the latter case the raw string must have been dynamically allocated,
 *                 and you must not deinitialize it after passing it to this method.
 * - COWL_SO_INTERN: if set, the CowlString is either created and added to an internal
 *                   instance pool, or if an instance with the same raw string already exists
 *                   in the pool, that instance is retained and returned. This entails that
 *                   all instances created with this flag are guaranteed to be unique in memory.
 *
 * @param string The underlying string object.
 * @param opts String creation options.
 * @return Retained string, or NULL on error.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
CowlString *cowl_string_opt(UString string, CowlStringOpts opts);

/**
 * Returns a retained string from the specified static string.
 *
 * @param CSTR [char const[]] The static string.
 * @return [CowlString *] Retained string, or NULL on error.
 *
 * @public @related CowlString
 */
#define cowl_string_from_static(CSTR) cowl_string_opt(ustring_literal(CSTR), COWL_SO_COPY)

/**
 * Returns a retained empty string.
 *
 * @return Retained string, or NULL on error.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
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
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
CowlString *cowl_string_intern(CowlString *string);

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
char *cowl_string_release_copying_cstring(CowlString *string);

/**
 * Gets the underlying string buffer.
 *
 * @param string The string.
 * @return The buffer.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
char const *cowl_string_get_cstring(CowlString *string);

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
 * Gets the underlying string object.
 *
 * @param string The string.
 * @return Underlying string object.
 *
 * @public @memberof CowlString
 */
COWL_PUBLIC
UString const *cowl_string_get_raw(CowlString *string);

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
#define cowl_string_to_string(STR) ((CowlString *)cowl_retain(STR))

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
CowlString *cowl_string_with_format(char const *format, ...);

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
CowlString *cowl_string_concat(CowlString *lhs, CowlString *rhs);

/**
 * Converts the string into an integer.
 *
 * @param string The string.
 * @param out Output value.
 * @param base Numeric base.
 * @return Return code.
 *
 * @public @memberof CowlString
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
 *
 * @public @memberof CowlString
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
 *
 * @public @memberof CowlString
 */
COWL_INLINE
cowl_ret cowl_string_to_float(CowlString *string, ulib_float *out) {
    return ustring_to_float(*cowl_string_get_raw(string), out) == ULIB_OK ? COWL_OK : COWL_ERR;
}

COWL_END_DECLS

#endif // COWL_STRING_H
