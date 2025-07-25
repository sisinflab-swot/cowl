/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ostream.h"
#include "cowl_any.h"
#include "cowl_error_handler.h"
#include "cowl_iterator.h"
#include "cowl_manager_private.h"
#include "cowl_object.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_ontology_header.h"
#include "cowl_ontology_private.h"
#include "cowl_ostream_private.h"
#include "cowl_prefix_map_private.h"
#include "cowl_ret.h"
#include "cowl_vector.h"
#include "cowl_writer.h"
#include "ulib.h"
#include <stddef.h>

CowlOStream *cowl_ostream(CowlManager *manager, UOStream *stream) {
    CowlOStream *ostream = ulib_alloc(ostream);
    if (!ostream) return NULL;

    *ostream = (CowlOStream){
        .super = COWL_OBJECT_INIT(COWL_OT_OSTREAM),
        .manager = cowl_retain(manager),
        .stream = stream,
    };

    return ostream;
}

void cowl_ostream_free(CowlOStream *stream) {
    cowl_release(stream->manager);
    cowl_release(stream->pm);
    ulib_free(stream);
}

CowlManager *cowl_ostream_get_manager(CowlOStream *stream) {
    return stream->manager;
}

CowlPrefixMap *cowl_ostream_get_prefix_map(CowlOStream *stream) {
    if (!stream->pm) stream->pm = cowl_manager_new_prefix_map(stream->manager);
    return stream->pm;
}

static CowlPrefixMap *cowl_ostream_find_prefix_map(CowlOStream *stream) {
    if (stream->pm) return stream->pm;
    return cowl_manager_find_prefix_map(stream->manager);
}

static cowl_ret handle_stream_writer_not_implemented(CowlOStream *stream, char const *name) {
    UString comp[] = {
        ustring_wrap_buf(name),
        ustring_literal(" writer does not support stream serialization"),
    };
    UString desc = ustring_concat(comp, ulib_array_count(comp));
    cowl_handle_error(COWL_ERR, desc, stream);
    ustring_deinit(&desc);
    return COWL_ERR;
}

cowl_ret cowl_ostream_write_header(CowlOStream *stream, CowlOntologyHeader header) {
    CowlWriter const *w = cowl_manager_get_writer(stream->manager);
    CowlStreamWriter sw = w->stream;
    if (!sw.write_header) return handle_stream_writer_not_implemented(stream, w->name);
    CowlPrefixMap *pm = cowl_ostream_find_prefix_map(stream);
    cowl_ret ret = sw.write_header((CowlStreamState){ w->ctx, pm }, stream->stream, header);
    return cowl_handle_error_code(ret, stream);
}

cowl_ret cowl_ostream_write_axiom(CowlOStream *stream, CowlAnyAxiom *axiom) {
    CowlWriter const *w = cowl_manager_get_writer(stream->manager);
    CowlStreamWriter sw = w->stream;
    if (!sw.write_axiom) return handle_stream_writer_not_implemented(stream, w->name);
    CowlPrefixMap *pm = cowl_ostream_find_prefix_map(stream);
    cowl_ret ret = sw.write_axiom((CowlStreamState){ w->ctx, pm }, stream->stream, axiom);
    return cowl_handle_error_code(ret, stream);
}

cowl_ret cowl_ostream_write_footer(CowlOStream *stream) {
    CowlWriter const *w = cowl_manager_get_writer(stream->manager);
    CowlStreamWriter sw = w->stream;
    if (!sw.write_footer) return handle_stream_writer_not_implemented(stream, w->name);
    CowlPrefixMap *pm = cowl_ostream_find_prefix_map(stream);
    cowl_ret ret = sw.write_footer((CowlStreamState){ w->ctx, pm }, stream->stream);
    return cowl_handle_error_code(ret, stream);
}

struct WriteAxiomCtx {
    cowl_ret *ret;
    CowlOStream *stream;
};

static bool axiom_writer(void *ctx, CowlAnyAxiom *axiom) {
    struct WriteAxiomCtx *actx = ctx;
    return (*actx->ret = cowl_ostream_write_axiom(actx->stream, axiom)) == COWL_OK;
}

static cowl_ret cowl_ostream_write_ontology_store(CowlOStream *stream, CowlOntology *onto) {
    CowlWriter const *w = cowl_manager_get_writer(stream->manager);
    return w->write_ontology(w->ctx, stream->stream, onto);
}

static cowl_ret cowl_ostream_write_ontology_stream(CowlOStream *stream, CowlOntology *onto) {
    CowlPrefixMap *old_pm = stream->pm;
    stream->pm = cowl_ontology_find_prefix_map(onto);

    cowl_ret ret;
    UVec(CowlObjectPtr) imports = uvec(CowlObjectPtr);

    CowlIterator iter = cowl_iterator_vec(&imports, false);
    if (!cowl_ontology_iterate_imports(onto, &iter)) {
        ret = COWL_ERR_MEM;
        goto end;
    }

    CowlOntologyHeader header = {
        .iri = cowl_ontology_get_iri(onto),
        .version = cowl_ontology_get_version(onto),
        .imports = &imports,
        .annotations = cowl_vector_get_data(cowl_ontology_get_annot(onto)),
    };
    if ((ret = cowl_ostream_write_header(stream, header))) goto end;

    struct WriteAxiomCtx ctx = { .ret = &ret, .stream = stream };
    iter.ctx = &ctx;
    iter.for_each = axiom_writer;
    if (!cowl_ontology_iterate_axioms(onto, &iter)) goto end;
    ret = cowl_ostream_write_footer(stream);

end:
    uvec_deinit(CowlObjectPtr, &imports);
    stream->pm = old_pm;
    return ret;
}

cowl_ret cowl_ostream_write_ontology(CowlOStream *stream, CowlOntology *onto) {
    cowl_ret ret = COWL_OK;
    CowlWriter const *w = cowl_manager_get_writer(stream->manager);
    if (cowl_writer_can_write_ontology(w)) {
        ret = cowl_ostream_write_ontology_store(stream, onto);
    } else if (cowl_writer_can_write_stream(w)) {
        ret = cowl_ostream_write_ontology_stream(stream, onto);
    } else {
        return cowl_handle_error(COWL_ERR, ustring_literal("Invalid writer"), stream);
    }
    return cowl_handle_error_code(ret, stream);
}
