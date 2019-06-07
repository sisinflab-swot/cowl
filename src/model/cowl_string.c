/// @author Ivano Bilenchi

#include "cowl_string_private.h"
#include "cowl_hash_utils.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

static cowl_struct(CowlString)* cowl_string_alloc(char const *cstring, cowl_uint_t length) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_STRING, length, uhash_str_hash(cstring));
    CowlString init = COWL_STRING_INIT(cstring, length, hash);
    cowl_struct(CowlString) *string = malloc(sizeof(*string));
    memcpy(string, &init, sizeof(*string));
    return string;
}

static void cowl_string_free(CowlString *string) {
    if (!string) return;
    free((void *)string->cstring);
    free((void *)string);
}

static cowl_uint_t cowl_string_length_of_formatted(char const *format, va_list argptr) {
    va_list args;
    va_copy(args, argptr);
    int res = vsnprintf(NULL, 0, format, args);
    va_end(args);

    assert(res >= 0);
    return (cowl_uint_t)res;
}

void cowl_string_split_two(char const *cstring, cowl_uint_t length,
                           char character, CowlString **out) {
    char const *chr = memchr(cstring, character, length);
    cowl_uint_t ns_length = chr ? (cowl_uint_t)(chr - cstring + 1) : length;

    if (ns_length == length) {
        out[0] = cowl_string_get(cstring, length, false);
        out[1] = cowl_string_get("", 0, false);
    } else {
        out[0] = cowl_string_get(strndup(cstring, ns_length), ns_length, true);
        out[1] = cowl_string_get(chr + 1, length - ns_length, false);
    }
}

CowlString* cowl_string_get(char const *cstring, cowl_uint_t length, bool owned) {
    return cowl_string_alloc(owned ? cstring : strndup(cstring, length), length);
}

CowlString* cowl_string_get_empty(void) {
    static CowlString *empty = NULL;
    if (!empty) empty = cowl_string_from_static("");
    return empty;
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
        cstring = strndup(string->cstring, string->length);
    } else {
        cstring = string->cstring;
        ((cowl_struct(CowlString) *)string)->cstring = NULL;
        cowl_string_free(string);
    }

    return cstring;
}

char const* cowl_string_get_cstring(CowlString *string) {
    return string->cstring;
}

cowl_uint_t cowl_string_get_length(CowlString *string) {
    return string->length;
}

bool cowl_string_equals(CowlString *lhs, CowlString *rhs) {
    return lhs->super.hash == rhs->super.hash &&
           lhs->length == rhs->length &&
           memcmp(lhs->cstring, rhs->cstring, lhs->length) == 0;
}

cowl_uint_t cowl_string_hash(CowlString *string) {
    return cowl_object_hash_get(string);
}

CowlString* cowl_string_with_format(char const *format, ...) {
    va_list args;
    va_start(args, format);

    cowl_uint_t length = cowl_string_length_of_formatted(format, args);
    size_t size = (length + 1) * sizeof(char);
    char *cstring = malloc(size);
    vsnprintf(cstring, size, format, args);

    va_end(args);
    return cowl_string_get(cstring, length, true);
}

CowlString* cowl_string_concat(CowlString *lhs, CowlString *rhs) {
    cowl_uint_t length = lhs->length + rhs->length;
    char *cstring = malloc((length + 1) * sizeof(*cstring));
    memcpy(cstring, lhs->cstring, lhs->length * sizeof(*cstring));
    memcpy(cstring + lhs->length, rhs->cstring, rhs->length * sizeof(*cstring));
    cstring[length] = '\0';
    return cowl_string_get(cstring, length, true);
}
