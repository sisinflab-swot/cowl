/// @author Ivano Bilenchi

#ifndef COWL_IMPORTS_LOADER_H
#define COWL_IMPORTS_LOADER_H

#include "cowl_error.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlOntology);

typedef CowlOntology* (*CowlOntologyIRI)(void *ctx, CowlIRI *iri);

typedef cowl_struct(CowlImportsLoader) {
    void *ctx;
    CowlOntology* (*load_ontology)(void *ctx, CowlIRI *iri, Vector(CowlError) *errors);
    void (*free)(void *ctx);
} CowlImportsLoader;

#define cowl_imports_loader_init(CTX, LOAD_FUNC, FREE_FUNC) \
    ((CowlImportsLoader){ .ctx = (CTX), .load_ontology = (LOAD_FUNC), .free = (FREE_FUNC)})

COWL_END_DECLS

#endif // COWL_IMPORTS_LOADER_H
