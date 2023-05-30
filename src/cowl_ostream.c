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

static cowl_ret handle_stream_writer_not_implemented(CowlOStream *stream, CowlWriter *writer) {
    UString desc = ustring_with_format("%s writer does not support stream serialization",
                                       writer->name);
    cowl_handle_error(COWL_ERR, desc, stream);
    return COWL_ERR;
}

cowl_ret cowl_ostream_write_header(CowlOStream *stream, CowlOntologyHeader header) {
    CowlWriter writer = cowl_manager_get_writer(stream->manager);

    if (!writer.stream.write_header) {
        return handle_stream_writer_not_implemented(stream, &writer);
    }

    cowl_ret ret = writer.stream.write_header(stream->stream, stream->st, header);
    if (ret) cowl_handle_error_code(ret, stream);
    return ret;
}

cowl_ret cowl_ostream_write_axiom(CowlOStream *stream, CowlAnyAxiom *axiom) {
    CowlWriter writer = cowl_manager_get_writer(stream->manager);

    if (!writer.stream.write_axiom) {
        return handle_stream_writer_not_implemented(stream, &writer);
    }

    cowl_ret ret = writer.stream.write_axiom(stream->stream, stream->st, axiom);
    if (ret) cowl_handle_error_code(ret, stream);
    return ret;
}

cowl_ret cowl_ostream_write_footer(CowlOStream *stream) {
    CowlWriter writer = cowl_manager_get_writer(stream->manager);

    if (!writer.stream.write_footer) {
        return handle_stream_writer_not_implemented(stream, &writer);
    }

    cowl_ret ret = writer.stream.write_footer(stream->stream, stream->st);
    if (ret) cowl_handle_error_code(ret, stream);
    return ret;
}

cowl_ret cowl_ostream_write_ontology(CowlOStream *stream, CowlOntology *ontology) {
    CowlWriter writer = cowl_manager_get_writer(stream->manager);
    cowl_ret ret = writer.write_ontology(stream->stream, ontology);
    if (ret) cowl_handle_error_code(ret, stream);
    return ret;
}
