/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_reader_private.h"
#include "cowl_config_private.h"
#include "cowl_error_handler_private.h"
#include "cowl_import_loader_private.h"
#include "cowl_ontology_private.h"
#include "cowl_parser_ctx_private.h"

#define cowl_parser_is_null(p) (!(p).name)

static CowlReader* cowl_reader_alloc(CowlParser parser) {
    CowlReader *reader = ulib_alloc(reader);
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
    ulib_free(reader);
}

CowlReader* cowl_reader_get(void) {
    return cowl_reader_alloc((CowlParser){0});
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
    CowlOntology *onto = NULL;
    if (!reader->stream || cowl_parser_is_null(reader->parser)) goto end;

    CowlParser parser = reader->parser;
    CowlParserCtx *ctx = (CowlParserCtx *)reader;
    onto = cowl_ontology_get();

    if (!onto) {
        cowl_parser_ctx_handle_error_type(ctx, COWL_ERR_MEM);
        goto end;
    }

    void *state = NULL;

    if (parser.alloc && !(state = parser.alloc())) {
        cowl_parser_ctx_handle_error_type(ctx, COWL_ERR_MEM);
        cowl_ontology_release(onto);
        goto end;
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

end:
    reader->stream_description = NULL;

    return onto;
}

static CowlOntology* cowl_reader_read_deinit(CowlReader *reader) {
    CowlOntology *onto = cowl_reader_read(reader);
    ustream_ret ret = uistream_deinit(reader->stream);
    if (ret) cowl_parser_ctx_handle_stream_error((CowlParserCtx *)reader, ret);
    reader->stream = NULL;
    return onto;
}

CowlOntology* cowl_reader_read_path(CowlReader *reader, char const *path) {
    UIStream stream;
    reader->stream = &stream;
    reader->stream_description = path;

    ustream_ret ret = uistream_from_path(reader->stream, path);

    if (ret) {
        cowl_parser_ctx_handle_stream_error((CowlParserCtx *)reader, ret);
        reader->stream = NULL;
        return NULL;
    }

    return cowl_reader_read_deinit(reader);
}

CowlOntology* cowl_reader_read_file(CowlReader *reader, FILE *file) {
    UIStream stream;
    reader->stream = &stream;

    ustream_ret ret = uistream_from_file(reader->stream, file);

    if (ret) {
        cowl_parser_ctx_handle_stream_error((CowlParserCtx *)reader, ret);
        reader->stream = NULL;
        return NULL;
    }

    return cowl_reader_read_deinit(reader);
}

CowlOntology* cowl_reader_read_cstring(CowlReader *reader, char const *cstring, size_t length) {
    UIStream stream;
    reader->stream = &stream;

    ustream_ret ret = uistream_from_buf(reader->stream, (char *)cstring, length);

    if (ret) {
        cowl_parser_ctx_handle_stream_error((CowlParserCtx *)reader, ret);
        reader->stream = NULL;
        return NULL;
    }

    return cowl_reader_read_deinit(reader);
}

CowlOntology* cowl_reader_read_stream(CowlReader *reader, UIStream const *stream) {
    reader->stream = (UIStream *)stream;
    return cowl_reader_read(reader);
}

void cowl_reader_set_import_loader(CowlReader *reader, CowlImportLoader loader) {
    reader->loader = loader;
}

void cowl_reader_set_error_handler(CowlReader *reader, CowlErrorHandler handler) {
    reader->handler = handler;
}
