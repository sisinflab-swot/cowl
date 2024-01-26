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

#include "cowl_error.h"

COWL_BEGIN_DECLS

/// Provides a mechanism for error handling.
typedef struct CowlErrorHandler {

    /// Error handler context, can be anything.
    void *ctx;

    /**
     * Pointer to a function called when an error occurs.
     *
     * @param ctx Error handler context.
     * @param error Error.
     */
    void (*handle_error)(void *ctx, CowlError const *error);

    /**
     * Pointer to a resource deallocator function for the context.
     *
     * @param ctx Error handler context.
     *
     * @note Can be NULL if the context does not need to release resources.
     */
    void (*free)(void *ctx);

} CowlErrorHandler;

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
 */
COWL_API
cowl_ret cowl_handle_error_code(cowl_ret code, CowlAny *origin);

/**
 * Handles an IO stream error via the most specific error handler available.
 *
 * @param code Error code.
 * @param origin Object that originated the error.
 * @return Error code.
 */
COWL_API
cowl_ret cowl_handle_stream_error(ustream_ret code, CowlAny *origin);

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
