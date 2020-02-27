/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_prop_private.h"
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"

#define cowl_inst_hash(X) cowl_iri_hash((X)->iri)
#define cowl_inst_eq(A, B) cowl_iri_equals((A)->iri, (B)->iri)

UHASH_INIT(CowlDataPropTable, CowlDataProp*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlDataPropTable) *inst_tbl = NULL;

void cowl_data_prop_api_init(void) {
    inst_tbl = uhset_alloc(CowlDataPropTable);
}

void cowl_data_prop_api_deinit(void) {
    uhash_free(CowlDataPropTable, inst_tbl);
}

static CowlDataProp* cowl_data_prop_alloc(CowlIRI *iri) {
    CowlDataProp init = { .super = COWL_DATA_PROP_EXP_INIT, .iri = cowl_iri_retain(iri) };
    cowl_struct(CowlDataProp) *prop = malloc(sizeof(*prop));
    memcpy(prop, &init, sizeof(*prop));
    return prop;
}

static void cowl_data_prop_free(CowlDataProp *prop) {
    if (!prop) return;
    cowl_iri_release(prop->iri);
    free((void *)prop);
}

CowlDataProp* cowl_data_prop_get(CowlIRI *iri) {
    uhash_ret_t ret;
    CowlDataProp key = { .iri = iri };
    uhash_uint_t idx = uhash_put(CowlDataPropTable, inst_tbl, &key, &ret);

    CowlDataProp *prop;

    if (ret == UHASH_INSERTED) {
        prop = cowl_data_prop_alloc(iri);
        uhash_key(inst_tbl, idx) = prop;
    } else {
        prop = uhash_key(inst_tbl, idx);
        cowl_object_retain(prop);
    }

    return prop;
}

CowlDataProp* cowl_data_prop_retain(CowlDataProp *prop) {
    return cowl_object_retain(prop);
}

void cowl_data_prop_release(CowlDataProp *prop) {
    if (prop && !cowl_object_release(prop)) {
        uhset_remove(CowlDataPropTable, inst_tbl, prop);
        cowl_data_prop_free(prop);
    }
}

CowlDataProp* cowl_data_prop_from_cstring(char const *cstring, cowl_uint_t length) {
    CowlIRI *iri = cowl_iri_from_cstring(cstring, length);
    CowlDataProp *prop = cowl_data_prop_get(iri);
    cowl_iri_release(iri);
    return prop;
}

CowlIRI* cowl_data_prop_get_iri(CowlDataProp *prop) {
    return prop->iri;
}

CowlString* cowl_data_prop_to_string(CowlDataProp *prop) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_data_prop(buf, prop);
    return cowl_str_buf_to_string(buf);
}

bool cowl_data_prop_equals(CowlDataProp *lhs, CowlDataProp *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_data_prop_hash(CowlDataProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_data_prop_iterate_signature(CowlDataProp *prop, CowlEntityIterator *iter) {
    return cowl_iterate(iter, cowl_entity_wrap_data_prop(prop));
}
