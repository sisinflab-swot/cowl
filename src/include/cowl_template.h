/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_TEMPLATE_H
#define COWL_TEMPLATE_H

#include "cowl_std.h"
#include "cowl_stream.h"
#include "cowl_string_private.h"

COWL_BEGIN_DECLS

#define COWL_TO_STRING_IMPL(LC, VAR) {                                                              \
    CowlString *string = NULL;                                                                      \
    UOStream stream;                                                                                \
    UStrBuf buf = ustrbuf_init();                                                                   \
    if (uostream_to_strbuf(&stream, &buf) == USTREAM_OK) {                                          \
        if (cowl_stream_write_##LC(&stream, (VAR)) == USTREAM_OK) {                                 \
            string = cowl_string_alloc(ustrbuf_to_ustring(&buf));                                   \
        }                                                                                           \
        uostream_deinit(&stream);                                                                   \
    }                                                                                               \
    ustrbuf_deinit(&buf);                                                                           \
    return string;                                                                                  \
}

COWL_END_DECLS

#endif // COWL_TEMPLATE_H
