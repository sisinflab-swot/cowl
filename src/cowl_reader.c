/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2025 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_reader.h"
#include "cowl_change_handler.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_ontology.h"
#include "cowl_reader_private.h"
#include "cowl_ret.h"
#include "ulib.h"
#include <stdio.h>

CowlReader *cowl_reader_default(void) {
#if defined(COWL_DEFAULT_READER)
    return ULIB_MACRO_CONCAT(cowl_reader_, COWL_DEFAULT_READER)();
#elif defined(COWL_READER_FUNCTIONAL)
    return cowl_reader_functional();
#else
    return NULL;
#endif
}

CowlReader *cowl_reader(CowlReaderImpl impl) {
    CowlReader *reader = ulib_alloc(reader);
    if (!reader) return NULL;

    *reader = (CowlReader){
        .super = COWL_OBJECT_INIT(COWL_OT_READER),
        .impl = impl,
    };

    return reader;
}

CowlReaderImpl *cowl_reader_get_impl(CowlReader *reader) {
    return &reader->impl;
}

char const *cowl_reader_get_name(CowlReader *reader) {
    return reader->impl.name;
}

void cowl_reader_free(CowlReader *reader) {
    if (reader->impl.free) reader->impl.free(reader->impl.ctx);
    ulib_free(reader);
}

cowl_ret cowl_reader_read(CowlReader *reader, UIStream *stream, CowlChangeHandler handler) {
    return reader->impl.read(reader->impl.ctx, stream, handler);
}

static cowl_ret read_deinit(CowlReader *reader, UIStream *stream, CowlChangeHandler handler) {
    cowl_ret const cret = cowl_reader_read(reader, stream, handler);
    ulib_ret const uret = uistream_deinit(stream);
    return cowl_is_err(cret) ? cret : cowl_ret_from_ulib(uret);
}

cowl_ret cowl_reader_read_path(CowlReader *reader, UString path, CowlChangeHandler handler) {
    UIStream stream;
    ulib_ret const ret = uistream_from_path(&stream, ustring_data(path));
    return ulib_is_ok(ret) ? read_deinit(reader, &stream, handler) : cowl_ret_from_ulib(ret);
}

CowlOntology *cowl_reader_read_ontology(CowlReader *reader, UIStream *stream) {
    CowlOntology *onto = cowl_ontology();
    if (!onto) goto err;

    CowlChangeHandler handler = cowl_change_handler_to_ontology(onto);
    if (cowl_is_err(cowl_reader_read(reader, stream, handler))) goto err;
    return onto;

err:
    cowl_release(onto);
    return NULL;
}

CowlOntology *cowl_reader_read_ontology_at_path(CowlReader *reader, UString path) {
    CowlOntology *onto = cowl_ontology();
    if (!onto) goto err;

    CowlChangeHandler handler = cowl_change_handler_to_ontology(onto);
    if (cowl_is_err(cowl_reader_read_path(reader, path, handler))) goto err;
    return onto;

err:
    cowl_release(onto);
    return NULL;
}

cowl_ret cowl_reader_write_error(CowlReader *reader, UOStream *stream) {
    if (!reader->impl.write_error) return COWL_ERR;
    return reader->impl.write_error(reader->impl.ctx, stream);
}
