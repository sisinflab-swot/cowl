/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STREAM_CONFIG_H
#define COWL_STREAM_CONFIG_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlIRI);
/// @endcond

/// Ontology stream configuration.
typedef struct CowlStreamConfig {

    /// Stream context, can be anything.
    void *ctx;

    /**
     * Pointer to a function that handles the specified ontology IRI.
     *
     * @param ctx Stream context.
     * @param iri The ontology IRI.
     * @return Return code.
     */
    cowl_ret (*handle_iri)(void *ctx, CowlIRI *iri);

    /**
     * Pointer to a function that handles the specified version IRI.
     *
     * @param ctx Stream context.
     * @param version The version IRI.
     * @return Return code.
     */
    cowl_ret (*handle_version)(void *ctx, CowlIRI *version);

    /**
     * Pointer to a function that handles the specified import IRI.
     *
     * @param ctx Stream context.
     * @param import The import IRI.
     * @return Return code.
     */
    cowl_ret (*handle_import)(void *ctx, CowlIRI *import);

    /**
     * Pointer to a function that handles the specified annotation.
     *
     * @param ctx Stream context.
     * @param annot The annotation.
     * @return Return code.
     */
    cowl_ret (*handle_annot)(void *ctx, CowlAnnotation *annot);

    /**
     * Pointer to a function that handles the specified axiom.
     *
     * @param ctx Stream context.
     * @param axiom The axiom.
     * @return Return code.
     */
    cowl_ret (*handle_axiom)(void *ctx, CowlAnyAxiom *axiom);

} CowlStreamConfig;

COWL_END_DECLS

#endif // COWL_STREAM_CONFIG_H
