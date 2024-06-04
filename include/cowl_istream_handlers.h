/**
 * Defines CowlIStreamHandlers and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ISTREAM_HANDLERS_H
#define COWL_ISTREAM_HANDLERS_H

#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_macros.h"
#include "cowl_ret.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlIRI);
/// @endcond

/// Ontology input stream handlers.
typedef struct CowlIStreamHandlers {

    /// Stream context, can be anything.
    void *ctx;

    /**
     * Pointer to a function that handles the specified ontology IRI.
     *
     * @param ctx Stream context.
     * @param iri The ontology IRI.
     * @return Return code.
     */
    cowl_ret (*iri)(void *ctx, CowlIRI *iri);

    /**
     * Pointer to a function that handles the specified version IRI.
     *
     * @param ctx Stream context.
     * @param version The version IRI.
     * @return Return code.
     */
    cowl_ret (*version)(void *ctx, CowlIRI *version);

    /**
     * Pointer to a function that handles the specified import IRI.
     *
     * @param ctx Stream context.
     * @param import The import IRI.
     * @return Return code.
     */
    cowl_ret (*import)(void *ctx, CowlIRI *import);

    /**
     * Pointer to a function that handles the specified annotation.
     *
     * @param ctx Stream context.
     * @param annot The annotation.
     * @return Return code.
     */
    cowl_ret (*annot)(void *ctx, CowlAnnotation *annot);

    /**
     * Pointer to a function that handles the specified axiom.
     *
     * @param ctx Stream context.
     * @param axiom The axiom.
     * @return Return code.
     */
    cowl_ret (*axiom)(void *ctx, CowlAnyAxiom *axiom);

} CowlIStreamHandlers;

COWL_END_DECLS

#endif // COWL_ISTREAM_HANDLERS_H
