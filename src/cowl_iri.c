/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_iri_private.h"
#include "cowl_hash_utils.h"
#include "cowl_string_private.h"
#include "cowl_str_buf.h"
#include "cowl_xml_utils.h"
#include "cowl_template.h"

static inline cowl_uint cowl_inst_hash(CowlIRI *iri) {
    return cowl_hash_2(COWL_HASH_INIT_IRI,
                       uhash_ptr_hash(iri->ns),
                       cowl_string_hash(iri->rem));
}

static inline bool cowl_inst_eq(CowlIRI *lhs, CowlIRI *rhs) {
    return lhs->ns == rhs->ns && cowl_string_equals(lhs->rem, rhs->rem);
}

UHASH_INIT(CowlIRITable, CowlIRI*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlIRITable) *inst_tbl = NULL;

cowl_ret cowl_iri_api_init(void) {
    inst_tbl = uhset_alloc(CowlIRITable);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_iri_api_deinit(void) {
    uhash_free(CowlIRITable, inst_tbl);
}

static CowlIRI* cowl_iri_alloc(CowlString *ns, CowlString *rem) {
    CowlIRI *iri = cowl_alloc(iri);
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
    cowl_free(iri);
}

CowlIRI* cowl_iri_unvalidated_get(CowlString *ns, CowlString *rem) {
    if (!(ns && (ns = cowl_string_intern(ns)))) return NULL;
    COWL_INST_TBL_GET_IMPL(IRI, iri, ((CowlIRI){ .ns = ns, .rem = rem }), cowl_iri_alloc(ns, rem))
}

CowlIRI* cowl_iri_get(CowlString *prefix, CowlString *suffix) {
    if (!(prefix && suffix)) return NULL;

    CowlRawString p_str = prefix->raw_string;
    CowlRawString s_str = suffix->raw_string;

    cowl_uint const s_ns_len = cowl_xml_ns_length(s_str);

    if (s_ns_len > 0) {
        // Part of the suffix should go in the namespace.
        CowlStrBuf buf = cowl_str_buf_init;

        if (cowl_str_buf_append_raw_string(&buf, p_str) ||
            cowl_str_buf_append_cstring(&buf, s_str.cstring, s_ns_len)) {
            cowl_str_buf_deinit(&buf);
            return NULL;
        }

        prefix = cowl_str_buf_to_string(&buf);
        suffix = cowl_string_get(s_str.cstring + s_ns_len, s_str.length - s_ns_len, true);
    } else {
        cowl_uint p_ns_len = cowl_xml_ns_length(p_str);

        if (p_ns_len < p_str.length) {
            // Part of the prefix should go in the remainder.
            CowlStrBuf buf = cowl_str_buf_init;

            if (cowl_str_buf_append_cstring(&buf, p_str.cstring + p_ns_len,
                                            p_str.length - p_ns_len) ||
                cowl_str_buf_append_raw_string(&buf, s_str)) {
                cowl_str_buf_deinit(&buf);
                return NULL;
            }

            prefix = cowl_string_get(p_str.cstring, p_ns_len, true);
            suffix = cowl_str_buf_to_string(&buf);
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
        uhset_remove(CowlIRITable, inst_tbl, iri);
        cowl_iri_free(iri);
    }
}

CowlIRI* cowl_iri_from_cstring(char const *cstring, size_t length) {
    if (!(cstring && length)) return NULL;

    CowlRawString string = cowl_raw_string_init(cstring, length, false);
    cowl_uint ns_length = cowl_xml_ns_length(string);

    CowlString *parts[2] = { NULL };
    if (cowl_string_split_two(string, ns_length, parts)) return NULL;

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

CowlString* cowl_iri_to_string_no_brackets(CowlIRI *iri) {
    CowlStrBuf buf = cowl_str_buf_init;
    cowl_str_buf_append_iri_no_brackets(&buf, iri);
    return cowl_str_buf_to_string(&buf);
}

bool cowl_iri_equals(CowlIRI *lhs, CowlIRI *rhs) {
    return lhs == rhs;
}

cowl_uint cowl_iri_hash(CowlIRI *iri) {
    return uhash_ptr_hash(iri);
}
