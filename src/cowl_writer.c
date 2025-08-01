/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_writer.h"
#include "cowl_any.h"
#include "cowl_cstring.h"
#include "cowl_iri.h"
#include "cowl_manager.h"
#include "cowl_object.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_ontology.h"
#include "cowl_ret.h"
#include "cowl_string.h"
#include "cowl_utils.h"
#include "ulib.h"
#include <stddef.h>
#include <string.h>

#define UINT_MAX_DIGITS 20 // NOLINT(modernize-macro-to-enum)

CowlWriter p_cowl_writer_invalid(void) {
    return (CowlWriter){ 0 };
}

void cowl_writer_free_ctx(CowlWriter *writer) {
    if (!(writer->free && writer->ctx)) return;
    writer->free(writer->ctx);
    writer->ctx = NULL;
}

cowl_ret cowl_write(UOStream *stream, CowlAny *object) {
    CowlWriter const *w = cowl_manager_get_writer(cowl_manager_root());
    if (cowl_writer_can_write_object(w)) return w->write(w->ctx, stream, object);
    return cowl_write_debug(stream, object);
}

cowl_ret cowl_write_debug(UOStream *s, CowlAny *obj) {
    uostream_writef(s, NULL, "<CowlObject %p, type ", obj);
    cowl_write_object_type(s, cowl_get_type(obj));
    cowl_write_static(s, ", ref ");
    cowl_write_uint(s, cowl_object_get_ref(obj));
    cowl_write_static(s, ">");
    return cowl_ret_from_ulib(s->state);
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

ulib_ret cowl_write_object_type(UOStream *s, CowlObjectType type) {
    UString val = cowl_object_type_to_ustring(type);
    cowl_write_ustring(s, &val);

    if (!cowl_enum_value_is_valid(OT, type)) {
        cowl_write_static(s, "(");
        cowl_write_uint(s, type);
        cowl_write_static(s, ")");
    }

    return s->state;
}
