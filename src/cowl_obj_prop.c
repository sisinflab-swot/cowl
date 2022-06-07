/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop.h"
#include "cowl_entity_private.h"
#include "cowl_iterator_private.h"

CowlObjProp* cowl_obj_prop_get(CowlIRI *iri) {
    return cowl_entity_get(COWL_OT_OPE_OBJ_PROP, iri);
}

void cowl_obj_prop_release(CowlObjProp *prop) {
    cowl_entity_release((CowlEntity *)prop);
}

CowlObjProp* cowl_obj_prop_from_string(UString string) {
    return cowl_entity_from_string(COWL_OT_OPE_OBJ_PROP, string);
}

CowlIRI* cowl_obj_prop_get_iri(CowlObjProp *prop) {
    return cowl_entity_get_iri((CowlEntity *)prop);
}

CowlString* cowl_obj_prop_to_string(CowlObjProp *prop) {
    return cowl_entity_to_string((CowlEntity *)prop);
}

bool cowl_obj_prop_iterate_primitives(CowlObjProp *prop, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_OBJ_PROP) ? cowl_iterate(iter, prop) : true;
}
