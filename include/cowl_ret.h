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

/// Return code type.
typedef ulib_ret cowl_ret;

/// Builtin return codes.
typedef enum cowl_ret_builtin {

    /// The operation succeeded.
    COWL_OK = ULIB_OK,

    /**
     * The operation did not succeed.
     *
     * @note This code is returned when an operation does not succeed as part of its normal
     *       execution. It does not signal an error condition.
     * @note This code is also returned when an operation is stopped by e.g. returning
     *       @val{COWL_NO} from an iterator function.
     */
    COWL_NO = ULIB_NO,

    /// The operation failed due to an unspecified error.
    COWL_ERR = ULIB_ERR,

    /// The operation failed due to a memory allocation error.
    COWL_ERR_MEM = ULIB_ERR_MEM,

    /// Buffer bounds exceeded, or value over/underflowed its type.
    COWL_ERR_BOUNDS = ULIB_ERR_BOUNDS,

    /**
     * The operation failed due to an IO error.
     *
     * @note When this happens, @cval{errno} is sometimes set to a more meaningful value.
     */
    COWL_ERR_IO = ULIB_ERR_IO,

    /// Syntax error.
    COWL_ERR_SYNTAX = -32,

} cowl_ret_builtin;

/// Alias for @val{COWL_OK}, used to indicate that an operation should continue.
#define COWL_CONTINUE COWL_OK

/// Alias for @val{COWL_NO}, used to indicate that an operation should be stopped.
#define COWL_STOP COWL_NO

/**
 * Checks if a return code indicates an error.
 *
 * @param ret Return code.
 * @return True if the return code indicates an error, false otherwise.
 */
COWL_CONST
COWL_INLINE
bool cowl_ret_is_err(cowl_ret ret) {
    return ulib_ret_is_err(ret);
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
 * Checks if a return code indicates that an operation should be stopped.
 *
 * @param ret Return code.
 * @return True if the return code indicates that an operation should be stopped, false otherwise.
 */
COWL_CONST
COWL_INLINE
bool cowl_ret_should_stop(cowl_ret ret) {
    return ret != COWL_CONTINUE;
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
 * Checks if a return code indicates that an operation should be stopped.
 *
 * @param ret Return code.
 * @return True if the return code indicates that an operation should be stopped, false otherwise.
 *
 * @note Hints the compiler that the condition is unlikely to be true.
 * @alias bool cowl_should_stop(cowl_ret ret);
 */
#define cowl_should_stop(ret) ulib_unlikely(cowl_ret_should_stop(ret))

/**
 * Converts @type{ulib_ret} into @type{cowl_ret}.
 *
 * @param ret Return code.
 * @return Return value.
 */
COWL_CONST
COWL_INLINE
cowl_ret cowl_ret_from_ulib(ulib_ret ret) {
    return (cowl_ret)ret;
}

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
UString cowl_ret_to_string(cowl_ret ret);

/// @}

COWL_END_DECLS

#endif // COWL_RET_H
