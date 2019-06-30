/// @author Ivano Bilenchi

#include "cowl_raw_string.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

static cowl_uint_t cowl_cstring_length_of_formatted(char const *format, va_list argptr) {
    va_list args;
    va_copy(args, argptr);
    int res = vsnprintf(NULL, 0, format, args);
    va_end(args);

    assert(res >= 0);
    return (cowl_uint_t)res;
}

CowlRawString cowl_raw_string_init(char const *cstring, cowl_uint_t length, bool copy) {
    return (CowlRawString){
        .length = length,
        .cstring = copy ? strndup(cstring, length) : cstring
    };
}

CowlRawString cowl_raw_string_init_cstring(char const *cstring, bool copy) {
    return cowl_raw_string_init(cstring, strlen(cstring), copy);
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
    cowl_uint_t length = cowl_cstring_length_of_formatted(format, args);
    size_t size = (length + 1) * sizeof(char);
    char *cstring = malloc(size);
    vsnprintf(cstring, size, format, args);
    return cowl_raw_string_init(cstring, length, false);
}

CowlRawString cowl_raw_string_concat(cowl_uint_t count, CowlRawString const *strings) {
    cowl_uint_t total_length = 0;
    for (cowl_uint_t i = 0; i < count; ++i) total_length += strings[i].length;

    char *const buffer = malloc((total_length + 1) * sizeof(*buffer));
    char *buffer_ptr = buffer;

    for (cowl_uint_t i = 0; i < count; ++i) {
        CowlRawString string = strings[i];
        memcpy(buffer_ptr, string.cstring, string.length * sizeof(*buffer));
        buffer_ptr += string.length;
    }

    buffer[total_length] = '\0';
    return cowl_raw_string_init(buffer, total_length, false);
}