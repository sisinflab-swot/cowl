/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STREAM_H
#define COWL_STREAM_H

#include "cowl_error_handler.h"
#include "cowl_object.h"
#include "cowl_reader.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlManager);
cowl_struct_decl(CowlSymTable);
cowl_struct_decl(CowlStream);
/// @endcond

/**
 * Ontology streams.
 *
 * A lightweight way to access knowledge without deserializing ontologies into CowlOntology objects.
 *
 * @see CowlReader
 *
 * @struct CowlStream
 * @extends CowlObject
 */

/**
 * Gets the manager of this ontology stream.
 *
 * @param stream The ontology stream.
 * @return The manager.
 *
 * @public @memberof CowlStream
 */
COWL_PUBLIC
CowlManager *cowl_stream_get_manager(CowlStream *stream);

/**
 * Gets the symbol table of this ontology stream.
 *
 * @param stream The ontology stream.
 * @return The symbol table.
 *
 * @public @memberof CowlStream
 */
COWL_PUBLIC
CowlSymTable *cowl_stream_get_sym_table(CowlStream *stream);

/**
 * Pushes an ontology IRI to the stream.
 *
 * @param stream The ontology stream.
 * @param iri The ontology IRI.
 * @return Return code.
 *
 * @public @memberof CowlStream
 */
COWL_PUBLIC
cowl_ret cowl_stream_push_iri(CowlStream *stream, CowlIRI *iri);

/**
 * Pushes a version IRI to the stream.
 *
 * @param stream The ontology stream.
 * @param version The version IRI.
 * @return Return code.
 *
 * @public @memberof CowlStream
 */
COWL_PUBLIC
cowl_ret cowl_stream_push_version(CowlStream *stream, CowlIRI *version);

/**
 * Pushes an import IRI to the stream.
 *
 * @param stream The ontology stream.
 * @param import The import IRI.
 * @return Return code.
 *
 * @public @memberof CowlStream
 */
COWL_PUBLIC
cowl_ret cowl_stream_push_import(CowlStream *stream, CowlIRI *import);

/**
 * Pushes an annotation to the stream.
 *
 * @param stream The ontology stream.
 * @param annot The annotation.
 * @return Return code.
 *
 * @public @memberof CowlStream
 */
COWL_PUBLIC
cowl_ret cowl_stream_push_annot(CowlStream *stream, CowlAnnotation *annot);

/**
 * Pushes an axiom to the stream.
 *
 * @param stream The ontology stream.
 * @param axiom The axiom.
 * @return Return code.
 *
 * @public @memberof CowlStream
 */
COWL_PUBLIC
cowl_ret cowl_stream_push_axiom(CowlStream *stream, CowlAnyAxiom *axiom);

COWL_END_DECLS

#endif // COWL_STREAM_H
