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

CowlAnonInd* cowl_anon_ind_get(void) {
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

CowlNodeId cowl_anon_ind_get_id(CowlAnonInd *ind) {
    return (CowlNodeId)ind;
}

CowlString* cowl_anon_ind_to_string(CowlAnonInd *ind) {
    return cowl_primitive_to_string((CowlPrimitive *)ind);
}

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
