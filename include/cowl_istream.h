/**
 * Declares CowlIStream and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ISTREAM_H
#define COWL_ISTREAM_H

#include "cowl_istream_handlers.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlManager);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlSymTable);
/// @endcond

/**
 * Ontology input stream.
 *
 * A lightweight way to access knowledge without deserializing ontologies
 * into @type{#CowlOntology} objects.
 *
 * @see @type{#CowlReader}
 *
 * @superstruct{CowlObject}
 * @struct CowlIStream
 */
cowl_struct_decl(CowlIStream);

/**
 * @defgroup CowlIStream CowlIStream API
 * @{
 */

/**
 * Gets the manager of this ontology input stream.
 *
 * @param stream The ontology input stream.
 * @return The manager.
 */
COWL_API
COWL_PURE
CowlManager *cowl_istream_get_manager(CowlIStream *stream);

/**
 * Gets the symbol table of this ontology input stream.
 *
 * @param stream The ontology input stream.
 * @return The symbol table.
 */
COWL_API
COWL_PURE
CowlSymTable *cowl_istream_get_sym_table(CowlIStream *stream);

/**
 * Handles the specified ontology IRI.
 *
 * @param stream The ontology input stream.
 * @param iri The ontology IRI.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_istream_handle_iri(CowlIStream *stream, CowlIRI *iri);

/**
 * Handles the specified ontology version IRI.
 *
 * @param stream The ontology input stream.
 * @param version The version IRI.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_istream_handle_version(CowlIStream *stream, CowlIRI *version);

/**
 * Handles the specified import IRI.
 *
 * @param stream The ontology input stream.
 * @param import The import IRI.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_istream_handle_import(CowlIStream *stream, CowlIRI *import);

/**
 * Handles the specified ontology annotation.
 *
 * @param stream The ontology input stream.
 * @param annot The annotation.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_istream_handle_annot(CowlIStream *stream, CowlAnnotation *annot);

/**
 * Handles the specified axiom.
 *
 * @param stream The ontology input stream.
 * @param axiom The axiom.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_istream_handle_axiom(CowlIStream *stream, CowlAnyAxiom *axiom);

/**
 * Streams through the ontology at the specified path.
 *
 * @param stream The ontology input stream.
 * @param path The file path.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_istream_process_path(CowlIStream *stream, UString path);

/**
 * Streams through the ontology read from the specified file.
 *
 * @param stream The ontology input stream.
 * @param file The file.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_istream_process_file(CowlIStream *stream, FILE *file);

/**
 * Streams through the ontology read from the specified string.
 *
 * @param stream The ontology input stream.
 * @param string The string.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_istream_process_string(CowlIStream *stream, UString const *string);

/**
 * Streams through the ontology read from the specified input stream.
 *
 * @param stream The ontology input stream.
 * @param istream The input stream.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_istream_process_stream(CowlIStream *stream, UIStream *istream);

/**
 * Streams through the specified ontology.
 *
 * @param stream The ontology input stream.
 * @param onto The ontology.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_istream_process_ontology(CowlIStream *stream, CowlOntology *onto);

/// @}

COWL_END_DECLS

#endif // COWL_ISTREAM_H
