/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_disj_union_axiom_private.h"
#include "cowl_class.h"
#include "cowl_template.h"
#include "cowl_vector.h"

static CowlDisjUnionAxiom* cowl_disj_union_axiom_alloc(CowlClass *cls, CowlVector *disjoints,
                                                       CowlVector *annot) {
    CowlDisjUnionAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_axiom_init(CowlDisjUnionAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_DISJ_UNION, annot),
        .cls = cowl_class_retain(cls),
        .disjoints = cowl_vector_retain(disjoints)
    );

    return axiom;
}

static void cowl_disj_union_axiom_free(CowlDisjUnionAxiom *axiom) {
    cowl_class_release(axiom->cls);
    cowl_vector_release(axiom->disjoints);
    cowl_axiom_free(axiom);
}

CowlDisjUnionAxiom* cowl_disj_union_axiom_get(CowlClass *cls, CowlVector *disjoints,
                                              CowlVector *annot) {
    if (!(cls && disjoints)) return NULL;
    return cowl_disj_union_axiom_alloc(cls, disjoints, annot);
}

CowlDisjUnionAxiom* cowl_disj_union_axiom_retain(CowlDisjUnionAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_disj_union_axiom_release(CowlDisjUnionAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_disj_union_axiom_free(axiom);
    }
}

CowlClass* cowl_disj_union_axiom_get_class(CowlDisjUnionAxiom *axiom) {
    return axiom->cls;
}

CowlVector* cowl_disj_union_axiom_get_disjoints(CowlDisjUnionAxiom *axiom) {
    return axiom->disjoints;
}

CowlVector* cowl_disj_union_axiom_get_annot(CowlDisjUnionAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_disj_union_axiom_to_string(CowlDisjUnionAxiom *axiom)
    COWL_TO_STRING_IMPL(disj_union_axiom, axiom)

bool cowl_disj_union_axiom_equals(CowlDisjUnionAxiom *lhs, CowlDisjUnionAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_class_equals(lhs->cls, rhs->cls) &&
                                  cowl_vector_equals(lhs->disjoints, rhs->disjoints));
}

ulib_uint cowl_disj_union_axiom_hash(CowlDisjUnionAxiom *axiom) {
    return cowl_hash_2(COWL_HASH_INIT_DISJ_UNION_AXIOM,
                       cowl_class_hash(axiom->cls),
                       cowl_vector_hash(axiom->disjoints));
}

bool cowl_disj_union_axiom_iterate_primitives(CowlDisjUnionAxiom *axiom, CowlPrimitiveFlags flags,
                                              CowlIterator *iter) {
    return (cowl_class_iterate_primitives(axiom->cls, flags, iter) &&
            cowl_vector_iterate_primitives(axiom->disjoints, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
