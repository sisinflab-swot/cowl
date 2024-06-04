/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_FILTER_PRIVATE_H
#define COWL_AXIOM_FILTER_PRIVATE_H

#include "cowl_axiom.h"
#include "cowl_axiom_filter.h"

COWL_BEGIN_DECLS

COWL_PURE
COWL_INLINE
CowlAxiomFilter cowl_axiom_filter_move(CowlAxiomFilter *filter) {
    CowlAxiomFilter ret;
    if (filter) {
        ret = *filter;
        *filter = (CowlAxiomFilter){ 0 };
    } else {
        ret = cowl_axiom_filter(COWL_AF_NONE);
    }
    return ret;
}

COWL_PURE
COWL_INLINE
bool cowl_axiom_filter_matches_types(CowlAxiomFilter const *filter, CowlAnyAxiom *axiom) {
    return filter->types == COWL_AF_ALL ||
           cowl_axiom_flags_has_type(filter->types, cowl_axiom_get_type(axiom));
}

COWL_PURE
COWL_INLINE
bool cowl_axiom_filter_matches_primitives(CowlAxiomFilter const *filter, CowlAnyAxiom *axiom) {
    uvec_foreach (CowlObjectPtr, &filter->primitives, p) {
        if (!cowl_has_primitive(axiom, *p.item)) return false;
    }
    return true;
}

COWL_PURE
COWL_INLINE
bool cowl_axiom_filter_matches_filter(CowlAxiomFilter const *filter, CowlAnyAxiom *axiom) {
    return !filter->closure.filter || filter->closure.filter(filter->closure.ctx, axiom);
}

COWL_PURE
COWL_INLINE
bool cowl_axiom_filter_matches(CowlAxiomFilter const *filter, CowlAnyAxiom *axiom) {
    return cowl_axiom_filter_matches_types(filter, axiom) &&
           cowl_axiom_filter_matches_primitives(filter, axiom) &&
           cowl_axiom_filter_matches_filter(filter, axiom);
}

COWL_END_DECLS

#endif // COWL_AXIOM_FILTER_PRIVATE_H
