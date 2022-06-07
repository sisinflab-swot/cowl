/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annot_prop.h"
#include "cowl_entity_private.h"
#include "cowl_iterator_private.h"

CowlAnnotProp* cowl_annot_prop_get(CowlIRI *iri) {
    return cowl_entity_get(COWL_OT_ANNOT_PROP, iri);
}

void cowl_annot_prop_release(CowlAnnotProp *prop) {
    cowl_entity_release((CowlEntity *)prop);
}

CowlAnnotProp* cowl_annot_prop_from_string(UString string) {
    return cowl_entity_from_string(COWL_OT_ANNOT_PROP, string);
}

CowlIRI* cowl_annot_prop_get_iri(CowlAnnotProp *prop) {
    return cowl_entity_get_iri((CowlEntity *)prop);
}

CowlString* cowl_annot_prop_to_string(CowlAnnotProp *prop) {
    return cowl_entity_to_string((CowlEntity *)prop);
}

bool cowl_annot_prop_iterate_primitives(CowlAnnotProp *prop, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_ANNOT_PROP) ? cowl_iterate(iter, prop) : true;
}
