/**
 * Defines CowlImportsLoader and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_IMPORTS_LOADER_H
#define COWL_IMPORTS_LOADER_H

#include "cowl_error.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlOntology);
/// @endcond

/**
 * Provides a mechanism for generic handling of [ontology imports].
 *
 * By providing an instance to the parser (via cowl_parser_set_imports_loader())
 * you can support loading ontologies imported by the root ontology. Essentially,
 * the CowlImportsLoader::load_ontology function should return the ontology
 * having the specified CowlIRI. Imports retrieval and loading is deliberately
 * left to the implementor.
 *
 * [ontology imports]: https://www.w3.org/TR/owl2-syntax/#Imports
 *
 * @see @ref ex-errors-imports
 */
typedef cowl_struct(CowlImportsLoader) {

    /// Loader context, can be anything.
    void *ctx;

    /**
     * Pointer to a function that returns the ontology having the specified IRI.
     * @param ctx Loader context.
     * @param iri IRI of the ontology to load.
     * @param[out] errors Errors loading the imported ontology should be appended here.
     * @return The imported ontology.
     */
    CowlOntology* (*load_ontology)(void *ctx, CowlIRI *iri, Vector(CowlError) *errors);

    /**
     * Pointer to a resource deallocator function for the context,
     * called when the parser is destroyed.
     *
     * @param ctx Loader context.
     *
     * @note Can be NULL if the context does not need to release resources.
     */
    void (*free)(void *ctx);

} CowlImportsLoader;

/**
 * Initializes a new imports loader.
 *
 * @param CTX Loader context.
 * @param LOAD_FUNC Pointer to a function that returns the ontology having the specified IRI.
 * @param FREE_FUNC Pointer to a resource deallocator function for the context.
 * @return Imports loader instance.
 *
 * @see CowlImportsLoader for the types.
 *
 * @public @related CowlImportsLoader
 */
#define cowl_imports_loader_init(CTX, LOAD_FUNC, FREE_FUNC) \
    ((CowlImportsLoader){ .ctx = (CTX), .load_ontology = (LOAD_FUNC), .free = (FREE_FUNC)})

COWL_END_DECLS

#endif // COWL_IMPORTS_LOADER_H
