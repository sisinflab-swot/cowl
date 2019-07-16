/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_string_private.h"
#include "cowl_hash_utils.h"
#include "cowl_macros.h"

#include <stdio.h>

cowl_struct(CowlString)* cowl_string_alloc(CowlRawString raw_string) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_STRING, raw_string.length,
                                   cowl_raw_string_hash(raw_string));

    CowlString init = {
        .super = COWL_HASH_OBJECT_INIT(hash),
        .raw_string = raw_string
    };

    cowl_struct(CowlString) *string = malloc(sizeof(*string));
    memcpy(string, &init, sizeof(*string));
    return string;
}

static void cowl_string_free(CowlString *string) {
    if (!string) return;
    cowl_raw_string_deinit(string->raw_string);
    free((void *)string);
}

void cowl_string_split_two(char const *cstring, cowl_uint_t length,
                           char character, CowlString **out) {
    char const *chr = memchr(cstring, character, length);
    cowl_uint_t ns_length = chr ? (cowl_uint_t)(chr - cstring + 1) : length;

    if (ns_length == length) {
        out[0] = cowl_string_get(cstring, length, true);
        out[1] = cowl_string_get("", 0, true);
    } else {
        out[0] = cowl_string_get(strndup(cstring, ns_length), ns_length, false);
        out[1] = cowl_string_get(chr + 1, length - ns_length, true);
    }
}

CowlString* cowl_string_get(char const *cstring, cowl_uint_t length, bool copy) {
    CowlRawString raw_string = cowl_raw_string_init(cstring, length, copy);
    return cowl_string_alloc(raw_string);
}

CowlString* cowl_string_get_empty(void) {
    static CowlString *empty = NULL;
    if (!empty) empty = cowl_string_from_static("");
    return cowl_string_retain(empty);
}

CowlString* cowl_string_retain(CowlString *string) {
    return cowl_object_retain(string);
}

void cowl_string_release(CowlString *string) {
    if (string && !cowl_object_release(string)) {
        cowl_string_free(string);
    }
}

char const* cowl_string_release_copying_cstring(CowlString *string) {
    if (!string) return NULL;
    char const *cstring;

    if (cowl_object_release(string)) {
        cstring = strndup(string->raw_string.cstring, string->raw_string.length);
    } else {
        cstring = string->raw_string.cstring;
        ((cowl_struct(CowlString) *)string)->raw_string.cstring = NULL;
        cowl_string_free(string);
    }

    return cstring;
}

char const* cowl_string_get_cstring(CowlString *string) {
    return string->raw_string.cstring;
}

cowl_uint_t cowl_string_get_length(CowlString *string) {
    return string->raw_string.length;
}

bool cowl_string_equals(CowlString *lhs, CowlString *rhs) {
    return lhs->super.hash == rhs->super.hash &&
           cowl_raw_string_equals(lhs->raw_string, rhs->raw_string);
}

cowl_uint_t cowl_string_hash(CowlString *string) {
    return cowl_object_hash_get(string);
}

CowlString* cowl_string_with_format(char const *format, ...) {
    va_list args;
    va_start(args, format);
    CowlRawString raw_string = cowl_raw_string_with_format_list(format, args);
    va_end(args);
    return cowl_string_alloc(raw_string);
}

CowlString* cowl_string_concat(CowlString *lhs, CowlString *rhs) {
    CowlRawString comp[] = { lhs->raw_string, rhs->raw_string };
    CowlRawString cat = cowl_raw_string_concat(cowl_array_size(comp), comp);
    return cowl_string_alloc(cat);
}
