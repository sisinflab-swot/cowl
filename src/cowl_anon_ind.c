/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_anon_ind_private.h"
#include "cowl_template.h"

static CowlAnonInd* cowl_anon_ind_alloc(void) {
    CowlAnonInd *ind = ulib_alloc(ind);
    if (!ind) return NULL;

    (*ind) = (CowlAnonInd) {
        .super = COWL_INDIVIDUAL_INIT(false)
    };

    return ind;
}

static void cowl_anon_ind_free(CowlAnonInd *ind) {
    ulib_free(ind);
}

CowlAnonInd* cowl_anon_ind_get(void) {
    return cowl_anon_ind_alloc();
}

CowlAnonInd* cowl_anon_ind_retain(CowlAnonInd *ind) {
    return cowl_object_incr_ref(ind);
}

void cowl_anon_ind_release(CowlAnonInd *ind) {
    if (ind && !cowl_object_decr_ref(ind)) {
        cowl_anon_ind_free(ind);
    }
}

CowlNodeId cowl_anon_ind_get_id(CowlAnonInd *ind) {
    return (CowlNodeId)ind;
}

CowlString* cowl_anon_ind_to_string(CowlAnonInd *ind)
    COWL_TO_STRING_IMPL(anon_ind, ind)

bool cowl_anon_ind_equals(CowlAnonInd *lhs, CowlAnonInd *rhs) {
    return lhs == rhs;
}

ulib_uint cowl_anon_ind_hash(CowlAnonInd *ind) {
    return uhash_ptr_hash(ind);
}

bool cowl_anon_ind_iterate_primitives(CowlAnonInd *ind, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_ANON_IND) ? cowl_iterate(iter, ind) : true;
}
