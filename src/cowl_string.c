/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_string_private.h"
#include "cowl_table_private.h"
#include <stdarg.h>

static UHash(CowlObjectTable) inst_tbl;
static CowlString *empty = NULL;

static CowlString *cowl_string_get(UString raw_string, bool copy) {
    if (copy) {
        raw_string = ustring_dup(raw_string);
        if (ustring_is_null(raw_string)) return NULL;
    }

    CowlString *string = ulib_alloc(string);
    if (string) {
        *string = cowl_string_init(raw_string);
    } else {
        ustring_deinit(&raw_string);
    }
    return string;
}

static CowlString *cowl_string_get_intern(UString raw_string, bool copy) {
    CowlString *string = NULL;
    CowlString key = cowl_string_init(raw_string);

    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, &inst_tbl, &key, &idx);

    if (ret == UHASH_PRESENT) {
        string = uhash_key(CowlObjectTable, &inst_tbl, idx);
        cowl_retain(string);
        if (!copy) ustring_deinit(&raw_string);
    } else if (ret == UHASH_INSERTED) {
        string = cowl_string_get(raw_string, copy);
        if (string) {
            cowl_object_bit_set(string);
            uhash_key(CowlObjectTable, &inst_tbl, idx) = string;
        } else {
            uhash_delete(CowlObjectTable, &inst_tbl, idx);
        }
    } else if (!copy) {
        ustring_deinit(&raw_string);
    }

    return string;
}

cowl_ret cowl_string_api_init(void) {
    inst_tbl = cowl_string_map();
    empty = cowl_string_get(ustring_literal(""), true);
    return empty ? COWL_OK : COWL_ERR_MEM;
}

void cowl_string_api_deinit(void) {
    cowl_release(empty);
    uhash_deinit(CowlObjectTable, &inst_tbl);
}

CowlString cowl_string_init(UString raw_string) {
    return (CowlString){
        .super = COWL_OBJECT_INIT(COWL_OT_STRING),
        .hash = ustring_is_null(raw_string) ? 0 : ustring_hash(raw_string),
        .raw_string = raw_string,
    };
}

CowlString *cowl_string_intern(CowlString *string) {
    if (!string) return NULL;
    if (cowl_object_bit_get(string)) return string;
    if (!ustring_length(string->raw_string)) return empty;

    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, &inst_tbl, string, &idx);

    if (ret == UHASH_INSERTED) {
        cowl_object_bit_set(string);
    } else if (ret == UHASH_PRESENT) {
        string = uhash_key(CowlObjectTable, &inst_tbl, idx);
    } else {
        string = NULL;
    }

    return string;
}

CowlString *cowl_string_copy(CowlString *string) {
    CowlString *copy = ulib_alloc(copy);
    if (!copy) return NULL;

    copy->super = COWL_OBJECT_INIT(COWL_OT_STRING);
    copy->hash = string->hash;
    copy->raw_string = ustring_dup(string->raw_string);

    return copy;
}

cowl_ret cowl_string_get_ns_rem(UString string, ulib_uint ns_length, CowlString **out) {
    CowlString *rhs;
    ulib_uint const str_len = ustring_length(string);
    char const *cstring = ustring_data(string);

    if (ns_length < str_len) {
        rhs = cowl_string_opt(ustring_wrap(cstring + ns_length, str_len - ns_length), COWL_SO_COPY);
    } else {
        ns_length = str_len;
        rhs = cowl_string_empty();
    }

    UString raw_string = ustring_wrap(cstring, ns_length);
    CowlString *lhs = cowl_string_opt(raw_string, COWL_SO_COPY | COWL_SO_INTERN);
    cowl_ret ret;

    if (lhs && rhs) {
        ret = COWL_OK;
    } else {
        cowl_release(lhs);
        cowl_release(rhs);
        lhs = NULL;
        rhs = NULL;
        ret = COWL_ERR_MEM;
    }

    out[0] = lhs;
    out[1] = rhs;
    return ret;
}

CowlString *cowl_string(UString raw_string) {
    if (ustring_is_null(raw_string)) return NULL;
    if (ustring_is_empty(raw_string)) return cowl_string_empty();
    return cowl_string_get(raw_string, false);
}

CowlString *cowl_string_opt(UString raw_string, CowlStringOpts opts) {
    CowlString *ret = NULL;
    bool copy = ubit_is_set(COWL_SO, opts, COWL_SO_COPY);

    if (ustring_is_null(raw_string)) {
        goto end_deinit;
    }

    if (ustring_is_empty(raw_string)) {
        ret = cowl_string_empty();
        goto end_deinit;
    }

    if (ubit_is_set(COWL_SO, opts, COWL_SO_INTERN)) {
        ret = cowl_string_get_intern(raw_string, copy);
    } else {
        ret = cowl_string_get(raw_string, copy);
    }

    return ret;

end_deinit:
    if (!copy) ustring_deinit(&raw_string);
    return ret;
}

CowlString *cowl_string_empty(void) {
    return cowl_retain(empty);
}

void cowl_string_free(CowlString *string) {
    // If the string was interned, it must also be removed from the hash set.
    if (cowl_object_bit_get(string)) uhset_remove(CowlObjectTable, &inst_tbl, string);
    ustring_deinit(&string->raw_string);
    ulib_free(string);
}

char *cowl_string_release_copying_cstring(CowlString *string) {
    if (!string) return NULL;
    char *ret;
    ulib_uint ref = cowl_object_decr_ref(string);

    if (ref) {
        ret = ulib_str_dup(ustring_data(string->raw_string), ustring_length(string->raw_string));
    } else {
        ret = ustring_deinit_return_data(&string->raw_string);
        string->raw_string = ustring_null;
        cowl_string_free(string);
    }

    return ret;
}

char const *cowl_string_get_cstring(CowlString *string) {
    return ustring_data(string->raw_string);
}

ulib_uint cowl_string_get_length(CowlString *string) {
    return ustring_length(string->raw_string);
}

UString const *cowl_string_get_raw(CowlString *string) {
    return &string->raw_string;
}

bool cowl_string_equals(CowlString *lhs, CowlString *rhs) {
    return lhs->hash == rhs->hash && ustring_equals(lhs->raw_string, rhs->raw_string);
}

ulib_uint cowl_string_hash(CowlString *string) {
    return string->hash;
}

CowlString *cowl_string_with_format(char const *format, ...) {
    va_list args;
    va_start(args, format);
    UString raw_string = ustring_with_format_list(format, args);
    va_end(args);
    return cowl_string(raw_string);
}

CowlString *cowl_string_concat(CowlString *lhs, CowlString *rhs) {
    UString comp[] = { lhs->raw_string, rhs->raw_string };
    UString cat = ustring_concat(comp, ulib_array_count(comp));
    return cowl_string(cat);
}
