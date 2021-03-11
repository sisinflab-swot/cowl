/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_parser_private.h"
#include "cowl_config_private.h"
#include "cowl_error_handler_private.h"
#include "cowl_import_loader_private.h"
#include "cowl_input_stream.h"
#include "cowl_ontology_private.h"
#include "cowl_parser_ctx.h"

static CowlParser* cowl_parser_alloc(CowlSubParser const *sp) {
    CowlParser *parser = cowl_alloc(parser);
    if (!parser) return NULL;

    *parser = (CowlParser) {
        .super = COWL_OBJECT_INIT(COWL_OT_PARSER),
        .sp = sp ? sp : cowl_api_get_sub_parser()
    };

    return parser;
}

static void cowl_parser_free(CowlParser *parser) {
    if (!parser) return;
    cowl_import_loader_deinit(parser->loader);
    cowl_error_handler_deinit(parser->handler);
    cowl_free(parser);
}

CowlParser* cowl_parser_get(void) {
    return cowl_parser_alloc(NULL);
}

CowlParser* cowl_parser_get_with_subparser(CowlSubParser const *sub_parser) {
    return cowl_parser_alloc(sub_parser);
}

CowlParser* cowl_parser_retain(CowlParser *parser) {
    return cowl_object_incr_ref(parser);
}

void cowl_parser_release(CowlParser *parser) {
    if (parser && !cowl_object_decr_ref(parser)) {
        cowl_parser_free(parser);
    }
}

CowlSubParser const* cowl_parser_get_subparser(CowlParser *parser) {
    return parser->sp;
}

static CowlOntology* cowl_parser_parse(CowlParser *parser) {
    if (!(parser->stream && parser->sp)) return NULL;

    CowlParserCtx *ctx = (CowlParserCtx *)parser;
    CowlOntology *onto = cowl_ontology_get();

    if (!onto) {
        cowl_parser_ctx_handle_error_type(ctx, COWL_ERR_MEM);
        return NULL;
    }

    void *state = NULL;

    if (parser->sp->alloc && !(state = parser->sp->alloc())) {
        cowl_parser_ctx_handle_error_type(ctx, COWL_ERR_MEM);
        cowl_ontology_release(onto);
        return NULL;
    }

    parser->state = state;
    parser->ontology = onto;

    if (parser->sp->parse(state, ctx)) {
        cowl_ontology_release(onto);
        onto = NULL;
    }

    if (parser->sp->free) parser->sp->free(state);

    parser->state = NULL;
    parser->ontology = NULL;

    return onto;
}

static CowlOntology* cowl_parser_parse_deinit(CowlParser *parser) {
    CowlOntology *onto = cowl_parser_parse(parser);
    cowl_ret ret = cowl_input_stream_deinit(parser->stream);
    if (ret) cowl_parser_ctx_handle_error_type((CowlParserCtx *)parser, ret);
    parser->stream = NULL;
    return onto;
}

CowlOntology* cowl_parser_parse_path(CowlParser *parser, char const *path) {
    CowlInputStream stream;
    parser->stream = &stream;

    cowl_ret ret = cowl_input_stream_from_path(parser->stream, path);

    if (ret) {
        cowl_parser_ctx_handle_error_type((CowlParserCtx *)parser, ret);
        parser->stream = NULL;
        return NULL;
    }

    return cowl_parser_parse_deinit(parser);
}

CowlOntology* cowl_parser_parse_file(CowlParser *parser, FILE *file) {
    CowlInputStream stream;
    parser->stream = &stream;

    cowl_ret ret;

    if ((ret = cowl_input_stream_from_file(parser->stream, file))) {
        cowl_parser_ctx_handle_error_type((CowlParserCtx *)parser, ret);
        parser->stream = NULL;
        return NULL;
    }

    return cowl_parser_parse_deinit(parser);
}

CowlOntology* cowl_parser_parse_cstring(CowlParser *parser, char const *cstring, size_t length) {
    CowlInputStream stream;
    parser->stream = &stream;

    cowl_ret ret;

    if ((ret = cowl_input_stream_from_cstring(parser->stream, cstring, length))) {
        cowl_parser_ctx_handle_error_type((CowlParserCtx *)parser, ret);
        parser->stream = NULL;
        return NULL;
    }

    return cowl_parser_parse_deinit(parser);
}

CowlOntology* cowl_parser_parse_stream(CowlParser *parser, CowlInputStream const *stream) {
    parser->stream = (CowlInputStream *)stream;
    return cowl_parser_parse(parser);
}

void cowl_parser_set_import_loader(CowlParser *parser, CowlImportLoader loader) {
    parser->loader = loader;
}

void cowl_parser_set_error_handler(CowlParser *parser, CowlErrorHandler handler) {
    parser->handler = handler;
}
