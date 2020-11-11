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
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

#define cowl_inst_hash(X) cowl_iri_hash((X)->iri)
#define cowl_inst_eq(A, B) cowl_iri_equals((A)->iri, (B)->iri)

UHASH_INIT(CowlDatatypeTable, CowlDatatype*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlDatatypeTable) *inst_tbl = NULL;

cowl_ret cowl_datatype_api_init(void) {
    inst_tbl = uhset_alloc(CowlDatatypeTable);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_datatype_api_deinit(void) {
    uhash_free(CowlDatatypeTable, inst_tbl);
}

static CowlDatatype* cowl_datatype_alloc(CowlIRI *iri) {
    CowlDatatype *dt = cowl_alloc(dt);
    if (!dt) return NULL;

    *dt = (CowlDatatype) {
        .super = COWL_DATA_RANGE_INIT(COWL_DRT_DATATYPE, 0),
        .iri = cowl_iri_retain(iri)
    };

    cowl_uint hash = uhash_ptr_hash(dt);
    cowl_object_hash_set(dt, hash);

    return dt;
}

static void cowl_datatype_free(CowlDatatype *dt) {
    if (!dt) return;
    cowl_iri_release(dt->iri);
    cowl_free(dt);
}

CowlDatatype* cowl_datatype_get(CowlIRI *iri) {
    if (!iri) return NULL;
    COWL_INST_TBL_GET_IMPL(Datatype, datatype, { .iri = iri }, cowl_datatype_alloc(iri))
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

CowlDatatype* cowl_datatype_from_cstring(char const *cstring, size_t length)
    COWL_ENTITY_FROM_CSTRING_IMPL(Datatype, datatype)

CowlIRI* cowl_datatype_get_iri(CowlDatatype *dt) {
    return dt->iri;
}

CowlString* cowl_datatype_to_string(CowlDatatype *dt)
    COWL_TO_STRING_IMPL(datatype, dt)

bool cowl_datatype_equals(CowlDatatype *lhs, CowlDatatype *rhs) {
    return lhs == rhs;
}

cowl_uint cowl_datatype_hash(CowlDatatype *dt) {
    return cowl_object_hash_get(dt);
}

bool cowl_datatype_iterate_primitives(CowlDatatype *dt, CowlIterator *iter,
                                      CowlPrimitiveFlags flags) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_DATATYPE) ? cowl_iterate(iter, dt) : true;
}
