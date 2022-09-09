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

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlError);
/// @endcond

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
CowlErrorHandler cowl_error_handler_init(void *ctx,
                                         void (*handler_func)(void *, CowlError const *),
                                         void (*free_func)(void *)) {
    CowlErrorHandler h = { .ctx = ctx, .handle_error = handler_func, .free = free_func };
    return h;
}

COWL_END_DECLS

#endif // COWL_ERROR_HANDLER_H
