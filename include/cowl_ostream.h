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

#include "cowl_attrs.h"
#include "cowl_macros.h"
#include "cowl_ontology_header.h"
#include "cowl_ret.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlManager);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlSymTable);
/// @endcond

/**
 * Ontology output stream.
 *
 * A lightweight way to serialize knowledge without creating @type{#CowlOntology} objects.
 *
 * @see @type{#CowlWriter}
 *
 * @superstruct{CowlObject}
 * @struct CowlOStream
 */
cowl_struct_decl(CowlOStream);

/**
 * @defgroup CowlOStream CowlOStream API
 * @{
 */

/**
 * Gets the manager of this ontology output stream.
 *
 * @param stream The ontology output stream.
 * @return The manager.
 */
COWL_API
COWL_PURE
CowlManager *cowl_ostream_get_manager(CowlOStream *stream);

/**
 * Gets the symbol table of this ontology output stream.
 *
 * @param stream The ontology output stream.
 * @return The symbol table.
 */
COWL_API
COWL_PURE
CowlSymTable *cowl_ostream_get_sym_table(CowlOStream *stream);

/**
 * Writes the ontology header.
 *
 * @param stream The ontology output stream.
 * @param header The ontology header.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ostream_write_header(CowlOStream *stream, CowlOntologyHeader header);

/**
 * Writes an axiom.
 *
 * @param stream The ontology output stream.
 * @param axiom The axiom.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ostream_write_axiom(CowlOStream *stream, CowlAnyAxiom *axiom);

/**
 * Writes the ontology footer.
 *
 * @param stream The ontology output stream.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ostream_write_footer(CowlOStream *stream);

/**
 * Writes the specified ontology to the stream.
 *
 * @param stream The ontology output stream.
 * @param onto The ontology.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ostream_write_ontology(CowlOStream *stream, CowlOntology *onto);

/// @}

COWL_END_DECLS

#endif // COWL_OSTREAM_H
