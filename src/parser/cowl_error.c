/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_error.h"
#include "cowl_ret_private.h"
#include "cowl_str_buf.h"

CowlString* cowl_error_to_string(CowlError const *error) {
    CowlStrBuf buf_storage = cowl_str_buf_init;
    CowlStrBuf *buf = &buf_storage;

    cowl_str_buf_append_static(buf, "Error ");
    cowl_str_buf_append_uint(buf, error->code);

    CowlErrorLoc loc = error->location;

    if (loc.iri || loc.source || loc.line) {
        cowl_str_buf_append_static(buf, " (");

        if (loc.iri) {
            cowl_str_buf_append_iri_no_brackets(buf, loc.iri);
            cowl_str_buf_append_static(buf, ", ");
        }

        if (loc.source) {
            cowl_str_buf_append_string(buf, loc.source);
            cowl_str_buf_append_static(buf, ", ");
        }

        if (loc.line) {
            cowl_str_buf_append_static(buf, "line ");
            cowl_str_buf_append_uint(buf, loc.line);
        }

        cowl_str_buf_append_static(buf, ")");
    }

    cowl_str_buf_append_static(buf, " - ");
    cowl_str_buf_append_raw_string(buf, cowl_ret_to_raw_string(error->code));

    if (error->description) {
        cowl_str_buf_append_static(buf, ": ");
        cowl_str_buf_append_string(buf, error->description);
    }

    return cowl_str_buf_to_string(buf);
}
