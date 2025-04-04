/**
 * Defines CowlReader and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_READER_H
#define COWL_READER_H

#include "cowl_attrs.h"
#include "cowl_ret.h"
#include "cowl_utils.h"
#include "ulib.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIStream);
/// @endcond

/// Defines a reader.
typedef struct CowlReader {

    /// Name of the reader.
    char const *name;

    /// Reader context.
    void *ctx;

    /**
     * Pointer to a function that reads an ontology from an input stream.
     *
     * @param ctx Reader context.
     * @param istream Input stream.
     * @param stream Ontology input stream.
     * @return Return code.
     *
     * @note This member is mandatory.
     */
    cowl_ret (*read)(void *ctx, UIStream *istream, CowlIStream *stream);

    /**
     * Pointer to a function that frees the reader context.
     *
     * @param ctx Reader context.
     *
     * @note This member is optional. If not set, the reader context will not be freed.
     */
    void (*free)(void *ctx);

} CowlReader;

/**
 * @defgroup CowlReader CowlReader API
 * @{
 */

/**
 * Frees the reader context.
 *
 * @param reader The reader.
 */
COWL_API
void cowl_reader_free_ctx(CowlReader *reader);

#ifdef COWL_READER_FUNCTIONAL

/**
 * Returns the functional syntax reader.
 *
 * @return Functional syntax reader.
 */
COWL_API
COWL_CONST
CowlReader cowl_reader_functional(void);

#endif // COWL_READER_FUNCTIONAL

/**
 * Returns the default reader.
 *
 * @return Default reader.
 *
 * @alias CowlReader cowl_reader_default(void);
 */
#if defined(COWL_DEFAULT_READER)
#define cowl_reader_default ULIB_MACRO_CONCAT(cowl_reader_, COWL_DEFAULT_READER)
#elif defined(COWL_READER_FUNCTIONAL)
#define cowl_reader_default cowl_reader_functional
#else
#define cowl_reader_default p_cowl_reader_invalid
#endif

/// @}

// Private API

COWL_API
COWL_CONST
CowlReader p_cowl_reader_invalid(void);

COWL_END_DECLS

#endif // COWL_READER_H
