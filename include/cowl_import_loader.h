/**
 * Defines CowlImportLoader and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_IMPORT_LOADER_H
#define COWL_IMPORT_LOADER_H

#include "cowl_error.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlOntology);
/// @endcond

/**
 * Provides a mechanism for generic handling of [ontology imports].
 *
 * The `load_ontology` function should return the ontology that has the specified @type{#CowlIRI}.
 * Imports retrieval and loading is deliberately left to the implementor.
 *
 * [ontology imports]: https://www.w3.org/TR/owl2-syntax/#Imports
 */
typedef struct CowlImportLoader {

    /// Loader context, can be anything.
    void *ctx;

    /**
     * Pointer to a function that returns the ontology having the specified IRI.
     *
     * @param ctx Loader context.
     * @param iri IRI of the ontology to load.
     * @return The imported ontology, or NULL on error.
     */
    CowlOntology *(*load_ontology)(void *ctx, CowlIRI *iri);

    /**
     * Pointer to a resource deallocator function for the context.
     *
     * @param ctx Loader context.
     *
     * @note Can be NULL if the context does not need to release resources.
     */
    void (*free)(void *ctx);

} CowlImportLoader;

COWL_END_DECLS

#endif // COWL_IMPORT_LOADER_H
