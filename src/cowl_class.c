/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_class.h"
#include "cowl_entity_private.h"
#include "cowl_iterator_private.h"

CowlClass* cowl_class_get(CowlIRI *iri) {
    return cowl_entity_get(COWL_OT_CE_CLASS, iri);
}

void cowl_class_release(CowlClass *cls) {
    cowl_entity_release((CowlEntity *)cls);
}

CowlClass* cowl_class_from_string(UString string) {
    return cowl_entity_from_string(COWL_OT_CE_CLASS, string);
}

CowlString* cowl_class_to_string(CowlClass *cls) {
    return cowl_entity_to_string((CowlEntity *)cls);
}

CowlIRI* cowl_class_get_iri(CowlClass *cls) {
    return cowl_entity_get_iri((CowlEntity *)cls);
}

bool cowl_class_iterate_primitives(CowlClass *cls, CowlPrimitiveFlags flags, CowlIterator *iter) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_CLASS) ? cowl_iterate(iter, cls) : true;
}
