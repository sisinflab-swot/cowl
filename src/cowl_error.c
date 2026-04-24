/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2026 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_error.h"
#include "cowl_object_private.h"
#include "cowl_ret.h"
#include "cowl_writer.h"
#include "ulib.h"
#include <stdarg.h>

CowlError cowl_error(cowl_ret code, char const *fmt, ...) {
    CowlError error = { .code = code, .message = ustring_null };

    if (fmt) {
        va_list args;
        va_start(args, fmt);
        error.message = ustring_with_format_list(fmt, args);
        va_end(args);
    }

    return error;
}

static ulib_ret write_error(UOStream *stream, void *error) {
    return cowl_write_error(stream, error);
}

UString cowl_error_to_string(CowlError const *error) {
    return cowl_to_string_impl((void *)error, write_error);
}
