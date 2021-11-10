/**
 * Declares CowlReader and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_READER_H
#define COWL_READER_H

#include "cowl_error_handler.h"
#include "cowl_import_loader.h"
#include "cowl_parser.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlReader);
/// @endcond

/**
 * Reads ontology documents.
 *
 * CowlReader supports multiple input sources, such as files, memory buffers, or buffered
 * input streams. It also supports multiple parsers, either built-in or provided by the user.
 *
 * @see CowlParser
 *
 * @struct CowlReader
 */

/**
 * Returns a retained reader that uses the default parser.
 *
 * @return Retained reader, or NULL on error.
 *
 * @note You can specify the default parser via `cowl_api_set_parser()`.
 *
 * @public @memberof CowlReader
 */
COWL_PUBLIC
CowlReader* cowl_reader_get(void);

/**
 * Returns a retained reader that uses the specified parser.
 *
 * @param parser The parser.
 * @return Retained reader, or NULL on error.
 *
 * @public @memberof CowlReader
 */
COWL_PUBLIC
CowlReader* cowl_reader_get_with_parser(CowlParser parser);

/**
 * Retains the specified reader.
 *
 * @param reader The reader.
 * @return Retained reader.
 *
 * @public @memberof CowlReader
 */
COWL_PUBLIC
CowlReader* cowl_reader_retain(CowlReader *reader);

/**
 * Releases the specified reader.
 *
 * @param reader The reader.
 *
 * @public @memberof CowlReader
 */
COWL_PUBLIC
void cowl_reader_release(CowlReader *reader);

/**
 * Sets the import loader.
 *
 * @param reader The reader.
 * @param loader The import loader.
 *
 * @public @memberof CowlReader
 */
COWL_PUBLIC
void cowl_reader_set_import_loader(CowlReader *reader, CowlImportLoader loader);

/**
 * Sets the error handler.
 *
 * @param reader The reader.
 * @param handler The error handler.
 *
 * @public @memberof CowlReader
 */
COWL_PUBLIC
void cowl_reader_set_error_handler(CowlReader *reader, CowlErrorHandler handler);

/**
 * Reads an ontology from the file at the specified path.
 *
 * @param reader The reader.
 * @param path The file path.
 * @return The read ontology, or NULL on error.
 *
 * @public @memberof CowlReader
 */
COWL_PUBLIC
CowlOntology* cowl_reader_read_path(CowlReader *reader, char const *path);

/**
 * Reads an ontology from the specified file.
 *
 * @param reader The reader.
 * @param file The input file.
 * @return The read ontology, or NULL on error.
 *
 * @public @memberof CowlReader
 */
COWL_PUBLIC
CowlOntology* cowl_reader_read_file(CowlReader *reader, FILE *file);

/**
 * Reads an ontology from the specified string.
 *
 * @param reader The reader.
 * @param cstring The input string.
 * @param length Length of the input string (excluding the NULL terminator).
 * @return The read ontology, or NULL on error.
 *
 * @public @memberof CowlReader
 */
COWL_PUBLIC
CowlOntology* cowl_reader_read_cstring(CowlReader *reader, char const *cstring, size_t length);

/**
 * Reads an ontology from the specified input stream.
 *
 * @param reader The reader.
 * @param stream The input stream.
 * @return The read ontology, or NULL on error.
 *
 * @note The stream is not released by the reader, you must do it yourself.
 *
 * @public @memberof CowlReader
 */
COWL_PUBLIC
CowlOntology* cowl_reader_read_stream(CowlReader *reader, UIStream const *stream);

COWL_END_DECLS

#endif // COWL_READER_H
