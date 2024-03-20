/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_istream_handlers.h"
#include "cowl_ontology.h"

static cowl_ret store_iri(void *ctx, CowlIRI *iri) {
    cowl_ontology_set_iri(ctx, iri);
    return COWL_OK;
}

static cowl_ret store_version(void *ctx, CowlIRI *version) {
    cowl_ontology_set_version(ctx, version);
    return COWL_OK;
}

static cowl_ret store_import(void *ctx, CowlIRI *import) {
    return cowl_ontology_add_import(ctx, import);
}

static cowl_ret store_annot(void *ctx, CowlAnnotation *annot) {
    return cowl_ontology_add_annot(ctx, annot);
}

static cowl_ret store_axiom(void *ctx, CowlAnyAxiom *axiom) {
    return cowl_ontology_add_axiom(ctx, axiom);
}

CowlIStreamHandlers cowl_istream_handlers_to_ontology(CowlOntology *onto) {
    return (CowlIStreamHandlers){
        .ctx = onto,
        .iri = store_iri,
        .version = store_version,
        .import = store_import,
        .annot = store_annot,
        .axiom = store_axiom,
    };
}
