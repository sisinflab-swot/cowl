/// @author Ivano Bilenchi

#include "cowl_string_private.h"
#include "cowl_hash_utils.h"
#include "khash_utils.h"

#pragma mark - Private

static struct CowlString* cowl_string_alloc(char const *cstring, uint32_t length) {
    uint32_t hash = cowl_hash_2(COWL_HASH_INIT_STRING, length, kh_str_hash_func(cstring));
    CowlString init = COWL_STRING_INIT(cstring, length, hash);
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
    return cowl_string_alloc(owned ? cstring : strndup(cstring, length), length);
}

CowlString* cowl_string_retain(CowlString *string) {
    return cowl_string_ref_incr(string);
}

void cowl_string_release(CowlString *string) {
    if (string && !cowl_string_ref_decr(string)) {
        cowl_string_free(string);
    }
}

char const* cowl_string_release_copying_cstring(CowlString *string) {
    if (!string) return NULL;
    char const *cstring;

    if (cowl_string_ref_decr(string)) {
        cstring = string->cstring;
        ((struct CowlString *)string)->cstring = NULL;
        cowl_string_free(string);
    } else {
        cstring = strndup(string->cstring, string->length);
    }

    return cstring;
}

char const* cowl_string_get_cstring(CowlString *string) {
    return string->cstring;
}

uint32_t cowl_string_get_length(CowlString *string) {
    return string->length;
}

bool cowl_string_equals(CowlString *lhs, CowlString *rhs) {
    return lhs->super.hash == rhs->super.hash &&
           lhs->length == rhs->length &&
           memcmp(lhs->cstring, rhs->cstring, lhs->length) == 0;
}

uint32_t cowl_string_hash(CowlString *string) {
    return cowl_string_hash_get(string);
}

CowlString* cowl_string_concat(CowlString *lhs, CowlString *rhs) {
    uint32_t length = lhs->length + rhs->length;
    char *cstring = malloc((length + 1) * sizeof(*cstring));
    memcpy(cstring, lhs->cstring, lhs->length * sizeof(*cstring));
    memcpy(cstring + lhs->length, rhs->cstring, rhs->length * sizeof(*cstring));
    cstring[length] = '\0';
    return cowl_string_get(cstring, length, true);
}
