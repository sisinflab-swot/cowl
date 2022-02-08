/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_parser_ctx_private.h"
#include "cowl_config_private.h"
#include "cowl_manager_private.h"
#include "cowl_ontology_private.h"
#include "cowl_string_private.h"

void cowl_parser_ctx_set_iri(CowlParserCtx *ctx, CowlIRI *iri) {
    cowl_ontology_set_iri(ctx->ontology, iri);
}

void cowl_parser_ctx_set_version(CowlParserCtx *ctx, CowlIRI *version) {
    cowl_ontology_set_version(ctx->ontology, version);
}

cowl_ret cowl_parser_ctx_add_import(CowlParserCtx *ctx, CowlIRI *iri) {
    CowlOntology *import = NULL;
    cowl_ret ret;

    if (!iri) {
        ret = COWL_ERR_MEM;
        goto err;
    }

    CowlImportLoader loader = ctx->manager->loader;
    if (!loader.load_ontology) loader = cowl_api_get_import_loader();
    if (!loader.load_ontology) return COWL_OK;

    import = loader.load_ontology(loader.ctx, iri);

    if (!import) {
        ret = COWL_ERR_IMPORT;
        goto err;
    }

    ret = cowl_ontology_add_import(ctx->ontology, import);
    cowl_ontology_release(import);

err:
    if (ret) cowl_parser_ctx_handle_error_type(ctx, ret);
    return ret;
}

cowl_ret cowl_parser_ctx_add_annot(CowlParserCtx *ctx, CowlAnnotation *annot) {
    cowl_ret ret = cowl_ontology_add_annot(ctx->ontology, annot);
    if (ret) cowl_parser_ctx_handle_error_type(ctx, ret);
    return ret;
}

cowl_ret cowl_parser_ctx_add_axiom(CowlParserCtx *ctx, CowlAxiom *axiom) {
    if (!axiom) {
        cowl_parser_ctx_handle_error_type(ctx, COWL_ERR_MEM);
        return COWL_ERR_MEM;
    }

    cowl_ret ret = cowl_ontology_add_axiom(ctx->ontology, axiom);

    if (ret) {
        cowl_parser_ctx_handle_error_type(ctx, ret);
        return ret;
    }

    return COWL_OK;
}

void cowl_parser_ctx_handle_error(CowlParserCtx *ctx, cowl_ret code, char const *description) {
    CowlManager *manager = ctx->manager;
    CowlErrorHandler handler = manager->handler;
    if (!handler.handle_error) handler = cowl_api_get_error_handler();
    if (!handler.handle_error) return;

    char const *temp = ctx->description ? ctx->description : "";
    CowlString source = cowl_string_init(ustring_wrap(temp, strlen(temp)));

    temp = description;
    CowlString descr = cowl_string_init(ustring_wrap(temp, strlen(temp)));

    CowlError error = {
        .code = code,
        .location = {
            .line = manager->parser.get_line ? manager->parser.get_line(ctx->state) : 0,
            .source = cowl_string_get_length(&source) ? &source : NULL,
            .iri = ctx->ontology ? cowl_ontology_get_id(ctx->ontology).ontology_iri : NULL,
        },
        .origin = (CowlObject *)manager,
        .description = cowl_string_get_length(&descr) ? &descr : NULL
    };

    handler.handle_error(handler.ctx, &error);
}

void cowl_parser_ctx_handle_error_type(CowlParserCtx *ctx, cowl_ret code) {
    cowl_parser_ctx_handle_error(ctx, code, cowl_ret_to_cstring(code));
}

void cowl_parser_ctx_handle_stream_error(CowlParserCtx *ctx, ustream_ret code) {
    cowl_parser_ctx_handle_error_type(ctx, cowl_ret_from_ustream(code));
}
