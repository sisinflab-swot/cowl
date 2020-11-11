/**
 * Defines cowl_ret and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_RET_H
#define COWL_RET_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
/// @endcond

/**
 * Return codes for API calls that can fail.
 *
 * @note Error codes are guaranteed to evaluate to true in boolean expressions.
 */
typedef cowl_enum(cowl_ret) {

/// @name Codes

    /// Success.
    COWL_OK,

    /// Failure with unspecified error.
    COWL_ERR,

    /**
     * Input/output error, usually returned when a file operation fails.
     *
     * @note When this happens, *errno* is sometimes set to a more meaningful value.
     */
    COWL_ERR_IO,

    /// Memory error, usually caused by failed allocations.
    COWL_ERR_MEM,

    /// Syntax error.
    COWL_ERR_SYNTAX,

/// @name Markers

    /// Number of enum values.
    COWL_RET_COUNT,

    /// First enum value.
    COWL_RET_FIRST = 0

} cowl_ret;

/**
 * Returns a human-readable string representation of the specified return value.
 *
 * @param ret Return value.
 * @return String representation, or NULL on error.
 *
 * @note You must not modify or free the returned string.
 */
char const* cowl_ret_to_cstring(cowl_ret ret);

/**
 * Returns a human-readable string representation of the specified return value.
 *
 * @param ret Return value.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 */
CowlString* cowl_ret_to_string(cowl_ret ret);

COWL_END_DECLS

#endif // COWL_RET_H
