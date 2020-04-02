/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_raw_string.h"
#include "cowl_str_buf.h"

#include <stdio.h>

CowlRawString cowl_raw_string_init(char const *cstring, size_t length, bool copy) {
    if (copy) {
        cstring = strndup(cstring, length);
        if (!cstring) length = 0;
    }

    return (CowlRawString) {
        .length = (cowl_uint_t)length,
        .cstring = cstring
    };
}

CowlRawString cowl_raw_string_init_cstring(char const *cstring, bool copy) {
    return cowl_raw_string_init(cstring, strlen(cstring), copy);
}

CowlRawString cowl_raw_string_copy(CowlRawString string) {
    return cowl_raw_string_init(string.cstring, string.length, true);
}

cowl_uint_t cowl_raw_string_index_of(CowlRawString string, char needle) {
    char const *chr = memchr(string.cstring, needle, string.length);
    return chr ? (cowl_uint_t)(chr - string.cstring) : string.length;
}

bool cowl_raw_string_equals(CowlRawString lhs, CowlRawString rhs) {
    return lhs.length == rhs.length && memcmp(lhs.cstring, rhs.cstring, lhs.length) == 0;
}

cowl_uint_t cowl_raw_string_hash(CowlRawString string) {
    #define cowl_cstring_hash_range(HASH, STR, START, END) do {                                     \
        for (uhash_uint_t i = (START); i < (END); ++i) {                                            \
            (HASH) = ((HASH) << 5u) - (HASH) + (cowl_uint_t)(STR)[i];                               \
        }                                                                                           \
    } while (0)

    cowl_uint_t const length = string.length;
    char const *cstr = string.cstring;

    cowl_uint_t const part_size = 32;
    cowl_uint_t hash = (cowl_uint_t)cstr[0];

    if (length <= 3 * part_size) {
        cowl_cstring_hash_range(hash, cstr, 1, length);
    } else {
        uhash_uint_t const half_idx = length / 2;
        uhash_uint_t const half_part_size = part_size / 2;
        cowl_cstring_hash_range(hash, cstr, 1, part_size);
        cowl_cstring_hash_range(hash, cstr, half_idx - half_part_size, half_idx + half_part_size);
        cowl_cstring_hash_range(hash, cstr, length - part_size, length);
    }

    return hash;
}

CowlRawString cowl_raw_string_with_format(char const *format, ...) {
    va_list args;
    va_start(args, format);
    CowlRawString string = cowl_raw_string_with_format_list(format, args);
    va_end(args);
    return string;
}

CowlRawString cowl_raw_string_with_format_list(char const *format, va_list args) {
    CowlStrBuf *buf = cowl_str_buf_alloc();

    if (buf && cowl_str_buf_append_format_list(buf, format, args)) {
        cowl_str_buf_free(buf);
        buf = NULL;
    }

    return cowl_str_buf_to_raw_string(buf);
}

CowlRawString cowl_raw_string_concat(cowl_uint_t count, CowlRawString const *strings) {
    CowlStrBuf *buf = cowl_str_buf_alloc();

    if (buf) {
        for (cowl_uint_t i = 0; i < count; ++i) {
            if (cowl_str_buf_append_raw_string(buf, strings[i])) {
                cowl_str_buf_free(buf);
                buf = NULL;
                break;
            }
        }
    }

    return cowl_str_buf_to_raw_string(buf);
}
