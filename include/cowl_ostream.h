/**
 * Declares CowlOStream and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OSTREAM_H
#define COWL_OSTREAM_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlManager);
cowl_struct_decl(CowlSymTable);
cowl_struct_decl(CowlOStream);
/// @endcond

/**
 * Ontology output stream.
 *
 * A lightweight way to serialize knowledge without creating CowlOntology objects.
 *
 * @see CowlWriter
 *
 * @struct CowlOStream
 * @extends CowlObject
 */

/**
 * Gets the manager of this ontology output stream.
 *
 * @param stream The ontology output stream.
 * @return The manager.
 *
 * @public @memberof CowlOStream
 */
COWL_PUBLIC
CowlManager *cowl_ostream_get_manager(CowlOStream *stream);

/**
 * Gets the symbol table of this ontology output stream.
 *
 * @param stream The ontology output stream.
 * @return The symbol table.
 *
 * @public @memberof CowlOStream
 */
COWL_PUBLIC
CowlSymTable *cowl_ostream_get_sym_table(CowlOStream *stream);

/**
 * Writes the ontology header.
 *
 * @param stream The ontology output stream.
 * @param header The ontology header.
 * @return Return code.
 *
 * @public @memberof CowlOStream
 */
COWL_PUBLIC
cowl_ret cowl_ostream_write_header(CowlOStream *stream, CowlOntologyHeader header);

/**
 * Writes an axiom.
 *
 * @param stream The ontology output stream.
 * @param axiom The axiom.
 * @return Return code.
 *
 * @public @memberof CowlOStream
 */
COWL_PUBLIC
cowl_ret cowl_ostream_write_axiom(CowlOStream *stream, CowlAnyAxiom *axiom);

/**
 * Writes the ontology footer.
 *
 * @param stream The ontology output stream.
 * @return Return code.
 *
 * @public @memberof CowlOStream
 */
COWL_PUBLIC
cowl_ret cowl_ostream_write_footer(CowlOStream *stream);

/**
 * Writes the specified ontology to the stream.
 *
 * @param stream The ontology output stream.
 * @param ontology The ontology.
 * @return Return code.
 *
 * @public @memberof CowlOStream
 */
COWL_PUBLIC
cowl_ret cowl_ostream_write_ontology(CowlOStream *stream, CowlOntology *ontology);

COWL_END_DECLS

#endif // COWL_OSTREAM_H
