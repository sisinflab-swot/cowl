/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_import_resolver.h"
#include "cowl_manager.h"
#include "cowl_object.h"
#include <stddef.h>

static CowlOntology *default_resolve_import(void *ctx, CowlIRI *iri) {
    CowlOntology *onto = cowl_manager_retrieve_ontology(ctx, iri, NULL);
    return onto ? cowl_retain(onto) : NULL;
}

CowlImportResolver cowl_import_resolver_default(CowlManager *manager) {
    return (CowlImportResolver){
        .ctx = manager,
        .resolve_import = default_resolve_import,
    };
}
