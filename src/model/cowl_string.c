/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_string_private.h"
#include "cowl_hash_utils.h"
#include "cowl_macros.h"

UHASH_IMPL(CowlStringTable, cowl_string_hash, cowl_string_equals)
static UHash(CowlStringTable) *str_tbl = NULL;
static CowlString *empty = NULL;

cowl_ret_t cowl_string_api_init(void) {
    str_tbl = uhset_alloc(CowlStringTable);
    empty = cowl_string_from_static("");
    return (str_tbl && empty) ? COWL_OK : COWL_ERR_MEM;
}

void cowl_string_api_deinit(void) {
    cowl_string_release(empty);
    uhash_free(CowlStringTable, str_tbl);
}

CowlString* cowl_string_alloc(CowlRawString raw_string) {
    if (cowl_raw_string_is_null(raw_string)) return NULL;
    CowlString *string = cowl_alloc(string);
    if (string) *string = cowl_string_init(raw_string);
    return string;
}

CowlString cowl_string_init(CowlRawString raw_string) {
    cowl_uint_t shash = cowl_raw_string_is_null(raw_string) ? 0 : cowl_raw_string_hash(raw_string);
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_STRING, raw_string.length, shash);

    CowlString init = {
        .super = COWL_HASH_OBJECT_INIT(COWL_OT_STRING, hash),
        .raw_string = raw_string
    };

    return init;
}

static void cowl_string_free(CowlString *string) {
    if (!string) return;
    cowl_raw_string_deinit(string->raw_string);
    cowl_free(string);
}

CowlString* cowl_string_get_intern(CowlString *string, bool copy) {
    if (!(string && string->raw_string.length)) return cowl_string_get_empty();

    uhash_uint_t idx;
    uhash_ret_t ret = uhash_put(CowlStringTable, str_tbl, string, &idx);

    if (ret == UHASH_INSERTED) {
        if (copy) {
            string = cowl_string_copy(string);
            if (string) {
                uhash_key(str_tbl, idx) = string;
            } else {
                uhash_delete(CowlStringTable, str_tbl, idx);
            }
        }
    } else if (ret == UHASH_PRESENT) {
        string = uhash_key(str_tbl, idx);
        (void)cowl_object_retain(string);
    } else {
        string = NULL;
    }

    return string;
}

CowlString* cowl_string_copy(CowlString *string) {
    CowlString *copy = cowl_alloc(copy);
    if (!copy) return NULL;

    cowl_uint_t hash = cowl_object_hash_get(string);
    copy->super = COWL_HASH_OBJECT_INIT(COWL_OT_STRING, hash);
    copy->raw_string = cowl_raw_string_copy(string->raw_string);

    return copy;
}

cowl_ret_t cowl_string_split_two(CowlRawString string, cowl_uint_t lhs_length, CowlString **out) {
    CowlString *lhs, *rhs;

    if (lhs_length < string.length) {
        lhs = cowl_string_get(string.cstring, lhs_length, true);
        rhs = cowl_string_get(string.cstring + lhs_length, string.length - lhs_length, true);
    } else {
        lhs = cowl_string_get(string.cstring, string.length, true);
        rhs = cowl_string_get_empty();
    }

    cowl_ret_t ret;

    if (lhs && rhs) {
        ret = COWL_OK;
    } else {
        cowl_string_release(lhs);
        cowl_string_release(rhs);
        lhs = NULL;
        rhs = NULL;
        ret = COWL_ERR_MEM;
    }

    out[0] = lhs;
    out[1] = rhs;
    return ret;
}

CowlString* cowl_string_get(char const *cstring, size_t length, bool copy) {
    CowlRawString raw_string = cowl_raw_string_init(cstring, length, copy);
    return cowl_string_alloc(raw_string);
}

CowlString* cowl_string_get_empty(void) {
    return cowl_string_retain(empty);
}

CowlString* cowl_string_retain(CowlString *string) {
    return cowl_object_retain(string);
}

void cowl_string_release(CowlString *string) {
    if (string && !cowl_object_release(string)) {
        // If the string was interned, it must also be removed from the hash set.
        uhash_uint_t k = uhash_get(CowlStringTable, str_tbl, string);
        if (k != UHASH_INDEX_MISSING && uhash_key(str_tbl, k) == string) {
            uhash_delete(CowlStringTable, str_tbl, k);
        }
        cowl_string_free(string);
    }
}

char const* cowl_string_release_copying_cstring(CowlString *string) {
    if (!string) return NULL;
    char const *cstring;

    if (cowl_object_release(string)) {
        cstring = cowl_strdup(string->raw_string.cstring, string->raw_string.length);
    } else {
        cstring = string->raw_string.cstring;
        string->raw_string.cstring = NULL;
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
