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
#include "cowl_object_table.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static UHash(CowlObjectTable) *inst_tbl = NULL;

static uhash_uint inst_tbl_hash(void *key) {
    return cowl_node_id_hash(cowl_anon_ind_get_id(key));
}

static bool inst_tbl_eq(void *lhs, void *rhs) {
    return cowl_node_id_equals(cowl_anon_ind_get_id(lhs), cowl_anon_ind_get_id(rhs));
}

cowl_ret cowl_anon_ind_api_init(void) {
    inst_tbl = uhset_alloc_pi(CowlObjectTable, inst_tbl_hash, inst_tbl_eq);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_anon_ind_api_deinit(void) {
    uhash_free(CowlObjectTable, inst_tbl);
}

static CowlAnonInd* cowl_anon_ind_alloc(CowlNodeID id) {
    CowlAnonInd *ind = cowl_alloc(ind);
    if (!ind) return NULL;

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
    if (!id) return NULL;
    COWL_INST_TBL_GET_IMPL(AnonInd, anon_ind, { .id = id }, cowl_anon_ind_alloc(id))
}

CowlAnonInd* cowl_anon_ind_retain(CowlAnonInd *ind) {
    return cowl_object_incr_ref(ind);
}

void cowl_anon_ind_release(CowlAnonInd *ind) {
    if (ind && !cowl_object_decr_ref(ind)) {
        uhset_remove(CowlObjectTable, inst_tbl, ind);
        cowl_anon_ind_free(ind);
    }
}

CowlNodeID cowl_anon_ind_get_id(CowlAnonInd *ind) {
    return ind->id;
}

CowlString* cowl_anon_ind_to_string(CowlAnonInd *ind)
    COWL_TO_STRING_IMPL(anon_ind, ind)

bool cowl_anon_ind_equals(CowlAnonInd *lhs, CowlAnonInd *rhs) {
    return lhs == rhs;
}

cowl_uint cowl_anon_ind_hash(CowlAnonInd *ind) {
    return uhash_ptr_hash(ind);
}

bool cowl_anon_ind_iterate_primitives(CowlAnonInd *ind, CowlIterator *iter,
                                      CowlPrimitiveFlags flags) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_ANON_IND) ? cowl_iterate(iter, ind) : true;
}
