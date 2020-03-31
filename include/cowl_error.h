/**
 * Defines CowlError and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ERROR_H
#define COWL_ERROR_H

#include "cowl_std.h"
#include "vector.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
/// @endcond

/// Error data structure.
typedef cowl_struct(CowlError) {

    /// Error code.
    cowl_ret_t code;

    /// If code is COWL_ERR_SYNTAX, this is the line where the error occurred.
    cowl_uint_t line;

    /// Human readable description of the error.
    CowlString *description;

} CowlError;

/// @cond
VECTOR_DECL_SPEC(CowlError, COWL_PUBLIC)
/// @endcond

/**
 * Vector of CowlError elements.
 *
 * @struct Vector_CowlError
 * @extends Vector
 */

/**
 * Initializes a new error.
 *
 * @param CODE [cowl_ret_t] Error code.
 * @param DESC [CowlString *] Error description.
 * @param LINE [cowl_uint_t] Line where the error occurred.
 * @return [CowlError] Error instance.
 *
 * @public @related CowlError
 */
#define cowl_error_init(CODE, DESC, LINE) ((CowlError)) {                                           \
    .code = (CODE), .description = (DESC), .line = (LINE)                                           \
}

/**
 * Convenience error initializer.
 *
 * @param CODE [cowl_ret_t] Error code.
 * @param DESC [char const *] Error description.
 * @param LINE [cowl_uint_t] Line where the error occurred.
 * @return [CowlError] Error instance.
 *
 * @public @related CowlError
 */
#define cowl_error_init_cstring(CODE, DESC, LINE) ((CowlError) {                                    \
    .code = (CODE),                                                                                 \
    .description = cowl_string_get((DESC), strlen(DESC), true),                                     \
    .line = (LINE)                                                                                  \
})

/**
 * Retains the specified error.
 *
 * @param ERROR [CowlError] The error.
 * @return [CowlError] Retained error.
 *
 * @public @related CowlError
 */
#define cowl_error_retain(ERROR) (cowl_string_retain((ERROR).description), (ERROR))

/**
 * Releases the specified error.
 *
 * @param ERROR [CowlError] The error.
 *
 * @public @related CowlError
 */
#define cowl_error_release(ERROR) cowl_string_release((ERROR).description)

/**
 * Returns a human-readable string representation of the specified error.
 *
 * @param error The error.
 * @return String representation.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlError
 */
COWL_PUBLIC
CowlString* cowl_error_to_string(CowlError error);

COWL_END_DECLS

#endif // COWL_ERROR_H
