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
#include "cowl_config_private.h"
#include "cowl_cstring.h"
#include "cowl_iri.h"
#include "cowl_manager_private.h"
#include "cowl_ontology.h"
#include "cowl_reader.h"
#include "cowl_string_private.h"

#define UINT_MAX_DIGITS 20

cowl_ret cowl_write(UOStream *stream, CowlAny *object) {
    CowlWriter writer = cowl_get_writer();
    if (writer.write) return writer.write(stream, object);
    return cowl_ret_from_ustream(cowl_write_debug(stream, object));
}

ustream_ret cowl_write_debug(UOStream *s, CowlAny *obj) {
    uostream_writef(s, NULL, "<CowlObject %p, type ", obj);
    cowl_write_object_type(s, cowl_get_type(obj));
    cowl_write_static(s, ", ref ");
    cowl_write_uint(s, cowl_object_get_ref(obj));
    cowl_write_static(s, ">");
    return s->state;
}

ustream_ret cowl_write_string(UOStream *stream, CowlString *string) {
    return uostream_write_string(stream, &string->raw_string, NULL);
}

ustream_ret cowl_write_iri(UOStream *stream, CowlIRI *iri) {
    cowl_write_string(stream, cowl_iri_get_ns(iri));
    cowl_write_string(stream, cowl_iri_get_rem(iri));
    return stream->state;
}

ustream_ret cowl_write_uint(UOStream *stream, ulib_uint uint) {
    char buf[UINT_MAX_DIGITS + 1];
    size_t len = cowl_str_from_uint(uint, buf);
    return uostream_write(stream, buf, len, NULL);
}

ustream_ret cowl_write_object_type(UOStream *s, CowlObjectType type) {
    UString val = cowl_object_type_to_ustring(type);
    cowl_write_ustring(s, &val);

    if (!cowl_enum_value_is_valid(OT, type)) {
        cowl_write_static(s, "(");
        cowl_write_uint(s, type);
        cowl_write_static(s, ")");
    }

    return s->state;
}

ustream_ret cowl_write_error(UOStream *s, CowlError const *error) {
    cowl_write_static(s, "Error ");
    cowl_write_uint(s, error->code);

    if (error->origin) {
        cowl_write_static(s, " - triggered by ");

        switch (cowl_get_type(error->origin)) {
            case COWL_OT_MANAGER: {
                CowlReader reader = cowl_manager_get_reader((CowlManager *)error->origin);
                char const *name = reader.name ? reader.name : "unnamed";
                uostream_write(s, name, strlen(name), NULL);
                cowl_write_static(s, " reader");
                break;
            }
            case COWL_OT_ONTOLOGY: {
                CowlOntology *onto = error->origin;
                cowl_write_static(s, "ontology ");
                cowl_write_iri(s, cowl_ontology_get_id(onto).iri);
                break;
            }
            default: {
                cowl_write_debug(s, error->origin);
                break;
            }
        }
    }

    if (error->code == COWL_ERR_SYNTAX) {
        CowlSyntaxError const *se = (CowlSyntaxError *)error;

        if (se->loc.source || se->loc.line) {
            cowl_write_static(s, " (");

            if (se->loc.source) {
                cowl_write_string(s, se->loc.source);
                cowl_write_static(s, ", ");
            }

            if (se->loc.line) {
                cowl_write_static(s, "line ");
                cowl_write_uint(s, se->loc.line);
            }

            cowl_write_static(s, ")");
        }
    }

    cowl_write_static(s, " - ");

    UString str = cowl_ret_to_ustring(error->code);
    cowl_write_ustring(s, &str);

    if (error->description) {
        cowl_write_static(s, ": ");
        cowl_write_string(s, error->description);
    }

    return s->state;
}
