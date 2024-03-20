/**
 * Declares CowlManager and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_MANAGER_H
#define COWL_MANAGER_H

#include "cowl_error_handler.h"
#include "cowl_import_loader.h"
#include "cowl_istream_handlers.h"
#include "cowl_reader.h"
#include "cowl_writer.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIStream);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlOntologyId);
cowl_struct_decl(CowlOStream);
/// @endcond

/**
 * Manages ontology documents.
 *
 * @superstruct{CowlObject}
 * @struct CowlManager
 */
cowl_struct_decl(CowlManager);

/**
 * @defgroup CowlManager CowlManager API
 * @{
 */

/**
 * Returns a manager that uses the default reader and writer.
 *
 * @return Manager, or NULL on error.
 *
 * @note You can specify the default reader and writer
 *       via @func{#cowl_set_reader()} and @func{#cowl_set_writer()}.
 */
COWL_API
COWL_RETAINED
CowlManager *cowl_manager(void);

/**
 * Gets the reader.
 *
 * @param manager The manager.
 * @return The reader.
 */
COWL_API
CowlReader cowl_manager_get_reader(CowlManager *manager);

/**
 * Sets the reader.
 *
 * @param manager The manager.
 * @param reader The reader.
 */
COWL_API
void cowl_manager_set_reader(CowlManager *manager, CowlReader reader);

/**
 * Gets the writer.
 *
 * @param manager The manager.
 * @return The writer.
 */
COWL_API
CowlWriter cowl_manager_get_writer(CowlManager *manager);

/**
 * Sets the writer.
 *
 * @param manager The manager.
 * @param writer The writer.
 */
COWL_API
void cowl_manager_set_writer(CowlManager *manager, CowlWriter writer);

/**
 * Gets the import loader.
 *
 * @param manager The manager.
 * @return The import loader.
 */
COWL_API
CowlImportLoader cowl_manager_get_import_loader(CowlManager *manager);

/**
 * Sets the import loader.
 *
 * @param manager The manager.
 * @param loader The import loader.
 */
COWL_API
void cowl_manager_set_import_loader(CowlManager *manager, CowlImportLoader loader);

/**
 * Gets the error handler.
 *
 * @param manager The manager.
 * @return The error handler.
 */
COWL_API
CowlErrorHandler cowl_manager_get_error_handler(CowlManager *manager);

/**
 * Sets the error handler.
 *
 * @param manager The manager.
 * @param handler The error handler.
 */
COWL_API
void cowl_manager_set_error_handler(CowlManager *manager, CowlErrorHandler handler);

/**
 * Returns the number of ontologies managed by this manager.
 *
 * @param manager The manager.
 * @return Number of ontologies.
 */
COWL_API
COWL_PURE
ulib_uint cowl_manager_ontology_count(CowlManager *manager);

/**
 * Iterates over the ontologies held by the manager.
 *
 * @param manager The manager.
 * @param iter The iterator.
 * @return True if iteration was completed, false if it was stopped.
 */
COWL_API
bool cowl_manager_iterate_ontologies(CowlManager *manager, CowlIterator *iter);

/**
 * Gets the ontology with the specified identifier.
 * If no existing ontology has the specified identifier, a new ontology is returned.
 *
 * @param manager The manager.
 * @param id The ontology identifier.
 * @return Ontology with the specified identifier.
 *
 * @note You can pass NULL as the ontology identifier, in which case the function returns
 *       a new anonymous ontology.
 */
COWL_API
COWL_RETAINED
CowlOntology *cowl_manager_get_ontology(CowlManager *manager, CowlOntologyId const *id);

/**
 * Gets the ontology with the specified identifier, if it exists.
 *
 * @param manager The manager.
 * @param id The ontology identifier.
 * @return Ontology with the specified identifier, or NULL if it does not exist.
 */
COWL_API
CowlOntology *cowl_manager_retrieve_ontology(CowlManager *manager, CowlOntologyId const *id);

/**
 * Reads an ontology from the file at the specified path.
 *
 * @param manager The manager.
 * @param path The file path.
 * @return The read ontology, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlOntology *cowl_manager_read_path(CowlManager *manager, UString path);

/**
 * Reads an ontology from the specified file.
 *
 * @param manager The manager.
 * @param file The input file.
 * @return The read ontology, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlOntology *cowl_manager_read_file(CowlManager *manager, FILE *file);

/**
 * Reads an ontology from the specified string.
 *
 * @param manager The manager.
 * @param string The input string.
 * @return The read ontology, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlOntology *cowl_manager_read_string(CowlManager *manager, UString const *string);

/**
 * Reads an ontology from the specified input stream.
 *
 * @param manager The manager.
 * @param stream The input stream.
 * @return The read ontology, or NULL on error.
 *
 * @note The stream is not released by the manager, you must do it yourself.
 */
COWL_API
COWL_RETAINED
CowlOntology *cowl_manager_read_stream(CowlManager *manager, UIStream *stream);

/**
 * Writes the ontology to the file at the specified path.
 *
 * @param manager The manager.
 * @param onto The ontology.
 * @param path The file path.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_manager_write_path(CowlManager *manager, CowlOntology *onto, UString path);

/**
 * Writes the ontology to the specified file.
 *
 * @param manager The manager.
 * @param onto The ontology.
 * @param file The output file.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_manager_write_file(CowlManager *manager, CowlOntology *onto, FILE *file);

/**
 * Writes the ontology to the specified string buffer.
 *
 * @param manager The manager.
 * @param onto The ontology.
 * @param buf The string buffer.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_manager_write_strbuf(CowlManager *manager, CowlOntology *onto, UStrBuf *buf);

/**
 * Writes the ontology to the specified output stream.
 *
 * @param manager The manager.
 * @param onto The ontology.
 * @param stream The output stream.
 * @return Return code.
 *
 * @note The stream is not released by the manager, you must do it yourself.
 */
COWL_API
cowl_ret cowl_manager_write_stream(CowlManager *manager, CowlOntology *onto, UOStream *stream);

/**
 * Returns an ontology input stream.
 *
 * @param manager The manager.
 * @param handlers The handlers.
 * @return Ontology input stream.
 */
COWL_API
COWL_RETAINED
CowlIStream *cowl_manager_get_istream(CowlManager *manager, CowlIStreamHandlers handlers);

/**
 * Returns an ontology input stream that stores constructs in the specified ontology.
 *
 * @param manager The manager.
 * @param onto The ontology.
 * @return Ontology input stream.
 */
COWL_API
COWL_RETAINED
CowlIStream *cowl_manager_get_istream_to_ontology(CowlManager *manager, CowlOntology *onto);

/**
 * Returns an ontology output stream.
 *
 * @param manager The manager.
 * @param stream The output stream.
 * @return Ontology output stream.
 */
COWL_API
COWL_RETAINED
CowlOStream *cowl_manager_get_ostream(CowlManager *manager, UOStream *stream);

/// @}

COWL_END_DECLS

#endif // COWL_MANAGER_H
