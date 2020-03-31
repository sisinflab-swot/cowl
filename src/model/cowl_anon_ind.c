/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_anon_ind_private.h"
#include "cowl_alloc.h"
#include "cowl_str_buf.h"

#define cowl_inst_hash(X) cowl_node_id_hash((X)->id)
#define cowl_inst_eq(A, B) cowl_node_id_equals((A)->id, (B)->id)

UHASH_INIT(CowlAnonIndTable, CowlAnonInd*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlAnonIndTable) *inst_tbl = NULL;

void cowl_anon_ind_api_init(void) {
    inst_tbl = uhset_alloc(CowlAnonIndTable);
}

void cowl_anon_ind_api_deinit(void) {
    uhash_free(CowlAnonIndTable, inst_tbl);
}

static CowlAnonInd* cowl_anon_ind_alloc(CowlNodeID id) {
    CowlAnonInd *ind = cowl_alloc(ind);
    (*ind) = (CowlAnonInd) {
        .super = COWL_INDIVIDUAL_INIT(false),
        .id = id
    };
    return ind;
}

static void cowl_anon_ind_free(CowlAnonInd *ind) {
    if (ind) cowl_free(ind);
}

CowlAnonInd* cowl_anon_ind_get(CowlNodeID id) {
    uhash_uint_t idx;
    CowlAnonInd key = { .id = id };
    uhash_ret_t ret = uhash_put(CowlAnonIndTable, inst_tbl, &key, &idx);

    CowlAnonInd *ind;

    if (ret == UHASH_INSERTED) {
        ind = cowl_anon_ind_alloc(id);
        uhash_key(inst_tbl, idx) = ind;
    } else {
        ind = uhash_key(inst_tbl, idx);
        cowl_object_retain(ind);
    }

    return ind;
}

CowlAnonInd* cowl_anon_ind_retain(CowlAnonInd *ind) {
    return cowl_object_retain(ind);
}

void cowl_anon_ind_release(CowlAnonInd *ind) {
    if (ind && !cowl_object_release(ind)) {
        uhset_remove(CowlAnonIndTable, inst_tbl, ind);
        cowl_anon_ind_free(ind);
    }
}

CowlNodeID cowl_anon_ind_get_id(CowlAnonInd *ind) {
    return ind->id;
}

CowlString* cowl_anon_ind_to_string(CowlAnonInd *ind) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_anon_ind(buf, ind);
    return cowl_str_buf_to_string(buf);
}

bool cowl_anon_ind_equals(CowlAnonInd *lhs, CowlAnonInd *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_anon_ind_hash(CowlAnonInd *ind) {
    return uhash_ptr_hash(ind);
}

bool cowl_anon_ind_iterate_anon_inds(CowlAnonInd *ind, CowlAnonIndIterator *iter) {
    return cowl_iterate(iter, ind);
}
