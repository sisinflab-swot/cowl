/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_datatype_private.h"
#include "cowl_alloc.h"
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"

#define cowl_inst_hash(X) cowl_iri_hash((X)->iri)
#define cowl_inst_eq(A, B) cowl_iri_equals((A)->iri, (B)->iri)

UHASH_INIT(CowlDatatypeTable, CowlDatatype*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlDatatypeTable) *inst_tbl = NULL;

void cowl_datatype_api_init(void) {
    inst_tbl = uhset_alloc(CowlDatatypeTable);
}

void cowl_datatype_api_deinit(void) {
    uhash_free(CowlDatatypeTable, inst_tbl);
}

static CowlDatatype* cowl_datatype_alloc(CowlIRI *iri) {
    CowlDatatype *dt = cowl_alloc(dt);
    *dt = (CowlDatatype) {
        .super = COWL_DATA_RANGE_INIT(COWL_DRT_DATATYPE, 0),
        .iri = cowl_iri_retain(iri)
    };

    cowl_uint_t hash = uhash_ptr_hash(dt);
    cowl_object_hash_set(dt, hash);

    return dt;
}

static void cowl_datatype_free(CowlDatatype *dt) {
    if (!dt) return;
    cowl_iri_release(dt->iri);
    cowl_free(dt);
}

CowlDatatype* cowl_datatype_get(CowlIRI *iri) {
    uhash_uint_t idx;
    CowlDatatype key = { .iri = iri };
    uhash_ret_t ret = uhash_put(CowlDatatypeTable, inst_tbl, &key, &idx);

    CowlDatatype *dt;

    if (ret == UHASH_INSERTED) {
        dt = cowl_datatype_alloc(iri);
        uhash_key(inst_tbl, idx) = dt;
    } else {
        dt = uhash_key(inst_tbl, idx);
        cowl_object_retain(dt);
    }

    return dt;
}

CowlDatatype* cowl_datatype_retain(CowlDatatype *dt) {
    return cowl_object_retain(dt);
}

void cowl_datatype_release(CowlDatatype *dt) {
    if (dt && !cowl_object_release(dt)) {
        uhset_remove(CowlDatatypeTable, inst_tbl, dt);
        cowl_datatype_free(dt);
    }
}

CowlDatatype* cowl_datatype_from_cstring(char const *cstring, size_t length) {
    CowlIRI *iri = cowl_iri_from_cstring(cstring, length);
    CowlDatatype *dt = cowl_datatype_get(iri);
    cowl_iri_release(iri);
    return dt;
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
