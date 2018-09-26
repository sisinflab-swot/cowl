/// @author Ivano Bilenchi

#include <string.h>

#include "cowl_string_private.h"
#include "khash_utils.h"

#pragma mark - Instance map

KHASH_MAP_UTILS_IMPL(CowlStringMap, char const*, CowlString*, kh_str_hash_func, kh_str_hash_equal);
static khash_t(CowlStringMap) *string_map = NULL;

#pragma mark - Public API

char const* cowl_string_cstring(CowlString const *string) {
    return string->cstring;
}

size_t cowl_string_length(CowlString const *string) {
    return string->length;
}

CowlString* cowl_string_get(char const *cstring, size_t length, bool owned) {
    if (!string_map) string_map = kh_init(CowlStringMap);

    CowlString *string;
    bool absent;
    khint_t idx = kh_put_key(CowlStringMap, string_map, cstring, &absent);

    if (absent) {
        if (!owned) {
            cstring = strndup(cstring, length + 1);
            kh_key(string_map, idx) = cstring;
        }
        string = cowl_string_alloc(cstring, length);
        kh_value(string_map, idx) = string;
    } else {
        string = kh_value(string_map, idx);
        string->ref_count++;
        if (owned) free((void *) cstring);
    }
    
    return string;
}

void cowl_string_release(CowlString *string) {
    if (string && !(--string->ref_count)) {
        kh_del_val(CowlStringMap, string_map, string->cstring);
        cowl_string_free(string);
    }
}

bool cowl_string_equals(CowlString const *string, CowlString const *other) {
    return string == other;
}

uint32_t cowl_string_hash(CowlString const *string) {
    return kh_ptr_hash_func(string);
}

#pragma mark - Private API

CowlString* cowl_string_alloc(char const *cstring, size_t length) {
    CowlString string_init = { .cstring = cstring, .length = length, .ref_count = 1 };
    CowlString *string = malloc(sizeof(*string));
    memcpy(string, &string_init, sizeof(*string));
    return string;
}

void cowl_string_free(CowlString *string) {
    if (!string) return;
    free((void *)string->cstring);
    free(string);
}
