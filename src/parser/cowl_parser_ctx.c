/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_parser_ctx_private.h"
#include "cowl_config_private.h"
#include "cowl_input_stream.h"
#include "cowl_ontology_private.h"
#include "cowl_string_private.h"

CowlInputStream* cowl_parser_ctx_get_stream(CowlParserCtx *ctx) {
    return ((CowlReader *)ctx)->stream;
}

void cowl_parser_ctx_set_iri(CowlParserCtx *ctx, CowlIRI *iri) {
    cowl_ontology_set_iri(((CowlReader *)ctx)->ontology, iri);
}

void cowl_parser_ctx_set_version(CowlParserCtx *ctx, CowlIRI *version) {
    cowl_ontology_set_version(((CowlReader *)ctx)->ontology, version);
}

cowl_ret cowl_parser_ctx_add_import(CowlParserCtx *ctx, CowlIRI *iri) {
    CowlOntology *import = NULL;
    CowlReader *reader = ((CowlReader *)ctx);
    cowl_ret ret;

    if (!iri) {
        ret = COWL_ERR_MEM;
        goto err;
    }

    CowlImportLoader loader = reader->loader;
    if (!loader.load_ontology) loader = cowl_api_get_import_loader();
    if (!loader.load_ontology) return COWL_OK;

    import = loader.load_ontology(loader.ctx, iri);

    if (!import) {
        ret = COWL_ERR_IMPORT;
        goto err;
    }

    ret = cowl_ontology_add_import(reader->ontology, import);
    cowl_ontology_release(import);

err:
    if (ret) cowl_parser_ctx_handle_error_type(ctx, ret);
    return ret;
}

cowl_ret cowl_parser_ctx_add_annot(CowlParserCtx *ctx, CowlAnnotation *annot) {
    cowl_ret ret = cowl_ontology_add_annot(((CowlReader *)ctx)->ontology, annot);
    if (ret) cowl_parser_ctx_handle_error_type(ctx, ret);
    return ret;
}

cowl_ret cowl_parser_ctx_add_axiom(CowlParserCtx *ctx, CowlAxiom *axiom) {
    if (!axiom) {
        cowl_parser_ctx_handle_error_type(ctx, COWL_ERR_MEM);
        return COWL_ERR_MEM;
    }

    cowl_ret ret = cowl_ontology_add_axiom(((CowlReader *)ctx)->ontology, axiom);

    if (ret) {
        cowl_parser_ctx_handle_error_type(ctx, ret);
        return ret;
    }

    return COWL_OK;
}

void cowl_parser_ctx_handle_error(CowlParserCtx *ctx, cowl_ret code, char const *description) {
    CowlReader *reader = ((CowlReader *)ctx);
    CowlErrorHandler handler = reader->handler;
    if (!handler.handle_error) handler = cowl_api_get_error_handler();
    if (!handler.handle_error) return;

    char const *temp = reader->stream->description;
    CowlString source = cowl_string_init(cowl_raw_string_init(temp, strlen(temp), false));

    temp = description;
    CowlString descr = cowl_string_init(cowl_raw_string_init(temp, strlen(temp), false));

    CowlError error = {
        .code = code,
        .location = {
            .line = reader->parser.get_line ? reader->parser.get_line(reader->state) : 0,
            .source = cowl_string_get_length(&source) ? &source : NULL,
            .iri = reader->ontology ? cowl_ontology_get_id(reader->ontology).ontology_iri : NULL,
        },
        .origin = (CowlObject *)reader,
        .description = cowl_string_get_length(&descr) ? &descr : NULL
    };

    handler.handle_error(handler.ctx, &error);
}

void cowl_parser_ctx_handle_error_type(CowlParserCtx *ctx, cowl_ret code) {
    cowl_parser_ctx_handle_error(ctx, code, cowl_ret_to_cstring(code));
}
