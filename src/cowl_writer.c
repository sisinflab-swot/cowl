/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2025 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_writer.h"
#include "cowl_any.h"
#include "cowl_config.h"
#include "cowl_cstring.h"
#include "cowl_error.h"
#include "cowl_iri.h"
#include "cowl_iterator.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_ontology_header.h"
#include "cowl_ontology_private.h"
#include "cowl_ret.h"
#include "cowl_string.h"
#include "cowl_utils.h"
#include "cowl_vector.h"
#include "cowl_writer_private.h"
#include "ulib.h"
#include <stddef.h>

enum { UINT_MAX_DIGITS = 20 };

CowlWriter *cowl_writer_default(void) {
#ifdef COWL_DEFAULT_WRITER
    return ULIB_MACRO_CONCAT(cowl_writer_, COWL_DEFAULT_WRITER)();
#elif defined(COWL_WRITER_FUNCTIONAL)
    return cowl_writer_functional();
#else
    return NULL;
#endif
}

CowlWriter *cowl_writer(CowlWriterImpl impl) {
    CowlWriter *writer = ulib_alloc(writer);
    if (!writer) return NULL;

    *writer = (CowlWriter){
        .super = COWL_OBJECT_INIT(COWL_OT_WRITER),
        .impl = impl,
    };

    return writer;
}

void cowl_writer_free(CowlWriter *writer) {
    if (writer->impl.free) writer->impl.free(writer->impl.ctx);
    ulib_free(writer);
}

char const *cowl_writer_get_name(CowlWriter *writer) {
    return writer->impl.name;
}

CowlWriterImpl *cowl_writer_get_impl(CowlWriter *writer) {
    return &writer->impl;
}

bool cowl_writer_can_write_stream(CowlWriter *writer) {
    return writer->impl.write_header && writer->impl.write_axiom && writer->impl.write_footer;
}

bool cowl_writer_can_write_object(CowlWriter *writer) {
    return writer->impl.write != NULL;
}

bool cowl_writer_can_write_ontology(CowlWriter *writer) {
    return writer->impl.write_ontology != NULL;
}

struct WriteAxiomCtx {
    CowlWriter *writer;
    UOStream *stream;
};

static cowl_ret axiom_writer(void *ctx, CowlAnyAxiom *axiom) {
    struct WriteAxiomCtx *c = ctx;
    return cowl_writer_write_axiom(c->writer, c->stream, axiom);
}

static inline cowl_ret
write_ontology_store(CowlWriter *writer, UOStream *stream, CowlOntology *onto) {
    return writer->impl.write_ontology(writer->impl.ctx, stream, onto);
}

static inline cowl_ret
write_ontology_stream(CowlWriter *writer, UOStream *stream, CowlOntology *onto) {
    CowlPrefixMap *pm = cowl_ontology_get_prefix_map(onto);

    cowl_ret ret;
    UVec(CowlObjectPtr) imports = uvec(CowlObjectPtr);

    CowlIterator iter = cowl_iterator_vec(&imports, false);
    if (cowl_is_err(ret = cowl_ontology_iterate_imports(onto, &iter))) goto end;

    CowlOntologyHeader header = {
        .pm = pm,
        .iri = cowl_ontology_get_iri(onto),
        .version = cowl_ontology_get_version(onto),
        .imports = &imports,
        .annotations = cowl_vector_get_data(cowl_ontology_get_annot(onto)),
    };
    if ((ret = cowl_writer_write_header(writer, stream, header))) goto end;

    struct WriteAxiomCtx ctx = { .writer = writer, .stream = stream };
    iter.ctx = &ctx;
    iter.for_each = axiom_writer;

    if (cowl_is_err((ret = cowl_ontology_iterate_axioms(onto, &iter)))) goto end;
    ret = cowl_writer_write_footer(writer, stream);

end:
    uvec_deinit(CowlObjectPtr, &imports);
    return ret;
}

cowl_ret cowl_writer_write_ontology(CowlWriter *writer, UOStream *stream, CowlOntology *onto) {
    if (cowl_writer_can_write_ontology(writer)) {
        return write_ontology_store(writer, stream, onto);
    }
    if (cowl_writer_can_write_stream(writer)) {
        return write_ontology_stream(writer, stream, onto);
    }
    return COWL_ERR;
}

