/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_datatype_private.h"
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"

UHASH_MAP_INIT(CowlDatatypeMap, CowlIRI*, CowlDatatype*, cowl_iri_hash, cowl_iri_equals)
static UHash(CowlDatatypeMap) *inst_map = NULL;

static CowlDatatype* cowl_datatype_alloc(CowlIRI *iri) {
    CowlDatatype init = {
        .super = COWL_DATA_RANGE_INIT(COWL_DRT_DATATYPE, 0),
        .iri = cowl_iri_retain(iri)
    };
    cowl_struct(CowlDatatype) *dt = malloc(sizeof(*dt));
    memcpy(dt, &init, sizeof(*dt));

    cowl_uint_t hash = uhash_ptr_hash(dt);
    cowl_object_hash_set(dt, hash);

    return dt;
}

static void cowl_datatype_free(CowlDatatype *dt) {
    if (!dt) return;
    cowl_iri_release(dt->iri);
    free((void *)dt);
}

CowlDatatype* cowl_datatype_get(CowlIRI *iri) {
    if (!inst_map) inst_map = uhash_alloc(CowlDatatypeMap);

    CowlDatatype *dt;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlDatatypeMap, inst_map, iri, &ret);

    if (ret == UHASH_INSERTED) {
        dt = cowl_datatype_alloc(iri);
        uhash_value(inst_map, idx) = dt;
    } else {
        dt = uhash_value(inst_map, idx);
        cowl_object_retain(dt);
    }

    return dt;
}

CowlDatatype* cowl_datatype_retain(CowlDatatype *dt) {
    return cowl_object_retain(dt);
}

void cowl_datatype_release(CowlDatatype *dt) {
    if (dt && !cowl_object_release(dt)) {
        uhmap_remove(CowlDatatypeMap, inst_map, dt->iri);
        cowl_datatype_free(dt);
    }
}

CowlIRI* cowl_datatype_get_iri(CowlDatatype *dt) {
    return dt->iri;
}

CowlString* cowl_datatype_to_string(CowlDatatype *dt) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_datatype(buf, dt);
    return cowl_str_buf_to_string(buf);
}

bool cowl_datatype_equals(CowlDatatype *lhs, CowlDatatype *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_datatype_hash(CowlDatatype *dt) {
    return cowl_object_hash_get(dt);
}

bool cowl_datatype_iterate_signature(CowlDatatype *dt, CowlEntityIterator *iter) {
    return cowl_iterate(iter, cowl_entity_wrap_datatype(dt));
}
