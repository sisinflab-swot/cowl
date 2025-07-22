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
#include "cowl_reader.h"
#include "cowl_ret.h"
#include "cowl_vector.h"
#include "ulib.h"
#include <stdio.h>

CowlIStream *cowl_istream(CowlManager *manager, CowlPrefixMap *pm, CowlIStreamHandlers handlers) {
    CowlIStream *stream = ulib_alloc(stream);
    if (!stream) return NULL;

    *stream = (CowlIStream){
        .super = COWL_OBJECT_INIT(COWL_OT_ISTREAM),
        .manager = cowl_retain(manager),
        .pm = cowl_retain(pm),
        .handlers = handlers,
    };

    return stream;
}

void cowl_istream_free(CowlIStream *stream) {
    cowl_release(stream->manager);
    cowl_release(stream->pm);
    ulib_free(stream);
}

CowlManager *cowl_istream_get_manager(CowlIStream *stream) {
    return stream->manager;
}

CowlPrefixMap *cowl_istream_get_prefix_map(CowlIStream *stream) {
    return stream->pm;
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
    if (ulib_is_err(istream->state)) return cowl_handle_ulib_error(istream->state, stream);
    CowlReader const *r = cowl_manager_get_reader(stream->manager);
    cowl_ret const ret = r->read(r->ctx, istream, stream);
    return cowl_handle_error_code(ret, stream);
}

static cowl_ret cowl_istream_process_stream_deinit(CowlIStream *stream, UIStream *istream) {
    cowl_ret ret = cowl_istream_process_stream(stream, istream);
    ulib_ret const s_ret = uistream_deinit(istream);
    if (ret == COWL_OK) ret = cowl_handle_ulib_error(s_ret, stream);
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
    void **c = (void **)ctx;
    CowlIStreamHandlers *handle = c[1];
    return (*((cowl_ret *)c[0]) = handle->import(handle->ctx, import_iri)) == COWL_OK;
}

static bool onto_stream_handle_axiom(void *ctx, CowlAny *axiom) {
    void **c = (void **)ctx;
    CowlIStreamHandlers *handle = c[1];
    return (*((cowl_ret *)c[0]) = handle->axiom(handle->ctx, axiom)) == COWL_OK;
}

cowl_ret cowl_istream_process_ontology(CowlIStream *stream, CowlOntology *onto) {
    cowl_ret ret = COWL_OK;
    CowlIStreamHandlers *handle = &stream->handlers;

    if (handle->iri) {
        CowlIRI *iri = cowl_ontology_get_iri(onto);
        if (iri && (ret = handle->iri(handle->ctx, iri))) return ret;
    }

    if (handle->version) {
        CowlIRI *version = cowl_ontology_get_version(onto);
        if (version && (ret = handle->version(handle->ctx, version))) return ret;
    }

    if (handle->annot) {
        CowlVector *annotations = cowl_ontology_get_annot(onto);
        cowl_vector_foreach (annotations, annot) {
            if ((ret = handle->annot(handle->ctx, *annot.item))) return ret;
        }
    }

    if (handle->import) {
        void *ctx[] = { &ret, handle };
        CowlIterator iter = { (void *)ctx, onto_stream_handle_import };
        if (!cowl_ontology_iterate_imports(onto, &iter)) return ret;
    }

    if (handle->axiom) {
        void *ctx[] = { &ret, handle };
        CowlIterator iter = { (void *)ctx, onto_stream_handle_axiom };
        if (!cowl_ontology_iterate_axioms(onto, &iter)) return ret;
    }

    return ret;
}
