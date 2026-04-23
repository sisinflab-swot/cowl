/**
 * Declares CowlReader and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2025 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_READER_H
#define COWL_READER_H

#include "cowl_attrs.h"
#include "cowl_change_handler.h"
#include "cowl_ret.h"
#include "cowl_utils.h"
#include "ulib.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlError);
/// @endcond

/**
 * A reader is an object that can read ontologies from an input stream.
 *
 * @superstruct{CowlObject}
 * @struct CowlReader
 */
cowl_struct_decl(CowlReader);

/// Reader implementation.
typedef struct CowlReaderImpl {

    /// Name of the reader.
    char const *name;

    /// Reader context.
    void *ctx;

    /**
     * Pointer to a function that reads an ontology from an input stream.
     *
     * @param ctx Reader context.
     * @param stream Input stream.
     * @param handler Change handler.
     * @return Return code.
     *
     * @note This member is mandatory.
     */
    cowl_ret (*read)(void *ctx, UIStream *stream, CowlChangeHandler handler);

    /**
     * Pointer to a function that returns the last error.
     *
     * @param ctx Reader context.
     * @return Last error, or NULL if no error occurred.
     *
     * @note This member is optional.
     */
    CowlError const *(*last_error)(void *ctx);

    /**
     * Pointer to a function that frees the reader context.
     *
     * @param ctx Reader context.
     *
     * @note This member is optional. If not set, the reader context will not be freed.
     */
    void (*free)(void *ctx);

} CowlReaderImpl;

/**
 * @defgroup CowlReader CowlReader API
 * @{
 */

#ifdef COWL_READER_FUNCTIONAL

/**
 * Returns the functional syntax reader.
 *
 * @return Functional syntax reader, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlReader *cowl_reader_functional(void);

#endif // COWL_READER_FUNCTIONAL

/**
 * Returns the default reader.
 *
 * @return Default reader, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlReader *cowl_reader_default(void);

/**
 * Returns a new reader.
 *
 * @param impl Reader implementation.
 * @return Reader, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlReader *cowl_reader(CowlReaderImpl impl);

/**
 * Returns the name of the reader.
 *
 * @param reader Reader.
 * @return Name of the reader.
 */
COWL_API
COWL_PURE
char const *cowl_reader_get_name(CowlReader *reader);

/**
 * Returns the implementation of the reader.
 *
 * @param reader Reader.
 * @return Reader implementation.
 */
COWL_API
COWL_PURE
CowlReaderImpl *cowl_reader_get_impl(CowlReader *reader);

/**
 * Reads an ontology from the specified input stream.
 *
 * @param reader Reader.
 * @param stream Input stream.
 * @param handler Change handler.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_reader_read(CowlReader *reader, UIStream *stream, CowlChangeHandler handler);

/**
 * Reads an ontology from the specified file path.
 *
 * @param reader Reader.
 * @param path File path.
 * @param handler Change handler.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_reader_read_path(CowlReader *reader, UString path, CowlChangeHandler handler);

/**
 * Reads an ontology from the specified input stream.
 *
 * @param reader Reader.
 * @param stream Input stream.
 * @param[out] ret Return code.
 * @return Ontology, or NULL on error.
 */
COWL_API
CowlOntology *cowl_reader_read_ontology(CowlReader *reader, UIStream *stream, cowl_ret *ret);

/**
 * Reads an ontology from the specified file path.
 *
 * @param reader Reader.
 * @param path File path.
 * @param[out] ret Return code.
 * @return Ontology, or NULL on error.
 */
COWL_API
CowlOntology *cowl_reader_read_ontology_at_path(CowlReader *reader, UString path, cowl_ret *ret);

/**
 * Returns the last error.
 *
 * @param reader Reader.
 * @return Last error, or NULL if no error occurred.
 */
COWL_API
CowlError const *cowl_reader_last_error(CowlReader *reader);

/// @}

COWL_END_DECLS

#endif // COWL_READER_H
