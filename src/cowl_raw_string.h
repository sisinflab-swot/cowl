/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_RAW_STRING_H
#define COWL_RAW_STRING_H

#include "cowl_std.h"
#include "cowl_cstring.h"

#include <stdarg.h>

COWL_BEGIN_DECLS

typedef cowl_struct(CowlRawString) {
    cowl_uint length;
    char const *cstring;
} CowlRawString;

#define cowl_raw_string_init_static(CSTRING, COPY)                                                  \
    ((CowlRawString) {                                                                              \
        .length = (sizeof(CSTRING) - 1),                                                            \
        .cstring = ((COPY) ? cowl_str_dup(CSTRING, sizeof(CSTRING) - 1) : (CSTRING))                \
    })

#define cowl_raw_string_deinit(STRING) cowl_free((void *)(STRING).cstring)
#define cowl_raw_string_empty cowl_raw_string_init_static("", false)

#define cowl_raw_string_is_null(STRING) (!(STRING).cstring)
#define COWL_RAW_STRING_NULL ((CowlRawString){ .length = 0, .cstring = NULL })

CowlRawString cowl_raw_string_init(char const *cstring, size_t length, bool copy);
CowlRawString cowl_raw_string_init_cstring(char const *cstring, bool copy);
CowlRawString cowl_raw_string_copy(CowlRawString string);

CowlRawString cowl_raw_string_with_format(char const *format, ...);
CowlRawString cowl_raw_string_with_format_list(char const *format, va_list args);
CowlRawString cowl_raw_string_concat(cowl_uint count, CowlRawString const *strings);
cowl_uint cowl_raw_string_index_of(CowlRawString string, char needle);

bool cowl_raw_string_equals(CowlRawString lhs, CowlRawString rhs);
cowl_uint cowl_raw_string_hash(CowlRawString string);

COWL_END_DECLS

#endif // COWL_RAW_STRING_H
