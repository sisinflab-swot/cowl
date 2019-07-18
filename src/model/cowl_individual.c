/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_individual_private.h"
#include "cowl_anon_ind.h"
#include "cowl_named_ind.h"
#include "cowl_str_buf.h"

CowlIndividual* cowl_individual_retain(CowlIndividual *ind) {
    return cowl_object_retain(ind);
}

void cowl_individual_release(CowlIndividual *ind) {
    if (!ind) return;

    if (ind->is_named) {
        cowl_named_ind_release((CowlNamedInd *)ind);
    } else {
        cowl_anon_ind_release((CowlAnonInd *)ind);
    }
}

bool cowl_individual_is_named(CowlIndividual *ind) {
    return ind->is_named;
}

CowlString* cowl_individual_to_string(CowlIndividual *ind) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_individual(buf, ind);
    return cowl_str_buf_to_string(buf);
}

bool cowl_individual_equals(CowlIndividual *lhs, CowlIndividual *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_individual_hash(CowlIndividual *ind) {
    return uhash_ptr_hash(ind);
}

bool cowl_individual_iterate_signature(CowlIndividual *ind, CowlEntityIterator *iter) {
    if (!ind->is_named) return true;
    return cowl_named_ind_iterate_signature((CowlNamedInd *)ind, iter);
}

bool cowl_individual_iterate_anon_inds(CowlIndividual *ind, CowlAnonIndIterator *iter) {
    if (ind->is_named) return true;
    return cowl_anon_ind_iterate_anon_inds((CowlAnonInd *)ind, iter);
}
