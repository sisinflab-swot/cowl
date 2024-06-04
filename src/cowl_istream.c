/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_istream.h"
#include "cowl_any.h"
#include "cowl_error_handler.h"
#include "cowl_istream_handlers.h"
#include "cowl_istream_private.h"
#include "cowl_iterator.h"
#include "cowl_manager.h"
#include "cowl_object.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_ontology.h"
#include "cowl_ontology_private.h"
#include "cowl_ret.h"
#include "cowl_vector.h"
#include "ulib.h"
#include <stdio.h>

CowlIStream *cowl_istream(CowlManager *manager, CowlSymTable *st, CowlIStreamHandlers handlers) {
    CowlIStream *stream = ulib_alloc(stream);
    if (!stream) return NULL;

    *stream = (CowlIStream){
        .super = COWL_OBJECT_INIT(COWL_OT_ISTREAM),
        .manager = cowl_retain(manager),
        .st = cowl_retain(st),
        .handlers = handlers,
    };

    return stream;
}

void cowl_istream_free(CowlIStream *stream) {
    cowl_release(stream->manager);
    cowl_release(stream->st);
    ulib_free(stream);
}

CowlManager *cowl_istream_get_manager(CowlIStream *stream) {
    return stream->manager;
}

CowlSymTable *cowl_istream_get_sym_table(CowlIStream *stream) {
    return stream->st;
}

cowl_ret cowl_istream_handle_iri(CowlIStream *stream, CowlIRI *iri) {
    CowlIStreamHandlers handle = stream->handlers;
    return handle.iri ? handle.iri(handle.ctx, iri) : COWL_OK;
}

cowl_ret cowl_istream_handle_version(CowlIStream *stream, CowlIRI *version) {
    CowlIStreamHandlers handle = stream->handlers;
    return handle.version ? handle.version(handle.ctx, version) : COWL_OK;
}

cowl_ret cowl_istream_handle_import(CowlIStream *stream, CowlIRI *import) {
    CowlIStreamHandlers handle = stream->handlers;
    return handle.import ? handle.import(handle.ctx, import) : COWL_OK;
}

cowl_ret cowl_istream_handle_annot(CowlIStream *stream, CowlAnnotation *annot) {
    CowlIStreamHandlers handle = stream->handlers;
    return handle.annot ? handle.annot(handle.ctx, annot) : COWL_OK;
}

cowl_ret cowl_istream_handle_axiom(CowlIStream *stream, CowlAnyAxiom *axiom) {
    CowlIStreamHandlers handle = stream->handlers;
    return handle.axiom ? handle.axiom(handle.ctx, axiom) : COWL_OK;
}

cowl_ret cowl_istream_process_stream(CowlIStream *stream, UIStream *istream) {
    if (istream->state) return cowl_handle_stream_error(istream->state, stream);
    cowl_ret ret = cowl_manager_get_reader(stream->manager).read(istream, stream);
    if (ret) cowl_handle_error_code(ret, stream);
    return ret;
}

static cowl_ret cowl_istream_process_stream_deinit(CowlIStream *stream, UIStream *istream) {
    cowl_ret ret = cowl_istream_process_stream(stream, istream);
    ustream_ret s_ret = uistream_deinit(istream);
    if (ret == COWL_OK && s_ret) ret = cowl_handle_stream_error(s_ret, stream);
    return ret;
}

cowl_ret cowl_istream_process_path(CowlIStream *stream, UString path) {
    UIStream istream;
    uistream_from_path(&istream, ustring_data(path));
    cowl_ret ret = cowl_istream_process_stream_deinit(stream, &istream);
    if (ret) cowl_handle_path_error(path, ustring_literal("failed to load ontology"), stream);
    return ret;
}

cowl_ret cowl_istream_process_file(CowlIStream *stream, FILE *file) {
    UIStream istream;
    uistream_from_file(&istream, file);
    return cowl_istream_process_stream_deinit(stream, &istream);
}

cowl_ret cowl_istream_process_string(CowlIStream *stream, UString const *string) {
    UIStream istream;
    uistream_from_ustring(&istream, string);
    return cowl_istream_process_stream_deinit(stream, &istream);
}

static bool onto_stream_handle_import(void *ctx, CowlAny *import_iri) {
    void **c = ctx;
    CowlIStreamHandlers *handle = c[1];
    return (*((cowl_ret *)c[0]) = handle->import(handle->ctx, import_iri)) == COWL_OK;
}

static bool onto_stream_handle_axiom(void *ctx, CowlAny *axiom) {
    void **c = ctx;
    CowlIStreamHandlers *handle = c[1];
    return (*((cowl_ret *)c[0]) = handle->axiom(handle->ctx, axiom)) == COWL_OK;
}

cowl_ret cowl_istream_process_ontology(CowlIStream *stream, CowlOntology *onto) {
    cowl_ret ret = COWL_OK;
    CowlIStreamHandlers *handle = &stream->handlers;

    if (handle->iri || handle->version) {
        CowlOntologyId id = cowl_ontology_get_id(onto);
        if (handle->iri && (ret = handle->iri(handle->ctx, id.iri))) return ret;
        if (handle->version && (ret = handle->version(handle->ctx, id.version))) return ret;
    }

    if (handle->annot) {
        CowlVector *annotations = cowl_ontology_get_annot(onto);
        cowl_vector_foreach (annotations, annot) {
            if ((ret = handle->annot(handle->ctx, *annot.item))) return ret;
        }
    }

    if (handle->import) {
        void *ctx[] = { &ret, handle };
        CowlIterator iter = { ctx, onto_stream_handle_import };
        if (!cowl_ontology_iterate_import_iris(onto, &iter, false)) return ret;
    }

    if (handle->axiom) {
        void *ctx[] = { &ret, handle };
        CowlIterator iter = { ctx, onto_stream_handle_axiom };
        if (!cowl_ontology_iterate_axioms(onto, &iter, false)) return ret;
    }

    return ret;
}
