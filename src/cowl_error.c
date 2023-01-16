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

CowlString *cowl_error_to_string(CowlError const *error) {
    UOStream stream;
    UStrBuf buf = ustrbuf();
    if (uostream_to_strbuf(&stream, &buf) || cowl_write_error(&stream, error)) goto err;

    CowlString *string = cowl_string(ustrbuf_to_ustring(&buf));
    uostream_deinit(&stream);
    return string;

err:
    uostream_deinit(&stream);
    ustrbuf_deinit(&buf);
    return NULL;
}
