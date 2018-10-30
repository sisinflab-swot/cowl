/// @author Ivano Bilenchi

#include <string.h>

#include "cowl_string_private.h"
#include "khash_utils.h"

#pragma mark - Instance map

KHASH_MAP_UTILS_INIT(CowlStringMap, char const*, CowlString*, kh_str_hash_func, kh_str_hash_equal);
static khash_t(CowlStringMap) *inst_map = NULL;

#pragma mark - Private

static struct CowlString* cowl_string_alloc(char const *cstring, uint32_t length) {
    CowlString init = COWL_STRING_INIT(cstring, length);
    struct CowlString *string = malloc(sizeof(*string));
    memcpy(string, &init, sizeof(*string));
    return string;
}

static void cowl_string_free(CowlString *string) {
    if (!string) return;
    free((void *)string->cstring);
    free((void *)string);
}

#pragma mark - Internal

void cowl_string_split_two(char const *cstring, uint32_t length, char character, CowlString **out) {
    char const *chr = memchr(cstring, character, length);
    uint32_t ns_length = chr ? (uint32_t)(chr - cstring + 1) : length;

    if (ns_length == length) {
        out[0] = cowl_string_get(cstring, length, false);
        out[1] = cowl_string_get("", 0, false);
    } else {
        out[0] = cowl_string_get(strndup(cstring, ns_length), ns_length, true);
        out[1] = cowl_string_get(chr + 1, length - ns_length, false);
    }
}

#pragma mark - Public

CowlString* cowl_string_get(char const *cstring, uint32_t length, bool owned) {
    if (!inst_map) inst_map = kh_init(CowlStringMap);

    CowlString *string;
    bool absent;
    khint_t idx = kh_put_key(CowlStringMap, inst_map, cstring, &absent);

    if (absent) {
        if (!owned) {
            cstring = strndup(cstring, length);
            kh_key(inst_map, idx) = cstring;
        }
        string = cowl_string_alloc(cstring, length);
        kh_value(inst_map, idx) = string;
    } else {
        string = kh_value(inst_map, idx);
        cowl_string_ref_incr(string);
        if (owned) free((void *)cstring);
    }
    
    return string;
}

CowlString* cowl_string_retain(CowlString *string) {
    return cowl_string_ref_incr(string);
}

void cowl_string_release(CowlString *string) {
    if (string && !cowl_string_ref_decr(string)) {
        kh_del_val(CowlStringMap, inst_map, string->cstring);
        cowl_string_free(string);
    }
}

char const* cowl_string_get_cstring(CowlString *string) {
    return string->cstring;
}

uint32_t cowl_string_get_length(CowlString *string) {
    return string->length;
}

bool cowl_string_equals(CowlString *lhs, CowlString *rhs) {
    return lhs == rhs;
}

uint32_t cowl_string_hash(CowlString *string) {
    return kh_ptr_hash_func(string);
}