cowl_ret cowl_writer_write_ontology_to_path(CowlWriter *writer, UString path, CowlOntology *onto) {
    UOStream stream;
    ulib_ret uret = uostream_to_path(&stream, ustring_data(path));
    if (ulib_is_err(uret)) return cowl_ret_from_ulib(uret);

    cowl_ret const cret = cowl_writer_write_ontology(writer, &stream, onto);
    uret = uostream_deinit(&stream);
    return cowl_is_err(cret) ? cret : cowl_ret_from_ulib(uret);
}

cowl_ret cowl_writer_write_header(CowlWriter *writer, UOStream *stream, CowlOntologyHeader header) {
    if (!writer->impl.write_header) return COWL_ERR;
    return writer->impl.write_header(writer->impl.ctx, stream, header);
}

cowl_ret cowl_writer_write_axiom(CowlWriter *writer, UOStream *stream, CowlAnyAxiom *axiom) {
    if (!writer->impl.write_axiom) return COWL_ERR;
    return writer->impl.write_axiom(writer->impl.ctx, stream, axiom);
}

cowl_ret cowl_writer_write_footer(CowlWriter *writer, UOStream *stream) {
    if (!writer->impl.write_footer) return COWL_ERR;
    return writer->impl.write_footer(writer->impl.ctx, stream);
}

cowl_ret cowl_writer_write(CowlWriter *writer, UOStream *stream, CowlAny *object) {
    if (!writer->impl.write) return COWL_ERR;
    return writer->impl.write(writer->impl.ctx, stream, object);
}

cowl_ret cowl_write(UOStream *stream, CowlAny *object) {
    CowlWriter *w = cowl_get_writer();
    if (w && cowl_writer_can_write_object(w)) return w->impl.write(w->impl.ctx, stream, object);
    return cowl_write_debug(stream, object);
}

cowl_ret cowl_write_debug(UOStream *stream, CowlAny *obj) {
    cowl_write_object_type(stream, cowl_get_type(obj));
    uostream_writef(stream, NULL, "(%p, rc: ", obj);
    cowl_write_uint(stream, cowl_get_ref(obj));
    cowl_write_static(stream, ")");
    return cowl_ret_from_ulib(stream->state);
}

ulib_ret cowl_write_string(UOStream *stream, CowlString *string) {
    return uostream_write_string(stream, cowl_string_get_raw(string), NULL);
}

ulib_ret cowl_write_iri(UOStream *stream, CowlIRI *iri) {
    cowl_write_string(stream, cowl_iri_get_ns(iri));
    cowl_write_string(stream, cowl_iri_get_rem(iri));
    return stream->state;
}

ulib_ret cowl_write_uint(UOStream *stream, ulib_uint uint) {
    char buf[UINT_MAX_DIGITS + 1];
    return uostream_write(stream, buf, cowl_str_from_uint(uint, buf), NULL);
}

ulib_ret cowl_write_object_type(UOStream *stream, CowlObjectType type) {
    UString val = cowl_object_type_to_ustring(type);
    cowl_write_ustring(stream, &val);

    if (!cowl_enum_value_is_valid(OT, type)) {
        cowl_write_static(stream, "(");
        cowl_write_uint(stream, type);
        cowl_write_static(stream, ")");
    }

    return stream->state;
}

ulib_ret cowl_write_error(UOStream *stream, CowlError const *error) {
    cowl_ret const code = error ? error->code : COWL_OK;
    if (cowl_is_ok(code)) return stream->state;

    UString const code_str = cowl_ret_to_ustring(code);
    cowl_write_ustring(stream, &code_str);

    if (cowl_error_has_message(error)) {
        cowl_write_static(stream, ": ");
        cowl_write_ustring(stream, &error->message);
    }

    if (cowl_error_has_loc(error)) {
        cowl_write_static(stream, " (");

        struct {
            ulib_uint value;
            char const *name;
        } const locs[] = {
            { .value = error->line, .name = "line " },
            { .value = error->col, .name = "col " },
            { .value = error->byte, .name = "byte " },
        };

        bool write_comma = false;

        for (unsigned i = 0; i < ulib_array_count(locs); ++i) {
            if (!locs[i].value) continue;
            if (write_comma) cowl_write_static(stream, ", ");
            cowl_write_cstring(stream, locs[i].name);
            cowl_write_uint(stream, locs[i].value);
            write_comma = true;
        }

        cowl_write_static(stream, ")");
    }

    return stream->state;
}
