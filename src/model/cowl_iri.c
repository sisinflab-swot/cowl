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

UHASH_SET_INIT(CowlNSSet, CowlString*, cowl_string_hash, cowl_string_equals)
static UHash(CowlNSSet) *ns_set = NULL;

static inline cowl_uint_t cowl_iri_map_hash_func(CowlIRI iri) {
    return cowl_hash_2(COWL_HASH_INIT_IRI,
                       cowl_string_hash(iri.ns),
                       cowl_string_hash(iri.rem));
}

static inline bool cowl_iri_map_hash_equal(CowlIRI a, CowlIRI b) {
    return a.ns == b.ns && cowl_string_equals(a.rem, b.rem);
}

UHASH_MAP_INIT(CowlIRIMap, cowl_struct(CowlIRI), CowlIRI*,
               cowl_iri_map_hash_func, cowl_iri_map_hash_equal)
static UHash(CowlIRIMap) *inst_map = NULL;

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
    if (!inst_map) {
        inst_map = uhash_alloc(CowlIRIMap);
        ns_set = uhash_alloc(CowlNSSet);
    }

    uhash_ret_t ret = uhset_insert_get_existing(CowlNSSet, ns_set, ns, &ns);
    if (ret == UHASH_INSERTED) cowl_string_retain(ns);

    CowlIRI key = { .ns = ns, .rem = rem };
    CowlIRI *iri;

    uhash_uint_t idx = uhash_put(CowlIRIMap, inst_map, key, &ret);

    if (ret == UHASH_INSERTED) {
        iri = cowl_iri_alloc(ns, rem);
        uhash_value(inst_map, idx) = iri;
    } else {
        iri = uhash_value(inst_map, idx);
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
            uhset_remove(CowlNSSet, ns_set, iri->ns);
            cowl_string_release(iri->ns);
        }
        uhmap_remove(CowlIRIMap, inst_map, (*iri));
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
