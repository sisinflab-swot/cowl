/**
 * Defines CowlError and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2026 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ERROR_H
#define COWL_ERROR_H

#include "cowl_attrs.h"
#include "cowl_ret.h"
#include "ulib.h"
#include <stddef.h>

COWL_BEGIN_DECLS

/// Error information.
typedef struct CowlError {

    /// Error code.
    cowl_ret code;

    /// Byte offset where the error occurred, or 0 if not available.
    ulib_uint byte;

    /// Line number where the error occurred, or 0 if not available.
    ulib_uint line;

    /// Column number where the error occurred, or 0 if not available.
    ulib_uint col;

    /// Error message, or @val{ustring_null} if not available.
    UString message;

} CowlError;

/**
 * @defgroup CowlError CowlError API
 * @{
 */

/**
 * Creates a new error with the specified code and message.
 *
 * @param code Error code.
 * @param fmt Error message format string, or NULL for no message.
 * @param ... Format string arguments.
 * @return Error object.
 *
 * @destructor{cowl_error_deinit}
 */
COWL_API
CowlError cowl_error(cowl_ret code, char const *fmt, ...);

/**
 * Creates a new error with the specified code and no message.
 *
 * @param code Error code.
 * @return Error object.
 *
 * @destructor{cowl_error_deinit}
 */
COWL_INLINE
CowlError cowl_error_code(cowl_ret code) {
    return cowl_error(code, NULL);
}

/**
 * Deinitializes the error.
 *
 * @param error The error.
 */
COWL_INLINE
void cowl_error_deinit(CowlError *error) {
    ustring_deinit(&error->message);
}

/**
 * Checks if the error has a message.
 *
 * @param error The error.
 * @return True if the error has a message, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_error_has_message(CowlError const *error) {
    return !ustring_is_empty(error->message);
}

/**
 * Checks if the error has a location.
 *
 * @param error The error.
 * @return True if the error has a location, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_error_has_loc(CowlError const *error) {
    return error->line || error->col || error->byte;
}

/**
 * Converts the error to a string.
 *
 * @param error The error.
 * @return String representation of the error.
 *
 * @see @func{cowl_write_error}
 *
 * @destructor{ustring_deinit}
 */
COWL_API
UString cowl_error_to_string(CowlError const *error);

/// @}

COWL_END_DECLS

#endif // COWL_ERROR_H
