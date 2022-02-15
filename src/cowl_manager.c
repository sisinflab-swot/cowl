/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_manager_private.h"
#include "cowl_config_private.h"
#include "cowl_error_handler_private.h"
#include "cowl_import_loader_private.h"
#include "cowl_ontology_private.h"
#include "cowl_parser_ctx_private.h"

static CowlManager* cowl_manager_alloc() {
    CowlManager *manager = ulib_alloc(manager);
    if (manager) *manager = (CowlManager) {
        .super = COWL_OBJECT_INIT(COWL_OT_MANAGER),
        .parser = { .name = NULL }
    };
    return manager;
}

static void cowl_manager_free(CowlManager *manager) {
    cowl_import_loader_deinit(manager->loader);
    cowl_error_handler_deinit(manager->handler);
    ulib_free(manager);
}

CowlManager* cowl_manager_get(void) {
    return cowl_manager_alloc();
}

CowlManager* cowl_manager_retain(CowlManager *manager) {
    return cowl_object_incr_ref(manager);
}

void cowl_manager_release(CowlManager *manager) {
    if (manager && !cowl_object_decr_ref(manager)) {
        cowl_manager_free(manager);
    }
}

static CowlOntology* cowl_parser_ctx_read_stream(CowlParserCtx *ctx, UIStream *stream) {
    if (!stream) goto end;
    ctx->ontology = cowl_ontology_get();

    if (!ctx->ontology) {
        cowl_parser_ctx_handle_error_type(ctx, COWL_ERR_MEM);
        goto end;
    }

    CowlParser parser = ctx->manager->parser.name ? ctx->manager->parser : cowl_api_get_parser();

    if (parser.alloc && !(ctx->state = parser.alloc())) {
        cowl_parser_ctx_handle_error_type(ctx, COWL_ERR_MEM);
        cowl_ontology_release(ctx->ontology);
        ctx->ontology = NULL;
        goto end;
    }

    if (parser.parse(ctx->state, stream, ctx)) {
        cowl_ontology_release(ctx->ontology);
        ctx->ontology = NULL;
    }

    if (parser.free) parser.free(ctx->state);

end:
    return ctx->ontology;
}

static CowlOntology* cowl_parser_ctx_read_deinit(CowlParserCtx *ctx, UIStream *stream) {
    CowlOntology *onto = cowl_parser_ctx_read_stream(ctx, stream);
    ustream_ret ret = uistream_deinit(stream);
    if (ret) cowl_parser_ctx_handle_stream_error(ctx, ret);
    return onto;
}

CowlOntology* cowl_manager_read_stream(CowlManager *manager, UIStream *stream) {
    CowlParserCtx ctx = { .manager = manager };
    return cowl_parser_ctx_read_stream(&ctx, stream);
}

CowlOntology* cowl_manager_read_path(CowlManager *manager, UString path) {
    UIStream stream;
    ustream_ret ret = uistream_from_path(&stream, ustring_data(path));
    CowlParserCtx ctx = { .manager = manager, .description = path };

    if (ret) {
        cowl_parser_ctx_handle_stream_error(&ctx, ret);
        return NULL;
    }

    return cowl_parser_ctx_read_deinit(&ctx, &stream);
}

CowlOntology* cowl_manager_read_file(CowlManager *manager, FILE *file) {
    UIStream stream;
    ustream_ret ret = uistream_from_file(&stream, file);
    CowlParserCtx ctx = { .manager = manager };

    if (ret) {
        cowl_parser_ctx_handle_stream_error(&ctx, ret);
        return NULL;
    }

    return cowl_parser_ctx_read_deinit(&ctx, &stream);
}

CowlOntology* cowl_manager_read_string(CowlManager *manager, UString const *string) {
    UIStream stream;
    ustream_ret ret = uistream_from_ustring(&stream, string);
    CowlParserCtx ctx = { .manager = manager };

    if (ret) {
        cowl_parser_ctx_handle_stream_error(&ctx, ret);
        return NULL;
    }

    return cowl_parser_ctx_read_deinit(&ctx, &stream);
}

void cowl_manager_set_parser(CowlManager *manager, CowlParser parser) {
    manager->parser = parser;
}

void cowl_manager_set_import_loader(CowlManager *manager, CowlImportLoader loader) {
    manager->loader = loader;
}

void cowl_manager_set_error_handler(CowlManager *manager, CowlErrorHandler handler) {
    manager->handler = handler;
}
