/**
 * Defines CowlErrorHandler and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ERROR_HANDLER_H
#define COWL_ERROR_HANDLER_H

#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_error.h"
#include "cowl_ret.h"
#include "ulib.h"

COWL_BEGIN_DECLS

/// Provides a mechanism for error handling.
typedef struct CowlErrorHandler {

    /// Error handler context.
    void *ctx;

    /**
     * Pointer to a function called when an error occurs.
     *
     * @param ctx Error handler context.
     * @param error Error.
     */
    void (*handle_error)(void *ctx, CowlError const *error);

    /**
     * Pointer to a function that frees the error handler context.
     *
     * @param ctx Error handler context.
     *
     * @note This member is optional. If not set, the error handler context will not be freed.
     */
    void (*free)(void *ctx);

} CowlErrorHandler;

/**
 * Frees the error handler context.
 *
 * @param handler The error handler.
 */
COWL_API
void cowl_error_handler_free_ctx(CowlErrorHandler *handler);

/**
 * @addtogroup CowlError
 * @{
 */

/**
 * Handles an error by using the most specific error handler available.
 *
 * @param code Error code.
 * @param desc Error description.
 * @param origin Object that originated the error.
 * @return Error code.
 */
COWL_API
cowl_ret cowl_handle_error(cowl_ret code, UString desc, CowlAny *origin);

/**
 * Handles a syntax error via the most specific error handler available.
 *
 * @param desc Error description.
 * @param origin Object that originated the error.
 * @param loc Error location.
 * @return Error code.
 */
COWL_API
cowl_ret cowl_handle_syntax_error(UString desc, CowlAny *origin, CowlErrorLoc loc);

/**
 * Handles a generic error of the specified type via the most specific error handler available.
 *
 * @param code Error code.
 * @param origin Object that originated the error.
 * @return Error code.
 *
 * @note If `code` is @val{COWL_OK}, this function does nothing and returns @val{COWL_OK}.
 */
COWL_INLINE
cowl_ret cowl_handle_error_code(cowl_ret code, CowlAny *origin) {
    if (ulib_likely(code == COWL_OK)) return COWL_OK;
    return cowl_handle_error(code, ustring_empty, origin);
}

/**
 * Handles an uLib error of the specified type via the most specific error handler available.
 *
 * @param code Error code.
 * @param origin Object that originated the error.
 * @return Error code.
 *
 * @note If `code` is not an error, this function does nothing and returns @val{COWL_OK}.
 */
COWL_INLINE
cowl_ret cowl_handle_ulib_error(ulib_ret code, CowlAny *origin) {
    if (ulib_is_ok(code)) return COWL_OK;
    return cowl_handle_error(cowl_ret_from_ulib(code), ustring_empty, origin);
}

/**
 * Handles an error triggered while accessing the file at the specified path.
 *
 * @param path File path.
 * @param reason Why the error was triggered.
 * @param origin Object that originated the error.
 * @return Error code.
 */
COWL_API
cowl_ret cowl_handle_path_error(UString path, UString reason, CowlAny *origin);

/// @}

COWL_END_DECLS

#endif // COWL_ERROR_HANDLER_H
