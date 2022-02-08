/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_iri_private.h"
#include "cowl_hash_utils.h"
#include "cowl_object_table.h"
#include "cowl_string_private.h"
#include "cowl_xml_utils.h"
#include "cowl_template.h"

static UHash(CowlObjectTable) *inst_tbl = NULL;

static ulib_uint inst_tbl_hash(void *key) {
    return cowl_hash_2(COWL_HASH_INIT_IRI, uhash_ptr_hash(cowl_iri_get_ns(key)),
                       cowl_string_hash(cowl_iri_get_rem(key)));
}

static bool inst_tbl_eq(void *lhs, void *rhs) {
    return cowl_iri_get_ns(lhs) == cowl_iri_get_ns(rhs) &&
           cowl_string_equals(cowl_iri_get_rem(lhs), cowl_iri_get_rem(rhs));
}

cowl_ret cowl_iri_api_init(void) {
    inst_tbl = uhset_alloc_pi(CowlObjectTable, inst_tbl_hash, inst_tbl_eq);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_iri_api_deinit(void) {
    uhash_free(CowlObjectTable, inst_tbl);
}

static CowlIRI* cowl_iri_alloc(CowlString *ns, CowlString *rem) {
    CowlIRI *iri = ulib_alloc(iri);
    if (!iri) return NULL;

    *iri = (CowlIRI) {
        .super = COWL_OBJECT_INIT(COWL_OT_IRI),
        .ns = cowl_string_retain(ns),
        .rem = cowl_string_retain(rem)
    };

    return iri;
}

static void cowl_iri_free(CowlIRI *iri) {
    if (!iri) return;
    cowl_string_release(iri->ns);
    cowl_string_release(iri->rem);
    ulib_free(iri);
}

CowlIRI* cowl_iri_unvalidated_get(CowlString *ns, CowlString *rem) {
    if (!(ns && (ns = cowl_string_intern(ns)))) return NULL;
    COWL_INST_TBL_GET_IMPL(IRI, iri, ((CowlIRI){ .ns = ns, .rem = rem }), cowl_iri_alloc(ns, rem))
}

CowlIRI* cowl_iri_get(CowlString *prefix, CowlString *suffix) {
    if (!(prefix && suffix)) return NULL;

    UString p_str = prefix->raw_string;
    UString s_str = suffix->raw_string;

    ulib_uint const s_ns_len = cowl_xml_ns_length(s_str);

    if (s_ns_len > 0) {
        // Part of the suffix should go in the namespace.
        UStrBuf buf = ustrbuf_init();
        char const *s_cstr = ustring_data(s_str);

        if (ustrbuf_append_ustring(&buf, p_str) ||
            ustrbuf_append_string(&buf, s_cstr, s_ns_len)) {
            ustrbuf_deinit(buf);
            return NULL;
        }

        prefix = cowl_string_get(ustrbuf_to_ustring(&buf));
        suffix = cowl_string_get(ustring_copy(s_cstr + s_ns_len, ustring_length(s_str) - s_ns_len));
    } else {
        ulib_uint p_ns_len = cowl_xml_ns_length(p_str);

        if (p_ns_len < ustring_length(p_str)) {
            // Part of the prefix should go in the remainder.
            UStrBuf buf = ustrbuf_init();
            char const *p_cstr = ustring_data(p_str);

            if (ustrbuf_append_string(&buf, p_cstr + p_ns_len, ustring_length(p_str) - p_ns_len) ||
                ustrbuf_append_ustring(&buf, s_str)) {
                ustrbuf_deinit(buf);
                return NULL;
            }

            prefix = cowl_string_get(ustring_copy(p_cstr, p_ns_len));
            suffix = cowl_string_alloc(ustrbuf_to_ustring(&buf));
        } else {
            // Prefix is a namespace and suffix is a remainder, use as-is.
            cowl_string_retain(prefix);
            cowl_string_retain(suffix);
        }
    }

    CowlIRI *iri = NULL;

    if (prefix && suffix) {
        iri = cowl_iri_unvalidated_get(prefix, suffix);
    }

    cowl_string_release(prefix);
    cowl_string_release(suffix);

    return iri;
}

CowlIRI* cowl_iri_retain(CowlIRI *iri) {
    return cowl_object_incr_ref(iri);
}

void cowl_iri_release(CowlIRI *iri) {
    if (iri && !cowl_object_decr_ref(iri)) {
        uhset_remove(CowlObjectTable, inst_tbl, iri);
        cowl_iri_free(iri);
    }
}

CowlIRI* cowl_iri_from_string(UString string) {
    if (ustring_size(string) <= 1) return NULL;
    ulib_uint ns_length = cowl_xml_ns_length(string);

    CowlString *parts[2] = { NULL };
    if (cowl_string_get_ns_rem(string, ns_length, parts)) return NULL;

    CowlIRI *iri = cowl_iri_unvalidated_get(parts[0], parts[1]);

    cowl_string_release(parts[0]);
    cowl_string_release(parts[1]);

    return iri;
}

CowlString* cowl_iri_get_ns(CowlIRI *iri) {
    return iri->ns;
}

CowlString* cowl_iri_get_rem(CowlIRI *iri) {
    return iri->rem;
}

CowlString* cowl_iri_to_string(CowlIRI *iri)
    COWL_TO_STRING_IMPL(iri, iri)

CowlString* cowl_iri_to_string_no_brackets(CowlIRI *iri)
    COWL_TO_STRING_IMPL(iri_no_brackets, iri)

bool cowl_iri_equals(CowlIRI *lhs, CowlIRI *rhs) {
    return lhs == rhs;
}

ulib_uint cowl_iri_hash(CowlIRI *iri) {
    return uhash_ptr_hash(iri);
}
