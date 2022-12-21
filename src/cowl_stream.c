/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_stream_private.h"
#include "cowl_manager.h"
#include "cowl_ontology_private.h"

static CowlStream* cowl_stream_alloc(CowlManager *manager, CowlSymTable *st, CowlStreamConfig cfg) {
    bool free_st = false;

    if (!st) {
        if (!(st = ulib_alloc(st))) return NULL;
        *st = cowl_sym_table_init();
        free_st = true;
    }

    CowlStream *stream = ulib_alloc(stream);
    if (!stream) return NULL;

    *stream = (CowlStream) {
        .super = COWL_OBJECT_BIT_INIT(COWL_OT_STREAM, free_st),
        .manager = cowl_manager_retain(manager),
        .st = st,
        .config = cfg
    };

    return stream;
}

CowlStream* cowl_stream(CowlManager *manager, CowlStreamConfig config) {
    return cowl_stream_alloc(manager, NULL, config);
}

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

CowlStream* cowl_stream_to_ontology(CowlOntology *onto) {
    CowlStreamConfig cfg = {
        .ctx = onto,
        .handle_iri = store_iri,
        .handle_version = store_version,
        .handle_import = store_import,
        .handle_annot = store_annot,
        .handle_axiom = store_axiom
    };
    return cowl_stream_alloc(onto->manager, &onto->st, cfg);
}

void cowl_stream_release(CowlStream *stream) {
    if (!stream || cowl_object_decr_ref(stream)) return;
    if (cowl_object_bit_get(stream)) {
        cowl_sym_table_deinit(stream->st);
        ulib_free(stream->st);
    }
    cowl_manager_release(stream->manager);
    ulib_free(stream);
}

CowlManager* cowl_stream_get_manager(CowlStream *stream) {
    return stream->manager;
}

CowlSymTable* cowl_stream_get_sym_table(CowlStream *stream) {
    return stream->st;
}

cowl_ret cowl_stream_push_iri(CowlStream *stream, CowlIRI *iri) {
    if (!stream->config.handle_iri) return COWL_OK;
    return stream->config.handle_iri(stream->config.ctx, iri);
}

cowl_ret cowl_stream_push_version(CowlStream *stream, CowlIRI *version) {
    if (!stream->config.handle_version) return COWL_OK;
    return stream->config.handle_version(stream->config.ctx, version);
}

cowl_ret cowl_stream_push_import(CowlStream *stream, CowlIRI *import) {
    if (!stream->config.handle_import) return COWL_OK;
    return stream->config.handle_import(stream->config.ctx, import);
}

cowl_ret cowl_stream_push_annot(CowlStream *stream, CowlAnnotation *annot) {
    if (!stream->config.handle_annot) return COWL_OK;
    return stream->config.handle_annot(stream->config.ctx, annot);
}

cowl_ret cowl_stream_push_axiom(CowlStream *stream, CowlAnyAxiom *axiom) {
    if (!stream->config.handle_axiom) return COWL_OK;
    return stream->config.handle_axiom(stream->config.ctx, axiom);
}
