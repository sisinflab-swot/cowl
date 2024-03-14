/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_INDEX_PRIVATE_H
#define COWL_AXIOM_INDEX_PRIVATE_H

#include "cowl_axiom_index.h"

COWL_BEGIN_DECLS

COWL_PURE
COWL_INLINE
CowlAxiomIndex cowl_axiom_index_move(CowlAxiomIndex *index) {
    CowlAxiomIndex ret;
    if (index) {
        ret = *index;
        *index = (CowlAxiomIndex){ 0 };
    } else {
        ret = cowl_axiom_index(COWL_AF_NONE);
    }
    return ret;
}

COWL_PURE
COWL_INLINE
bool cowl_axiom_index_matches_types(CowlAxiomIndex *index, CowlAnyAxiom *axiom) {
    return cowl_axiom_flags_has_type(index->types, cowl_axiom_get_type(axiom));
}

COWL_PURE
COWL_INLINE
bool cowl_axiom_index_matches_primitives(CowlAxiomIndex *index, CowlAnyAxiom *axiom) {
    uvec_foreach (CowlObjectPtr, &index->primitives, p) {
        if (!cowl_has_primitive(axiom, *p.item)) return false;
    }
    return true;
}

COWL_PURE
COWL_INLINE
bool cowl_axiom_index_matches(CowlAxiomIndex *index, CowlAnyAxiom *axiom) {
    return cowl_axiom_index_matches_types(index, axiom) &&
           cowl_axiom_index_matches_primitives(index, axiom);
}

COWL_END_DECLS

#endif // COWL_AXIOM_INDEX_PRIVATE_H
