/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_named_ind_private.h"
#include "cowl_iri.h"
#include "cowl_iterator_private.h"
#include "cowl_object_table.h"
#include "cowl_template.h"

static UHash(CowlObjectTable) *inst_tbl = NULL;

static ulib_uint inst_tbl_hash(void *key) {
    return cowl_iri_hash(cowl_named_ind_get_iri(key));
}

static bool inst_tbl_eq(void *lhs, void *rhs) {
    return cowl_iri_equals(cowl_named_ind_get_iri(lhs), cowl_named_ind_get_iri(rhs));
}

cowl_ret cowl_named_ind_api_init(void) {
    inst_tbl = uhset_alloc_pi(CowlObjectTable, inst_tbl_hash, inst_tbl_eq);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_named_ind_api_deinit(void) {
    uhash_free(CowlObjectTable, inst_tbl);
}

static CowlNamedInd* cowl_named_ind_alloc(CowlIRI *iri) {
    CowlNamedInd *ind = ulib_alloc(ind);
    if (!ind) return NULL;

    *ind = (CowlNamedInd) {
        .super = COWL_INDIVIDUAL_INIT(true),
        .iri = cowl_iri_retain(iri)
    };

    return ind;
}

static void cowl_named_ind_free(CowlNamedInd *ind) {
    if (!ind) return;
    cowl_iri_release(ind->iri);
    ulib_free(ind);
}

CowlNamedInd* cowl_named_ind_get(CowlIRI *iri) {
    if (!iri) return NULL;
    COWL_INST_TBL_GET_IMPL(NamedInd, named_ind, { .iri = iri }, cowl_named_ind_alloc(iri))
}

CowlNamedInd* cowl_named_ind_retain(CowlNamedInd *ind) {
    return cowl_object_incr_ref(ind);
}

void cowl_named_ind_release(CowlNamedInd *ind) {
    if (ind && !cowl_object_decr_ref(ind)) {
        uhset_remove(CowlObjectTable, inst_tbl, ind);
        cowl_named_ind_free(ind);
    }
}

CowlNamedInd* cowl_named_ind_from_string(UString string)
    COWL_ENTITY_FROM_STRING_IMPL(NamedInd, named_ind)

CowlIRI* cowl_named_ind_get_iri(CowlNamedInd *ind) {
    return ind->iri;
}

CowlString* cowl_named_ind_to_string(CowlNamedInd *ind)
    COWL_TO_STRING_IMPL(named_ind, ind)

bool cowl_named_ind_equals(CowlNamedInd *lhs, CowlNamedInd *rhs) {
    return lhs == rhs;
}

ulib_uint cowl_named_ind_hash(CowlNamedInd *ind) {
    return uhash_ptr_hash(ind);
}

bool cowl_named_ind_iterate_primitives(CowlNamedInd *ind, CowlPrimitiveFlags flags,
                                       CowlIterator *iter) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_NAMED_IND) ? cowl_iterate(iter, ind) : true;
}
