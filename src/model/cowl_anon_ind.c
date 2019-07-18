/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_anon_ind_private.h"
#include "cowl_string.h"
#include "cowl_str_buf.h"

#define cowl_inst_hash(X) cowl_node_id_hash((X)->id)
#define cowl_inst_eq(A, B) cowl_node_id_equals((A)->id, (B)->id)

UHASH_INIT(CowlAnonIndTable, CowlAnonInd*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlAnonIndTable) *inst_tbl = NULL;

static CowlAnonInd* cowl_anon_ind_alloc(CowlNodeID id) {
    CowlAnonInd init = {
        .super = COWL_INDIVIDUAL_INIT(false),
        .id = id
    };
    cowl_struct(CowlAnonInd) *ind = malloc(sizeof(*ind));
    memcpy(ind, &init, sizeof(*ind));
    return ind;
}

static void cowl_anon_ind_free(CowlAnonInd *ind) {
    if (!ind) return;
    free((void *)ind);
}

CowlAnonInd* cowl_anon_ind_get(CowlNodeID id) {
    if (!inst_tbl) inst_tbl = uhset_alloc(CowlAnonIndTable);

    uhash_ret_t ret;
    CowlAnonInd key = { .id = id };
    uhash_uint_t idx = uhash_put(CowlAnonIndTable, inst_tbl, &key, &ret);

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
