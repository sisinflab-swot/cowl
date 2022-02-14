/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_cls_axiom_private.h"
#include "cowl_macros.h"
#include "cowl_object_table.h"
#include "cowl_template.h"

static CowlNAryClsAxiom* cowl_nary_cls_axiom_alloc(CowlAxiomType type, CowlObjectTable *classes,
                                                   CowlObjectVec *annot) {
    CowlNAryClsAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    ulib_uint hash = cowl_axiom_hash_2(COWL_HASH_INIT_NARY_CLS_AXIOM, annot, type,
                                       cowl_object_set_hash(classes));

    cowl_axiom_init(CowlNAryClsAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .classes = classes
    );

    return axiom;
}

static void cowl_nary_cls_axiom_free(CowlNAryClsAxiom *axiom) {
    cowl_object_set_free(axiom->classes);
    cowl_axiom_free(axiom);
}

CowlNAryClsAxiom* cowl_nary_cls_axiom_get(CowlNAryAxiomType type, CowlObjectTable *classes,
                                          CowlObjectVec *annot) {
    if (!(classes && cowl_enum_value_is_valid(NAT, type))) return NULL;
    return cowl_nary_cls_axiom_alloc((CowlAxiomType)type + COWL_AT_EQUIV_CLASSES, classes, annot);
}

CowlNAryClsAxiom* cowl_nary_cls_axiom_retain(CowlNAryClsAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_nary_cls_axiom_release(CowlNAryClsAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_nary_cls_axiom_free(axiom);
    }
}

CowlNAryAxiomType cowl_nary_cls_axiom_get_type(CowlNAryClsAxiom *axiom) {
    return (CowlNAryAxiomType)(cowl_get_type(axiom) - COWL_OT_A_EQUIV_CLASSES);
}

CowlObjectTable *cowl_nary_cls_axiom_get_classes(CowlNAryClsAxiom *axiom) {
    return axiom->classes;
}

CowlObjectVec* cowl_nary_cls_axiom_get_annot(CowlNAryClsAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_nary_cls_axiom_to_string(CowlNAryClsAxiom *axiom)
    COWL_TO_STRING_IMPL(nary_cls_axiom, axiom)

bool cowl_nary_cls_axiom_equals(CowlNAryClsAxiom *lhs, CowlNAryClsAxiom *rhs) {
    return cowl_object_type_equals(lhs, rhs) &&
           cowl_axiom_equals_impl(lhs, rhs, cowl_object_set_equals(lhs->classes, rhs->classes));
}

ulib_uint cowl_nary_cls_axiom_hash(CowlNAryClsAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_cls_axiom_iterate_primitives(CowlNAryClsAxiom *axiom, CowlPrimitiveFlags flags,
                                            CowlIterator *iter) {
    return (cowl_object_set_iterate_primitives(axiom->classes, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
