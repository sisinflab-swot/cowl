/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_named_ind.h"
#include "cowl_entity_private.h"
#include "cowl_iterator_private.h"

CowlNamedInd* cowl_named_ind_get(CowlIRI *iri) {
    return cowl_entity_get(COWL_OT_I_NAMED, iri);
}

void cowl_named_ind_release(CowlNamedInd *ind) {
    cowl_entity_release((CowlEntity *)ind);
}

CowlNamedInd* cowl_named_ind_from_string(UString string) {
    return cowl_entity_from_string(COWL_OT_I_NAMED, string);
}

CowlIRI* cowl_named_ind_get_iri(CowlNamedInd *ind) {
    return cowl_entity_get_iri((CowlEntity *)ind);
}

CowlString* cowl_named_ind_to_string(CowlNamedInd *ind) {
    return cowl_entity_to_string((CowlEntity *)ind);
}

bool cowl_named_ind_iterate_primitives(CowlNamedInd *ind, CowlPrimitiveFlags flags,
                                       CowlIterator *iter) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_NAMED_IND) ? cowl_iterate(iter, ind) : true;
}
