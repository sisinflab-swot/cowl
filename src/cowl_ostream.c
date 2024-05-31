/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_manager_private.h"
#include "cowl_ontology.h"
#include "cowl_ostream_private.h"
#include "cowl_sym_table_private.h"

CowlOStream *cowl_ostream(CowlManager *manager, UOStream *stream) {
    CowlOStream *ostream = ulib_alloc(ostream);
    if (!ostream) return NULL;

    CowlSymTable *st = cowl_sym_table();
    if (!st) {
        ulib_free(ostream);
        return NULL;
    }

    *ostream = (CowlOStream){
        .super = COWL_OBJECT_INIT(COWL_OT_OSTREAM),
        .manager = cowl_retain(manager),
        .st = st,
        .stream = stream,
    };

    return ostream;
}

void cowl_ostream_free(CowlOStream *stream) {
    cowl_release(stream->manager);
    cowl_release(stream->st);
    ulib_free(stream);
}

CowlManager *cowl_ostream_get_manager(CowlOStream *stream) {
    return stream->manager;
}

CowlSymTable *cowl_ostream_get_sym_table(CowlOStream *stream) {
    return stream->st;
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

cowl_ret
cowl_ostream_write_header(cowl_unused CowlOStream *stream, cowl_unused CowlOntologyHeader header) {
    CowlWriter w = cowl_manager_get_writer(stream->manager);
    CowlStreamWriter writer = w.stream;

    if (!writer.write_header) {
        return handle_stream_writer_not_implemented(stream, w.name);
    }

    cowl_ret ret = writer.write_header(stream->stream, stream->st, header);
    if (ret) cowl_handle_error_code(ret, stream);
    return ret;
}

cowl_ret cowl_ostream_write_axiom(CowlOStream *stream, CowlAnyAxiom *axiom) {
    CowlWriter w = cowl_manager_get_writer(stream->manager);
    CowlStreamWriter writer = w.stream;

    if (!writer.write_axiom) {
        return handle_stream_writer_not_implemented(stream, w.name);
    }

    cowl_ret ret = writer.write_axiom(stream->stream, stream->st, axiom);
    if (ret) cowl_handle_error_code(ret, stream);
    return ret;
}

cowl_ret cowl_ostream_write_footer(CowlOStream *stream) {
    CowlWriter w = cowl_manager_get_writer(stream->manager);
    CowlStreamWriter writer = w.stream;

    if (!writer.write_footer) {
        return handle_stream_writer_not_implemented(stream, w.name);
    }

    cowl_ret ret = writer.write_footer(stream->stream, stream->st);
    if (ret) cowl_handle_error_code(ret, stream);
    return ret;
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
    cowl_ret ret;
    CowlSymTable *st = cowl_ontology_get_sym_table(onto);
    if ((ret = cowl_sym_table_merge(st, cowl_ostream_get_sym_table(stream), false))) return ret;
    CowlWriter writer = cowl_manager_get_writer(stream->manager);
    return writer.write_ontology(stream->stream, onto);
}

static cowl_ret cowl_ostream_write_ontology_stream(CowlOStream *stream, CowlOntology *onto) {
    cowl_ret ret;
    CowlSymTable *st = cowl_ostream_get_sym_table(stream);
    UVec(CowlObjectPtr) imports = uvec(CowlObjectPtr);
    if ((ret = cowl_sym_table_merge(st, cowl_ontology_get_sym_table(onto), true))) goto end;

    CowlIterator iter = cowl_iterator_vec(&imports, false);
    if (!cowl_ontology_iterate_import_iris(onto, &iter, false)) {
        ret = COWL_ERR_MEM;
        goto end;
    }

    CowlOntologyHeader header = {
        .id = cowl_ontology_get_id(onto),
        .imports = &imports,
        .annotations = cowl_vector_get_data(cowl_ontology_get_annot(onto)),
    };
    if ((ret = cowl_ostream_write_header(stream, header))) goto end;

    struct WriteAxiomCtx ctx = { .ret = &ret, .stream = stream };
    iter.ctx = &ctx;
    iter.for_each = axiom_writer;
    if (!cowl_ontology_iterate_axioms(onto, &iter, false)) goto end;
    ret = cowl_ostream_write_footer(stream);

end:
    uvec_deinit(CowlObjectPtr, &imports);
    return ret;
}

cowl_ret cowl_ostream_write_ontology(CowlOStream *stream, CowlOntology *onto) {
    cowl_ret ret = COWL_OK;
    CowlWriter writer = cowl_manager_get_writer(stream->manager);
    if (cowl_writer_can_write_ontology(&writer)) {
        ret = cowl_ostream_write_ontology_store(stream, onto);
    } else if (cowl_writer_can_write_stream(&writer)) {
        ret = cowl_ostream_write_ontology_stream(stream, onto);
    } else {
        return cowl_handle_error(COWL_ERR, ustring_literal("Invalid writer"), stream);
    }
    if (ret) cowl_handle_error_code(ret, stream);
    return ret;
}
