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
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlIndividual* cowl_individual_retain(CowlIndividual *ind) {
    return cowl_object_incr_ref(ind);
}

void cowl_individual_release(CowlIndividual *ind) {
    cowl_object_release((CowlObject *)ind);
}

bool cowl_individual_is_named(CowlIndividual *ind) {
    return cowl_get_type(ind) == COWL_OT_I_NAMED;
}

CowlString* cowl_individual_to_string(CowlIndividual *ind)
    COWL_TO_STRING_IMPL(individual, ind)

bool cowl_individual_equals(CowlIndividual *lhs, CowlIndividual *rhs) {
    return lhs == rhs;
}

cowl_uint cowl_individual_hash(CowlIndividual *ind) {
    return uhash_ptr_hash(ind);
}

bool cowl_individual_iterate_primitives(CowlIndividual *ind, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return cowl_object_iterate_primitives((CowlObject *)ind, flags, iter);
}
