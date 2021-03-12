/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_reader_private.h"
#include "cowl_config_private.h"
#include "cowl_error_handler_private.h"
#include "cowl_import_loader_private.h"
#include "cowl_input_stream.h"
#include "cowl_ontology_private.h"
#include "cowl_parser_ctx.h"

#define cowl_parser_is_null(p) (!(p).name)

static CowlReader* cowl_reader_alloc(CowlParser parser) {
    CowlReader *reader = cowl_alloc(reader);
    if (!reader) return NULL;

    *reader = (CowlReader) {
        .super = COWL_OBJECT_INIT(COWL_OT_READER),
        .parser = cowl_parser_is_null(parser) ? cowl_api_get_parser() : parser
    };

    return reader;
}

static void cowl_reader_free(CowlReader *reader) {
    if (!reader) return;
    cowl_import_loader_deinit(reader->loader);
    cowl_error_handler_deinit(reader->handler);
    cowl_free(reader);
}

CowlReader* cowl_reader_get(void) {
    return cowl_reader_alloc((CowlParser){});
}

CowlReader* cowl_reader_get_with_parser(CowlParser parser) {
    return cowl_reader_alloc(parser);
}

CowlReader* cowl_reader_retain(CowlReader *reader) {
    return cowl_object_incr_ref(reader);
}

void cowl_reader_release(CowlReader *reader) {
    if (reader && !cowl_object_decr_ref(reader)) {
        cowl_reader_free(reader);
    }
}

static CowlOntology* cowl_reader_read(CowlReader *reader) {
    if (!reader->stream || cowl_parser_is_null(reader->parser)) return NULL;

    CowlParser parser = reader->parser;
    CowlParserCtx *ctx = (CowlParserCtx *)reader;
    CowlOntology *onto = cowl_ontology_get();

    if (!onto) {
        cowl_parser_ctx_handle_error_type(ctx, COWL_ERR_MEM);
        return NULL;
    }

    void *state = NULL;

    if (parser.alloc && !(state = parser.alloc())) {
        cowl_parser_ctx_handle_error_type(ctx, COWL_ERR_MEM);
        cowl_ontology_release(onto);
        return NULL;
    }

    reader->state = state;
    reader->ontology = onto;

    if (parser.parse(state, ctx)) {
        cowl_ontology_release(onto);
        onto = NULL;
    }

    if (parser.free) parser.free(state);

    reader->state = NULL;
    reader->ontology = NULL;

    return onto;
}

static CowlOntology* cowl_reader_read_deinit(CowlReader *reader) {
    CowlOntology *onto = cowl_reader_read(reader);
    cowl_ret ret = cowl_input_stream_deinit(reader->stream);
    if (ret) cowl_parser_ctx_handle_error_type((CowlParserCtx *)reader, ret);
    reader->stream = NULL;
    return onto;
}

CowlOntology* cowl_reader_read_path(CowlReader *reader, char const *path) {
    CowlInputStream stream;
    reader->stream = &stream;

    cowl_ret ret = cowl_input_stream_from_path(reader->stream, path);

    if (ret) {
        cowl_parser_ctx_handle_error_type((CowlParserCtx *)reader, ret);
        reader->stream = NULL;
        return NULL;
    }

    return cowl_reader_read_deinit(reader);
}

CowlOntology* cowl_reader_read_file(CowlReader *reader, FILE *file) {
    CowlInputStream stream;
    reader->stream = &stream;

    cowl_ret ret;

    if ((ret = cowl_input_stream_from_file(reader->stream, file))) {
        cowl_parser_ctx_handle_error_type((CowlParserCtx *)reader, ret);
        reader->stream = NULL;
        return NULL;
    }

    return cowl_reader_read_deinit(reader);
}

CowlOntology* cowl_reader_read_cstring(CowlReader *reader, char const *cstring, size_t length) {
    CowlInputStream stream;
    reader->stream = &stream;

    cowl_ret ret;

    if ((ret = cowl_input_stream_from_cstring(reader->stream, cstring, length))) {
        cowl_parser_ctx_handle_error_type((CowlParserCtx *)reader, ret);
        reader->stream = NULL;
        return NULL;
    }

    return cowl_reader_read_deinit(reader);
}

CowlOntology* cowl_reader_read_stream(CowlReader *reader, CowlInputStream const *stream) {
    reader->stream = (CowlInputStream *)stream;
    return cowl_reader_read(reader);
}

void cowl_reader_set_import_loader(CowlReader *reader, CowlImportLoader loader) {
    reader->loader = loader;
}

void cowl_reader_set_error_handler(CowlReader *reader, CowlErrorHandler handler) {
    reader->handler = handler;
}
