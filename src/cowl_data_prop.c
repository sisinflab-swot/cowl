/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_prop_private.h"
#include "cowl_iri.h"
#include "cowl_iterator_private.h"
#include "cowl_object_table.h"
#include "cowl_template.h"

static UHash(CowlObjectTable) *inst_tbl = NULL;

static ulib_uint inst_tbl_hash(void *key) {
    return cowl_iri_hash(cowl_data_prop_get_iri(key));
}

static bool inst_tbl_eq(void *lhs, void *rhs) {
    return cowl_iri_equals(cowl_data_prop_get_iri(lhs), cowl_data_prop_get_iri(rhs));
}

cowl_ret cowl_data_prop_api_init(void) {
    inst_tbl = uhset_alloc_pi(CowlObjectTable, inst_tbl_hash, inst_tbl_eq);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_data_prop_api_deinit(void) {
    uhash_free(CowlObjectTable, inst_tbl);
}

static CowlDataProp* cowl_data_prop_alloc(CowlIRI *iri) {
    CowlDataProp *prop = ulib_alloc(prop);
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
    ulib_free(prop);
}

CowlDataProp* cowl_data_prop_get(CowlIRI *iri) {
    if (!iri) return NULL;
    COWL_INST_TBL_GET_IMPL(DataProp, data_prop, { .iri = iri }, cowl_data_prop_alloc(iri))
}

CowlDataProp* cowl_data_prop_retain(CowlDataProp *prop) {
    return cowl_object_incr_ref(prop);
}

void cowl_data_prop_release(CowlDataProp *prop) {
    if (prop && !cowl_object_decr_ref(prop)) {
        uhset_remove(CowlObjectTable, inst_tbl, prop);
        cowl_data_prop_free(prop);
    }
}

CowlDataProp* cowl_data_prop_from_string(UString string)
    COWL_ENTITY_FROM_STRING_IMPL(DataProp, data_prop)

CowlIRI* cowl_data_prop_get_iri(CowlDataProp *prop) {
    return prop->iri;
}

CowlString* cowl_data_prop_to_string(CowlDataProp *prop)
    COWL_TO_STRING_IMPL(data_prop, prop)

bool cowl_data_prop_equals(CowlDataProp *lhs, CowlDataProp *rhs) {
    return lhs == rhs;
}

ulib_uint cowl_data_prop_hash(CowlDataProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_data_prop_iterate_primitives(CowlDataProp *prop, CowlPrimitiveFlags flags,
                                       CowlIterator *iter) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_DATA_PROP) ? cowl_iterate(iter, prop) : true;
}
