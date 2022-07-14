/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_error.h"
#include "cowl_string.h"
#include "cowl_writer.h"

CowlString* cowl_error_to_string(CowlError const *error) {
    CowlString *string = NULL;
    UOStream stream;
    UStrBuf buf = ustrbuf_init();
    if (uostream_to_strbuf(&stream, &buf) == USTREAM_OK) {
        if (cowl_write_error(&stream, error) == USTREAM_OK) {
            string = cowl_string_get(ustrbuf_to_ustring(&buf));
        }
        uostream_deinit(&stream);
    }
    ustrbuf_deinit(&buf);
    return string;
}
