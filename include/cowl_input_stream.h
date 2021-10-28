/**
 * Defines CowlInputStream and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INPUT_STREAM_H
#define COWL_INPUT_STREAM_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// Models a generic input stream.
typedef cowl_struct(CowlInputStream) {

    /// Stream context, can be anything.
    void *ctx;

    /**
     * Stream description.
     *
     * @note This field is optional. Setting it will result in better error reporting, as it
     *       will be used to populate the `source` field in `CowlError`.
     */
    char const *description;

    /**
     * Pointer to a function that reads a maximum of `count` bytes by copying them into `buf`.
     *
     * @param ctx Stream context.
     * @param buf Input buffer.
     * @param count Maximum number of bytes to read.
     * @param[out] read Number of bytes read.
     * @return Return code.
     */
    cowl_ret (*read_bytes)(void *ctx, cowl_byte *buf, size_t count, size_t *read);

    /**
     * Pointer to a function that releases any resource reserved by the stream.
     * The provided function is invoked when `cowl_input_stream_deinit` is called.
     *
     * @param ctx Stream context.
     * @return Return code.
     *
     * @note Can be NULL if the stream does not need to release resources.
     */
    cowl_ret (*free)(void *ctx);

} CowlInputStream;

/**
 * Initializes a new input stream.
 *
 * @param CTX Stream context.
 * @param DESC Stream description.
 * @param READ_FUNC `read_bytes` function pointer.
 * @param FREE_FUNC `free` function pointer.
 * @return Input stream instance.
 *
 * @public @related CowlInputStream
 */
#define cowl_input_stream_init(CTX, DESC, READ_FUNC, FREE_FUNC)                                     \
    ((CowlInputStream){                                                                             \
        .ctx = (CTX),                                                                               \
        .description = (DESC),                                                                      \
        .read_bytes = (READ_FUNC),                                                                  \
        .free = (FREE_FUNC)                                                                         \
    })

/**
 * Deinitializes an input stream, releasing any reserved resource.
 *
 * @param stream Input stream.
 * @return Return code.
 *
 * @public @memberof CowlInputStream
 */
COWL_PUBLIC
cowl_ret cowl_input_stream_deinit(CowlInputStream *stream);

/**
 * Initializes an input stream so that it reads from the file at the specified path.
 *
 * @param stream Input stream.
 * @param path Path to the file to read from.
 * @return Return code.
 *
 * @public @memberof CowlInputStream
 */
COWL_PUBLIC
cowl_ret cowl_input_stream_from_path(CowlInputStream *stream, char const *path);

/**
 * Initializes an input stream so that it reads from the specified file.
 *
 * @param stream Input stream.
 * @param file The input file.
 * @return Return code.
 *
 * @public @memberof CowlInputStream
 */
COWL_PUBLIC
cowl_ret cowl_input_stream_from_file(CowlInputStream *stream, FILE *file);

/**
 * Initializes an input stream so that it reads from the specified string.
 *
 * @param stream Input stream.
 * @param cstring The input string.
 * @param length Length of the input string (excluding the NULL terminator).
 * @return Return code.
 *
 * @public @memberof CowlInputStream
 */
COWL_PUBLIC
cowl_ret cowl_input_stream_from_cstring(CowlInputStream *stream, char const *cstring,
                                        size_t length);

/**
 * Reads a maximum of `count` bytes into `buf` from the specified input stream.
 *
 * @param stream Input stream.
 * @param buf Input buffer.
 * @param count Maximum number of bytes to read.
 * @param[out] read Number of bytes read.
 * @return Return code.
 *
 * @public @memberof CowlInputStream
 */
COWL_PUBLIC
cowl_ret cowl_input_stream_read_bytes(CowlInputStream const *stream, cowl_byte *buf,
                                      size_t count, size_t *read);

COWL_END_DECLS

#endif // COWL_INPUT_STREAM_H
