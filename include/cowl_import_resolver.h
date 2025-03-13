/**
 * Defines CowlImportResolver and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_IMPORT_RESOLVER_H
#define COWL_IMPORT_RESOLVER_H

#include "cowl_attrs.h"
#include "cowl_utils.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlManager);
cowl_struct_decl(CowlOntology);
/// @endcond

/**
 * Provides a mechanism for generic handling of [ontology imports].
 *
 * The `resolve_import` function should return the ontology associated to the specified
 * @type{#CowlIRI}. Imports retrieval and loading is deliberately left to the implementor.
 *
 * [ontology imports]: https://www.w3.org/TR/owl2-syntax/#Imports
 */
typedef struct CowlImportResolver {

    /// Resolver context, can be anything.
    void *ctx;

    /**
     * Pointer to a function that returns the ontology associated to the specified IRI.
     *
     * @param ctx Resolver context.
     * @param iri The IRI.
     * @return Imported ontology, or NULL on error.
     *
     * @note The returned ontology must be retained.
     */
    CowlOntology *(*resolve_import)(void *ctx, CowlIRI *iri);

    /**
     * Pointer to a resource deallocator function.
     *
     * @param ctx Resolver context.
     *
     * @note Can be NULL if the resolver does not need to release resources.
     */
    void (*free)(void *ctx);

} CowlImportResolver;

/**
 * Returns the ontology associated to the specified IRI.
 *
 * @param resolver The resolver.
 * @param iri The IRI.
 * @return Imported ontology, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlOntology *
cowl_import_resolver_resolve_import(CowlImportResolver const *resolver, CowlIRI *iri) {
    return resolver->resolve_import(resolver->ctx, iri);
}

/**
 * Default import resolver, which looks for the ontology with the specified IRI
 * in the manager's ontologies.
 *
 * @param manager The manager.
 * @return Default import resolver.
 *
 * @note The manager is set as the resolver context, but it is not retained.
 */
COWL_API
CowlImportResolver cowl_import_resolver_default(CowlManager *manager);

COWL_END_DECLS

#endif // COWL_IMPORT_RESOLVER_H
