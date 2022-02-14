/**
 * Declares CowlManager and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_MANAGER_H
#define COWL_MANAGER_H

#include "cowl_error_handler.h"
#include "cowl_import_loader.h"
#include "cowl_parser.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlManager);
/// @endcond

/**
 * Manages ontology documents.
 *
 * CowlManager supports multiple input sources, such as files, memory buffers, or
 * buffered streams. It also supports multiple parsers, either built-in or provided by the user.
 *
 * @see CowlParser
 *
 * @struct CowlManager
 */

/**
 * Returns a retained manager that uses the default parser.
 *
 * @return Retained manager, or NULL on error.
 *
 * @note You can specify the default parser via `cowl_api_set_parser()`.
 *
 * @public @memberof CowlManager
 */
COWL_PUBLIC
CowlManager* cowl_manager_get(void);

/**
 * Retains the specified manager.
 *
 * @param manager The manager.
 * @return Retained manager.
 *
 * @public @memberof CowlManager
 */
COWL_PUBLIC
CowlManager* cowl_manager_retain(CowlManager *manager);

/**
 * Releases the specified manager.
 *
 * @param manager The manager.
 *
 * @public @memberof CowlManager
 */
COWL_PUBLIC
void cowl_manager_release(CowlManager *manager);

/**
 * Sets the parser.
 *
 * @param manager The manager.
 * @param parser The parser.
 *
 * @public @memberof CowlManager
 */
COWL_PUBLIC
void cowl_manager_set_parser(CowlManager *manager, CowlParser parser);

/**
 * Sets the import loader.
 *
 * @param manager The manager.
 * @param loader The import loader.
 *
 * @public @memberof CowlManager
 */
COWL_PUBLIC
void cowl_manager_set_import_loader(CowlManager *manager, CowlImportLoader loader);

/**
 * Sets the error handler.
 *
 * @param manager The manager.
 * @param handler The error handler.
 *
 * @public @memberof CowlManager
 */
COWL_PUBLIC
void cowl_manager_set_error_handler(CowlManager *manager, CowlErrorHandler handler);

/**
 * Reads an ontology from the file at the specified path.
 *
 * @param manager The manager.
 * @param path The file path.
 * @return The read ontology, or NULL on error.
 *
 * @public @memberof CowlManager
 */
COWL_PUBLIC
CowlOntology* cowl_manager_read_path(CowlManager *manager, char const *path);

/**
 * Reads an ontology from the specified file.
 *
 * @param manager The manager.
 * @param file The input file.
 * @return The read ontology, or NULL on error.
 *
 * @public @memberof CowlManager
 */
COWL_PUBLIC
CowlOntology* cowl_manager_read_file(CowlManager *manager, FILE *file);

/**
 * Reads an ontology from the specified string.
 *
 * @param manager The manager.
 * @param string The input string.
 * @return The read ontology, or NULL on error.
 *
 * @public @memberof CowlManager
 */
COWL_PUBLIC
CowlOntology* cowl_manager_read_string(CowlManager *manager, UString const *string);

/**
 * Reads an ontology from the specified input stream.
 *
 * @param manager The manager.
 * @param stream The input stream.
 * @return The read ontology, or NULL on error.
 *
 * @note The stream is not released by the manager, you must do it yourself.
 *
 * @public @memberof CowlManager
 */
COWL_PUBLIC
CowlOntology* cowl_manager_read_stream(CowlManager *manager, UIStream *stream);

COWL_END_DECLS

#endif // COWL_MANAGER_H
