/// @author Ivano Bilenchi

#ifndef COWL_RAW_STRING_H
#define COWL_RAW_STRING_H

#include "cowl_std.h"

#include <stdarg.h>

COWL_BEGIN_DECLS

typedef cowl_struct(CowlRawString) {
    cowl_uint_t length;
    char const *cstring;
} CowlRawString;

#define cowl_raw_string_init_static(CSTRING, COPY)                                                  \
    ((CowlRawString) {                                                                              \
        .length = (sizeof(CSTRING) - 1),                                                            \
        .cstring = ((COPY) ? strndup(CSTRING, sizeof(CSTRING) - 1) : (CSTRING))                     \
    })

#define cowl_raw_string_deinit(STRING) free((void *)(STRING).cstring)

CowlRawString cowl_raw_string_init(char const *cstring, cowl_uint_t length, bool copy);
CowlRawString cowl_raw_string_init_cstring(char const *cstring, bool copy);

bool cowl_raw_string_equals(CowlRawString lhs, CowlRawString rhs);
cowl_uint_t cowl_raw_string_hash(CowlRawString string);

CowlRawString cowl_raw_string_with_format(char const *format, ...);
CowlRawString cowl_raw_string_with_format_list(char const *format, va_list args);
CowlRawString cowl_raw_string_concat(cowl_uint_t count, CowlRawString const *strings);


COWL_END_DECLS

#endif // COWL_RAW_STRING_H
