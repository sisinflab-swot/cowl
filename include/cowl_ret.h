/**
 * Defines cowl_ret and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_RET_H
#define COWL_RET_H

#include "cowl_attrs.h"
#include "cowl_utils.h"
#include "ulib.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
/// @endcond

/**
 * @defgroup cowl_ret cowl_ret
 * @{
 */

/**
 * Return codes for API calls that can fail.
 *
 * @note Error codes are guaranteed to evaluate to true in boolean expressions.
 */
typedef enum cowl_ret {

    /// @name Codes

    /// Success.
    COWL_OK,

    /// Failure with unspecified error.
    COWL_ERR,

    /**
     * Input/output error, usually returned when a file or stream operation fails.
     *
     * @note When this happens, @cvar{errno} is sometimes set to a more meaningful value.
     */
    COWL_ERR_IO,

    /// Memory error, usually caused by failed allocations.
    COWL_ERR_MEM,

    /// Syntax error.
    COWL_ERR_SYNTAX,

} cowl_ret;

/**
 * Checks if a return code indicates an error.
 *
 * @param ret Return code.
 * @return True if the return code indicates an error, false otherwise.
 */
COWL_CONST
COWL_INLINE
bool cowl_ret_is_err(cowl_ret ret) {
    return ret >= COWL_ERR;
}

/**
 * Checks if a return code does not indicate an error.
 *
 * @param ret Return code.
 * @return True if the return code does not indicate an error, false otherwise.
 */
COWL_CONST
COWL_INLINE
bool cowl_ret_is_ok(cowl_ret ret) {
    return !cowl_ret_is_err(ret);
}

/**
 * Checks if a return code indicates an error.
 *
 * @param ret Return code.
 * @return True if the return code indicates an error, false otherwise.
 *
 * @note Hints the compiler that the condition is unlikely to be true.
 * @alias bool cowl_is_err(cowl_ret ret);
 */
#define cowl_is_err(ret) ulib_unlikely(cowl_ret_is_err(ret))

/**
 * Checks if a return code does not indicate an error.
 *
 * @param ret Return code.
 * @return True if the return code does not indicate an error, false otherwise.
 *
 * @note Hints the compiler that the condition is likely to be true.
 * @alias bool cowl_is_ok(cowl_ret ret);
 */
#define cowl_is_ok(ret) ulib_likely(cowl_ret_is_ok(ret))

/**
 * Converts @type{ulib_ret} into @type{cowl_ret}.
 *
 * @param ret Return code.
 * @return Return value.
 */
COWL_API
COWL_CONST
cowl_ret cowl_ret_from_ulib(ulib_ret ret);

/**
 * Returns a human-readable string representation of the specified return value.
 *
 * @param ret Return value.
 * @return String representation, or NULL on error.
 *
 * @note You must not modify or free the returned string.
 */
COWL_API
COWL_CONST
UString cowl_ret_to_ustring(cowl_ret ret);

/**
 * Returns a human-readable string representation of the specified return value.
 *
 * @param ret Return value.
 * @return String representation, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlString *cowl_ret_to_string(cowl_ret ret);

/// @}

COWL_END_DECLS

#endif // COWL_RET_H
