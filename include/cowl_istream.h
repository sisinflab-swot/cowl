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

#include "cowl_istream_config.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlManager);
cowl_struct_decl(CowlSymTable);
cowl_struct_decl(CowlIStream);
/// @endcond

/**
 * Ontology input stream.
 *
 * A lightweight way to access knowledge without deserializing ontologies into CowlOntology objects.
 *
 * @see CowlReader
 *
 * @struct CowlIStream
 * @extends CowlObject
 */

/**
 * Gets the manager of this ontology input stream.
 *
 * @param stream The ontology input stream.
 * @return The manager.
 *
 * @public @memberof CowlIStream
 */
COWL_PUBLIC
CowlManager *cowl_istream_get_manager(CowlIStream *stream);

/**
 * Gets the symbol table of this ontology input stream.
 *
 * @param stream The ontology input stream.
 * @return The symbol table.
 *
 * @public @memberof CowlIStream
 */
COWL_PUBLIC
CowlSymTable *cowl_istream_get_sym_table(CowlIStream *stream);

/**
 * Pushes an ontology IRI to the stream.
 *
 * @param stream The ontology input stream.
 * @param iri The ontology IRI.
 * @return Return code.
 *
 * @public @memberof CowlIStream
 */
COWL_PUBLIC
cowl_ret cowl_istream_push_iri(CowlIStream *stream, CowlIRI *iri);

/**
 * Pushes a version IRI to the stream.
 *
 * @param stream The ontology input stream.
 * @param version The version IRI.
 * @return Return code.
 *
 * @public @memberof CowlIStream
 */
COWL_PUBLIC
cowl_ret cowl_istream_push_version(CowlIStream *stream, CowlIRI *version);

/**
 * Pushes an import IRI to the stream.
 *
 * @param stream The ontology input stream.
 * @param import The import IRI.
 * @return Return code.
 *
 * @public @memberof CowlIStream
 */
COWL_PUBLIC
cowl_ret cowl_istream_push_import(CowlIStream *stream, CowlIRI *import);

/**
 * Pushes an annotation to the stream.
 *
 * @param stream The ontology input stream.
 * @param annot The annotation.
 * @return Return code.
 *
 * @public @memberof CowlIStream
 */
COWL_PUBLIC
cowl_ret cowl_istream_push_annot(CowlIStream *stream, CowlAnnotation *annot);

/**
 * Pushes an axiom to the stream.
 *
 * @param stream The ontology input stream.
 * @param axiom The axiom.
 * @return Return code.
 *
 * @public @memberof CowlIStream
 */
COWL_PUBLIC
cowl_ret cowl_istream_push_axiom(CowlIStream *stream, CowlAnyAxiom *axiom);

COWL_END_DECLS

#endif // COWL_ISTREAM_H
