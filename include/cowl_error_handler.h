/**
 * Defines CowlErrorHandler and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020-2022 SisInf Lab, Polytechnic University of Bari
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
 * Initializes a new error handler.
 *
 * @param ctx Error handler context.
 * @param handler_func Pointer to an error handling function.
 * @param free_func Pointer to a resource deallocator function for the context.
 * @return Error handler instance.
 *
 * @public @memberof CowlErrorHandler
 */
COWL_INLINE
CowlErrorHandler cowl_error_handler(void *ctx,
                                    void (*handler_func)(void *, CowlError const *),
                                    void (*free_func)(void *)) {
    CowlErrorHandler h = { .ctx = ctx, .handle_error = handler_func, .free = free_func };
    return h;
}

/**
 * Handles an error by using the most specific error handler available.
 *
 * @param code Error code.
 * @param desc Error description.
 * @param origin Object that originated the error.
 *
 * @public @related CowlErrorHandler
 */
COWL_PUBLIC
void cowl_handle_error(cowl_ret code, UString desc, void *origin);

/**
 * Handles a syntax error via the most specific error handler available.
 *
 * @param desc Error description.
 * @param origin Object that originated the error.
 * @param loc Error location.
 *
 * @public @related CowlErrorHandler
 */
COWL_PUBLIC
void cowl_handle_syntax_error(UString desc, void *origin, CowlErrorLoc loc);

/**
 * Handles a generic error of the specified type via the most specific error handler available.
 *
 * @param code Error code.
 * @param origin Object that originated the error.
 *
 * @public @related CowlErrorHandler
 */
COWL_PUBLIC
void cowl_handle_error_code(cowl_ret code, void *origin);

/**
 * Handles an IO stream error via the most specific error handler available.
 *
 * @param code Error code.
 * @param origin Object that originated the error.
 *
 * @public @related CowlErrorHandler
 */
COWL_PUBLIC
void cowl_handle_stream_error(ustream_ret code, void *origin);

COWL_END_DECLS

#endif // COWL_ERROR_HANDLER_H
