/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_named_ind_private.h"
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"

#define cowl_inst_hash(X) cowl_iri_hash((X)->iri)
#define cowl_inst_eq(A, B) cowl_iri_equals((A)->iri, (B)->iri)

UHASH_INIT(CowlNamedIndTable, CowlNamedInd*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlNamedIndTable) *inst_tbl = NULL;

void cowl_named_ind_api_init(void) {
    inst_tbl = uhset_alloc(CowlNamedIndTable);
}

void cowl_named_ind_api_deinit(void) {
    uhash_free(CowlNamedIndTable, inst_tbl);
}

static CowlNamedInd* cowl_named_ind_alloc(CowlIRI *iri) {
    CowlNamedInd ind_init = {
        .super = COWL_INDIVIDUAL_INIT(true),
        .iri = cowl_iri_retain(iri)
    };
    cowl_struct(CowlNamedInd) *ind = malloc(sizeof(*ind));
    memcpy(ind, &ind_init, sizeof(*ind));
    return ind;
}

static void cowl_named_ind_free(CowlNamedInd *ind) {
    if (!ind) return;
    cowl_iri_release(ind->iri);
    free((void *)ind);
}

CowlNamedInd* cowl_named_ind_get(CowlIRI *iri) {
    uhash_ret_t ret;
    CowlNamedInd key = { .iri = iri };
    uhash_uint_t idx = uhash_put(CowlNamedIndTable, inst_tbl, &key, &ret);

    CowlNamedInd *ind;

    if (ret == UHASH_INSERTED) {
        ind = cowl_named_ind_alloc(iri);
        uhash_key(inst_tbl, idx) = ind;
    } else {
        ind = uhash_key(inst_tbl, idx);
        cowl_object_retain(ind);
    }

    return ind;
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

CowlNamedInd* cowl_named_ind_from_cstring(char const *cstring, cowl_uint_t length) {
    CowlIRI *iri = cowl_iri_from_cstring(cstring, length);
    CowlNamedInd *ind = cowl_named_ind_get(iri);
    cowl_iri_release(iri);
    return ind;
}

CowlIRI* cowl_named_ind_get_iri(CowlNamedInd *ind) {
    return ind->iri;
}

CowlString* cowl_named_ind_to_string(CowlNamedInd *ind) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_named_ind(buf, ind);
    return cowl_str_buf_to_string(buf);
}

bool cowl_named_ind_equals(CowlNamedInd *lhs, CowlNamedInd *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_named_ind_hash(CowlNamedInd *ind) {
    return uhash_ptr_hash(ind);
}

bool cowl_named_ind_iterate_signature(CowlNamedInd *ind, CowlEntityIterator *iter) {
    return cowl_iterate(iter, cowl_entity_wrap_named_ind(ind));
}
