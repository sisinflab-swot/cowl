/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_prop_private.h"
#include "cowl_alloc.h"
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

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
    CowlDataProp *prop = cowl_alloc(prop);
    if (!prop) return NULL;

    *prop = (CowlDataProp) {
        .super = COWL_DATA_PROP_EXP_INIT,
        .iri = cowl_iri_retain(iri)
    };

    return prop;
}

static void cowl_data_prop_free(CowlDataProp *prop) {
    if (!prop) return;
    cowl_iri_release(prop->iri);
    cowl_free(prop);
}

CowlDataProp* cowl_data_prop_get(CowlIRI *iri)
    COWL_INST_TBL_GET_IMPL(DataProp, data_prop, { .iri = iri }, cowl_data_prop_alloc(iri))

CowlDataProp* cowl_data_prop_retain(CowlDataProp *prop) {
    return cowl_object_retain(prop);
}

void cowl_data_prop_release(CowlDataProp *prop) {
    if (prop && !cowl_object_release(prop)) {
        uhset_remove(CowlDataPropTable, inst_tbl, prop);
        cowl_data_prop_free(prop);
    }
}

CowlDataProp* cowl_data_prop_from_cstring(char const *cstring, size_t length)
    COWL_ENTITY_FROM_CSTRING_IMPL(DataProp, data_prop)

CowlIRI* cowl_data_prop_get_iri(CowlDataProp *prop) {
    return prop->iri;
}

CowlString* cowl_data_prop_to_string(CowlDataProp *prop)
    COWL_TO_STRING_IMPL(data_prop, prop)

bool cowl_data_prop_equals(CowlDataProp *lhs, CowlDataProp *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_data_prop_hash(CowlDataProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_data_prop_iterate_signature(CowlDataProp *prop, CowlEntityIterator *iter) {
    return cowl_iterate(iter, cowl_entity_wrap_data_prop(prop));
}
