/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_anon_ind.h"
#include "cowl_iterator_private.h"
#include "cowl_object_private.h"
#include "cowl_primitive.h"

static ulib_uint const rand_id_len = P_USTRING_SMALL_SIZE - 1;

CowlAnonInd* cowl_anon_ind(void) {
    CowlObject *ind = ulib_alloc(ind);
    if (!ind) return NULL;
    *ind = COWL_OBJECT_INIT(COWL_OT_I_ANONYMOUS);
    return (CowlAnonInd*)ind;
}

void cowl_anon_ind_release(CowlAnonInd *ind) {
    if (ind && !cowl_object_decr_ref(ind)) {
        ulib_free(ind);
    }
}

UString cowl_anon_ind_generate_id(void) {
    return urand_string(rand_id_len, NULL);
}
