/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_named_ind_private.h"
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

#define cowl_inst_hash(X) cowl_iri_hash((X)->iri)
#define cowl_inst_eq(A, B) cowl_iri_equals((A)->iri, (B)->iri)

UHASH_INIT(CowlNamedIndTable, CowlNamedInd*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlNamedIndTable) *inst_tbl = NULL;

cowl_ret_t cowl_named_ind_api_init(void) {
    inst_tbl = uhset_alloc(CowlNamedIndTable);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_named_ind_api_deinit(void) {
    uhash_free(CowlNamedIndTable, inst_tbl);
}

static CowlNamedInd* cowl_named_ind_alloc(CowlIRI *iri) {
    CowlNamedInd *ind = cowl_alloc(ind);
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
    cowl_free(ind);
}

CowlNamedInd* cowl_named_ind_get(CowlIRI *iri) {
    if (!iri) return NULL;
    COWL_INST_TBL_GET_IMPL(NamedInd, named_ind, { .iri = iri }, cowl_named_ind_alloc(iri))
}

CowlNamedInd* cowl_named_ind_retain(CowlNamedInd *ind) {
    return cowl_object_retain(ind);
}

void cowl_named_ind_release(CowlNamedInd *ind) {
    if (ind && !cowl_object_release(ind)) {
        uhset_remove(CowlNamedIndTable, inst_tbl, ind);
        cowl_named_ind_free(ind);
    }
}

CowlNamedInd* cowl_named_ind_from_cstring(char const *cstring, size_t length)
    COWL_ENTITY_FROM_CSTRING_IMPL(NamedInd, named_ind)

CowlIRI* cowl_named_ind_get_iri(CowlNamedInd *ind) {
    return ind->iri;
}

CowlString* cowl_named_ind_to_string(CowlNamedInd *ind)
    COWL_TO_STRING_IMPL(named_ind, ind)

bool cowl_named_ind_equals(CowlNamedInd *lhs, CowlNamedInd *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_named_ind_hash(CowlNamedInd *ind) {
    return uhash_ptr_hash(ind);
}

bool cowl_named_ind_iterate(CowlNamedInd *ind, CowlIterator *iter) {
    return cowl_flags_is_set(iter->flags, COWL_IF_NAMED_IND) ? cowl_iterate(iter, ind) : true;
}
