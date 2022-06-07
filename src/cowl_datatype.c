/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_datatype.h"
#include "cowl_entity_private.h"
#include "cowl_iterator_private.h"

CowlDatatype* cowl_datatype_get(CowlIRI *iri) {
    return cowl_entity_get(COWL_OT_DR_DATATYPE, iri);
}

void cowl_datatype_release(CowlDatatype *dt) {
    cowl_entity_release((CowlEntity *)dt);
}

CowlDatatype* cowl_datatype_from_string(UString string) {
    return cowl_entity_from_string(COWL_OT_DR_DATATYPE, string);
}

CowlIRI* cowl_datatype_get_iri(CowlDatatype *dt) {
    return cowl_entity_get_iri((CowlEntity *)dt);
}

CowlString* cowl_datatype_to_string(CowlDatatype *dt) {
    return cowl_entity_to_string((CowlEntity *)dt);
}

bool cowl_datatype_iterate_primitives(CowlDatatype *dt, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_DATATYPE) ? cowl_iterate(iter, dt) : true;
}
