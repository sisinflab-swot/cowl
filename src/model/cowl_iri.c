/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include <string.h>

#include "cowl_iri_private.h"
#include "cowl_hash_utils.h"
#include "cowl_string_private.h"
#include "cowl_str_buf.h"

static UHash(CowlStringTable) *ns_tbl = NULL;

static inline cowl_uint_t cowl_inst_hash(CowlIRI *iri) {
    return cowl_hash_2(COWL_HASH_INIT_IRI,
                       uhash_ptr_hash(iri->ns),
                       cowl_string_hash(iri->rem));
}

static inline bool cowl_inst_eq(CowlIRI *lhs, CowlIRI *rhs) {
    return lhs->ns == rhs->ns && cowl_string_equals(lhs->rem, rhs->rem);
}

UHASH_INIT(CowlIRITable, CowlIRI*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlIRITable) *inst_tbl = NULL;

static cowl_struct(CowlIRI)* cowl_iri_alloc(CowlString *ns, CowlString *rem) {
    CowlIRI init = {
        .super = COWL_OBJECT_INIT,
        .ns = cowl_string_retain(ns),
        .rem = cowl_string_retain(rem)
    };
    cowl_struct(CowlIRI) *iri = malloc(sizeof(*iri));
    memcpy(iri, &init, sizeof(*iri));
    return iri;
}

static void cowl_iri_free(CowlIRI *iri) {
    if (!iri) return;
    cowl_string_release(iri->ns);
    cowl_string_release(iri->rem);
    free((void *)iri);
}

CowlIRI* cowl_iri_get(CowlString *ns, CowlString *rem) {
    if (!inst_tbl) {
        inst_tbl = uhset_alloc(CowlIRITable);
        ns_tbl = uhset_alloc(CowlStringTable);
    }

    uhash_ret_t ret = uhset_insert_get_existing(CowlStringTable, ns_tbl, ns, &ns);
    if (ret == UHASH_INSERTED) cowl_string_retain(ns);

    CowlIRI key = { .ns = ns, .rem = rem };
    uhash_uint_t idx = uhash_put(CowlIRITable, inst_tbl, &key, &ret);

    CowlIRI *iri;

    if (ret == UHASH_INSERTED) {
        iri = cowl_iri_alloc(ns, rem);
        uhash_key(inst_tbl, idx) = iri;
    } else {
        iri = uhash_key(inst_tbl, idx);
        cowl_object_retain(iri);
    }

    return iri;
}

CowlIRI* cowl_iri_retain(CowlIRI *iri) {
    return cowl_object_retain(iri);
}

void cowl_iri_release(CowlIRI *iri) {
    if (iri && !cowl_object_release(iri)) {
        if (cowl_object_ref_get(iri->ns) == 2) {
            uhset_remove(CowlStringTable, ns_tbl, iri->ns);
            cowl_string_release(iri->ns);
        }
        uhset_remove(CowlIRITable, inst_tbl, iri);
        cowl_iri_free(iri);
    }
}

CowlIRI* cowl_iri_from_cstring(char const *cstring, cowl_uint_t length) {
    // TODO: implement according to spec: https://www.w3.org/TR/REC-xml-names/#NT-NCName
    CowlString *parts[2] = { NULL };
    cowl_string_split_two(cstring, length, '#', parts);

    CowlIRI *iri = cowl_iri_get(parts[0], parts[1]);

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

CowlString* cowl_iri_to_string(CowlIRI *iri) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_iri(buf, iri);
    return cowl_str_buf_to_string(buf);
}

bool cowl_iri_equals(CowlIRI *lhs, CowlIRI *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_iri_hash(CowlIRI *iri) {
    return uhash_ptr_hash(iri);
}
