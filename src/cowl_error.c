/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_error.h"
#include "cowl_string.h"
#include "cowl_writer.h"
#include "ulib.h"

CowlString *cowl_error_to_string(CowlError const *error) {
    return cowl_string(cowl_error_to_ustring(error));
}

UString cowl_error_to_ustring(CowlError const *error) {
    UOStream stream;
    UStrBuf buf = ustrbuf();
    if (uostream_to_strbuf(&stream, &buf) || cowl_write_error(&stream, error)) goto err;

    UString string = ustrbuf_to_ustring(&buf);
    uostream_deinit(&stream);
    return string;

err:
    uostream_deinit(&stream);
    ustrbuf_deinit(&buf);
    return ustring_null;
}
