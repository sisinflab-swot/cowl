/**
 * Defines cowl_ret_t and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_RET_T_H
#define COWL_RET_T_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
/// @endcond

/// Return codes for API calls that can fail.
typedef enum cowl_ret_t {

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

    /// Syntax error.
    COWL_ERR_SYNTAX,

/// @name Markers

    /// Number of enum values.
    COWL_RET_COUNT,

    /// First enum value.
    COWL_RET_FIRST = 0

} cowl_ret_t;

/**
 * Returns a human-readable string representation of the specified return value.
 *
 * @param ret Return value.
 * @return String representation.
 *
 * @note You must not modify or free the returned string.
 */
char const* cowl_ret_t_to_cstring(cowl_ret_t ret);

/**
 * Returns a human-readable string representation of the specified return value.
 *
 * @param ret Return value.
 * @return String representation.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 */
CowlString* cowl_ret_t_to_string(cowl_ret_t ret);

COWL_END_DECLS

#endif // COWL_RET_T_H
