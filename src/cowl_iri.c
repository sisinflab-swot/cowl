/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_iri.h"
#include "cowl_any.h"
#include "cowl_iri_private.h"
#include "cowl_object.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_ret.h"
#include "cowl_string.h"
#include "cowl_string_private.h"
#include "cowl_table.h" // IWYU pragma: keep, needed for UHash(CowlObjectTable)
#include "cowl_vocab.h"
#include "cowl_xml_utils.h"
#include "ulib.h"
#include <stddef.h>

static UHash(CowlObjectTable) inst_tbl;

static ulib_uint inst_tbl_hash(CowlAny *key) {
    ulib_uint h1 = ulib_hash_alloc_ptr(cowl_iri_get_ns(key));
    ulib_uint h2 = cowl_string_hash(cowl_iri_get_rem(key));
    return ulib_hash_combine(h1, h2);
}

static bool inst_tbl_eq(CowlAny *lhs, CowlAny *rhs) {
    return cowl_iri_get_ns(lhs) == cowl_iri_get_ns(rhs) &&
           cowl_string_equals(cowl_iri_get_rem(lhs), cowl_iri_get_rem(rhs));
}

cowl_ret cowl_iri_api_init(void) {
    inst_tbl = uhset_pi(CowlObjectTable, inst_tbl_hash, inst_tbl_eq);
    return COWL_OK;
}

void cowl_iri_api_deinit(void) {
    uhash_deinit(CowlObjectTable, &inst_tbl);
}

static CowlIRI *cowl_iri_alloc(CowlString *ns, CowlString *rem) {
    CowlIRI *iri = ulib_alloc(iri);
    if (!iri) return NULL;

    *iri = (CowlIRI){
        .super = COWL_OBJECT_INIT(COWL_OT_IRI),
        .ns = cowl_retain(ns),
        .rem = cowl_retain(rem),
    };

    return iri;
}

void cowl_iri_free(CowlIRI *iri) {
    uhset_remove(CowlObjectTable, &inst_tbl, iri);
    cowl_release(iri->ns);
    cowl_release(iri->rem);
    ulib_free(iri);
}

CowlIRI *cowl_iri_unvalidated(CowlString *ns, CowlString *rem) {
    if (!(ns && (ns = cowl_string_intern(ns)))) return NULL;

    ulib_uint idx;
    CowlIRI key = { .ns = ns, .rem = rem };
    uhash_ret ret = uhash_put(CowlObjectTable, &inst_tbl, &key, &idx);

    CowlIRI *val = NULL;

    if (ret == UHASH_INSERTED) {
        val = cowl_iri_alloc(ns, rem);
        if (val) {
            uhash_key(CowlObjectTable, &inst_tbl, idx) = val;
        } else {
            uhash_delete(CowlObjectTable, &inst_tbl, idx);
        }
    } else if (ret == UHASH_PRESENT) {
        val = uhash_key(CowlObjectTable, &inst_tbl, idx);
        (void)cowl_object_incr_ref(val);
    }

    return val;
}

CowlIRI *cowl_iri(CowlString *prefix, CowlString *suffix) {
    if (!(prefix && suffix)) return NULL;

    UString p_str = prefix->raw_string;
    UString s_str = suffix->raw_string;

    ulib_uint const s_ns_len = cowl_xml_ns_length(s_str);

    if (s_ns_len > 0) {
        // Part of the suffix should go in the namespace.
        UStrBuf buf = ustrbuf();
        char const *s_cstr = ustring_data(s_str);

        if (ustrbuf_append_ustring(&buf, p_str) || ustrbuf_append_string(&buf, s_cstr, s_ns_len)) {
            ustrbuf_deinit(&buf);
            return NULL;
        }

        prefix = cowl_string(ustrbuf_to_ustring(&buf));
        UString raw_suffix = ustring_wrap(s_cstr + s_ns_len, ustring_length(s_str) - s_ns_len);
        suffix = cowl_string_opt(raw_suffix, COWL_SO_COPY);
    } else {
        ulib_uint p_ns_len = cowl_xml_ns_length(p_str);

        if (p_ns_len < ustring_length(p_str)) {
            // Part of the prefix should go in the remainder.
            UStrBuf buf = ustrbuf();
            char const *p_cstr = ustring_data(p_str);

            if (ustrbuf_append_string(&buf, p_cstr + p_ns_len, ustring_length(p_str) - p_ns_len) ||
                ustrbuf_append_ustring(&buf, s_str)) {
                ustrbuf_deinit(&buf);
                return NULL;
            }

            prefix = cowl_string_opt(ustring_wrap(p_cstr, p_ns_len), COWL_SO_COPY | COWL_SO_INTERN);
            suffix = cowl_string(ustrbuf_to_ustring(&buf));
        } else {
            // Prefix is a namespace and suffix is a remainder, use as-is.
            cowl_retain(prefix);
            cowl_retain(suffix);
        }
    }

    CowlIRI *iri = NULL;

    if (prefix && suffix) {
        iri = cowl_iri_unvalidated(prefix, suffix);
    }

    cowl_release(prefix);
    cowl_release(suffix);

    return iri;
}

CowlIRI *cowl_iri_from_string(UString string) {
    if (ustring_size(string) <= 1) return NULL;
    ulib_uint ns_length = cowl_xml_ns_length(string);

    CowlString *parts[2] = { NULL };
    if (cowl_string_get_ns_rem(string, ns_length, parts)) return NULL;

    CowlIRI *iri = cowl_iri_unvalidated(parts[0], parts[1]);
    cowl_release(parts[0]);
    cowl_release(parts[1]);
    return iri;
}

CowlString *cowl_iri_get_ns(CowlIRI *iri) {
    return iri->ns;
}

CowlString *cowl_iri_get_rem(CowlIRI *iri) {
    return iri->rem;
}

bool cowl_iri_is_reserved(CowlIRI *iri) {
    return cowl_vocab_is_reserved_ns(iri->ns);
}
