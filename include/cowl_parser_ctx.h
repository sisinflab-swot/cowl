/**
 * Declares CowlParserCtx and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PARSER_CTX_H
#define COWL_PARSER_CTX_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlParserCtx);
/// @endcond

/**
 * Parser context, providing helpers for building parsers.
 *
 * @struct CowlParserCtx
 */

/**
 * Sets the IRI of the parsed ontology.
 *
 * @param ctx Parser context.
 * @param iri Ontology IRI.
 *
 * @public @memberof CowlParserCtx
 */
COWL_PUBLIC
void cowl_parser_ctx_set_iri(CowlParserCtx *ctx, CowlIRI *iri);

/**
 * Sets the version IRI of the parsed ontology.
 *
 * @param ctx Parser context.
 * @param version Version IRI.
 *
 * @public @memberof CowlParserCtx
 */
COWL_PUBLIC
void cowl_parser_ctx_set_version(CowlParserCtx *ctx, CowlIRI *version);

/**
 * Adds an annotation to the parsed ontology.
 *
 * @param ctx Parser context.
 * @param annot Annotation.
 * @return Return code.
 *
 * @public @memberof CowlParserCtx
 */
COWL_PUBLIC
cowl_ret cowl_parser_ctx_add_annot(CowlParserCtx *ctx, CowlAnnotation *annot);

/**
 * Adds an import to the parsed ontology.
 *
 * @param ctx Parser context.
 * @param iri IRI of the imported ontology.
 * @return Return code.
 *
 * @public @memberof CowlParserCtx
 */
COWL_PUBLIC
cowl_ret cowl_parser_ctx_add_import(CowlParserCtx *ctx, CowlIRI *iri);

/**
 * Adds an axiom to the parsed ontology.
 *
 * @param ctx Parser context.
 * @param axiom Axiom.
 * @return Return code.
 *
 * @public @memberof CowlParserCtx
 */
COWL_PUBLIC
cowl_ret cowl_parser_ctx_add_axiom(CowlParserCtx *ctx, CowlAxiom *axiom);

/**
 * Handles the specified error through the user-provided error handler.
 *
 * @param ctx Parser context.
 * @param code Error code.
 * @param description Error description.
 *
 * @public @memberof CowlParserCtx
 */
COWL_PUBLIC
void cowl_parser_ctx_handle_error(CowlParserCtx *ctx, cowl_ret code, UString description);

/**
 * Handles a generic error with the specified code through the user-provided error handler.
 *
 * @param ctx Parser context.
 * @param code Error code.
 *
 * @public @memberof CowlParserCtx
 */
COWL_PUBLIC
void cowl_parser_ctx_handle_error_type(CowlParserCtx *ctx, cowl_ret code);

COWL_END_DECLS

#endif // COWL_PARSER_CTX_H
