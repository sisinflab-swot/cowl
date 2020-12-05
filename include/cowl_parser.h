/**
 * Declares CowlParser and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PARSER_H
#define COWL_PARSER_H

#include "cowl_error_handler.h"
#include "cowl_imports_loader.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlParser);
/// @endcond

/**
 * Allows for the deserialization of ontology documents.
 *
 * @struct CowlParser
 */

/**
 * Returns a retained parser.
 *
 * @return Retained parser, or NULL on error.
 *
 * @public @memberof CowlParser
 */
COWL_PUBLIC
CowlParser* cowl_parser_get(void);

/**
 * Retains the specified parser.
 *
 * @param parser The parser.
 * @return Retained parser.
 *
 * @public @memberof CowlParser
 */
COWL_PUBLIC
CowlParser* cowl_parser_retain(CowlParser *parser);

/**
 * Releases the specified parser.
 *
 * @param parser The parser.
 *
 * @public @memberof CowlParser
 */
COWL_PUBLIC
void cowl_parser_release(CowlParser *parser);

/**
 * Sets the imports loader.
 *
 * @param parser The parser.
 * @param loader The imports loader.
 *
 * @public @memberof CowlParser
 */
COWL_PUBLIC
void cowl_parser_set_imports_loader(CowlParser *parser, CowlImportsLoader loader);

/**
 * Sets the error handler.
 *
 * @param parser The parser.
 * @param handler The error handler.
 *
 * @public @memberof CowlParser
 */
COWL_PUBLIC
void cowl_parser_set_error_handler(CowlParser *parser, CowlErrorHandler handler);

/**
 * Parses an ontology from the file at the specified path.
 *
 * @param parser The parser.
 * @param path The file path.
 * @return The parsed ontology, or NULL on error.
 *
 * @public @memberof CowlParser
 */
COWL_PUBLIC
CowlOntology* cowl_parser_parse_ontology(CowlParser *parser, char const *path);

COWL_END_DECLS

#endif // COWL_PARSER_H
