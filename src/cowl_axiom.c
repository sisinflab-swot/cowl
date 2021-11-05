/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_axiom_private.h"
#include "cowl_template.h"

CowlAxiom* cowl_axiom_retain(CowlAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_axiom_release(CowlAxiom *axiom) {
    cowl_object_release((CowlObject *)axiom);
}

CowlAxiomType cowl_axiom_get_type(CowlAxiom *axiom) {
    return (CowlAxiomType)(cowl_get_type(axiom) - COWL_OT_A_DECL);
}

CowlString* cowl_axiom_to_string(CowlAxiom *axiom)
    COWL_TO_STRING_IMPL(axiom, axiom)

bool cowl_axiom_equals(CowlAxiom *lhs, CowlAxiom *rhs) {
    return cowl_object_equals((CowlObject *)lhs, (CowlObject *)rhs);
}

ulib_uint cowl_axiom_hash(CowlAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_axiom_iterate_primitives(CowlAxiom *axiom, CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_object_iterate_primitives((CowlObject *)axiom, flags, iter);
}
