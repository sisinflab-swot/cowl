/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_cls_axiom_private.h"
#include "cowl_cls_exp_set.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlNAryClsAxiom* cowl_nary_cls_axiom_alloc(CowlAxiomType type, CowlClsExpSet *classes,
                                                   CowlAnnotationVec *annot) {
    CowlNAryClsAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_NARY_CLS_AXIOM, annot, type,
                                         cowl_cls_exp_set_hash(classes));

    cowl_axiom_init(CowlNAryClsAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .classes = classes
    );

    return axiom;
}

static void cowl_nary_cls_axiom_free(CowlNAryClsAxiom *axiom) {
    if (!axiom) return;
    cowl_cls_exp_set_free(axiom->classes);
    cowl_axiom_free(axiom);
}

CowlNAryClsAxiom* cowl_nary_cls_axiom_get(CowlNAryAxiomType type, CowlClsExpSet *classes,
                                          CowlAnnotationVec *annot) {
    return cowl_nary_cls_axiom_alloc((CowlAxiomType)type + COWL_AT_EQUIV_CLASSES, classes, annot);
}

CowlNAryClsAxiom* cowl_nary_cls_axiom_retain(CowlNAryClsAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_nary_cls_axiom_release(CowlNAryClsAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_nary_cls_axiom_free(axiom);
    }
}

CowlNAryAxiomType cowl_nary_cls_axiom_get_type(CowlNAryClsAxiom *axiom) {
    CowlAxiomFlags flags = axiom->super.flags;
    return (CowlNAryAxiomType)(flags - COWL_AT_EQUIV_CLASSES);
}

CowlClsExpSet *cowl_nary_cls_axiom_get_classes(CowlNAryClsAxiom *axiom) {
    return axiom->classes;
}

CowlAnnotationVec* cowl_nary_cls_axiom_get_annot(CowlNAryClsAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_nary_cls_axiom_to_string(CowlNAryClsAxiom *axiom)
    COWL_TO_STRING_IMPL(nary_cls_axiom, axiom)

bool cowl_nary_cls_axiom_equals(CowlNAryClsAxiom *lhs, CowlNAryClsAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs, cowl_cls_exp_set_equals(lhs->classes, rhs->classes));
}

cowl_uint_t cowl_nary_cls_axiom_hash(CowlNAryClsAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_cls_axiom_iterate_signature(CowlNAryClsAxiom *axiom, CowlEntityIterator *iter) {
    if (!cowl_cls_exp_set_iterate_signature(axiom->classes, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}

bool cowl_nary_cls_axiom_iterate_anon_inds(CowlNAryClsAxiom *axiom, CowlAnonIndIterator *iter) {
    if (!cowl_cls_exp_set_iterate_anon_inds(axiom->classes, iter)) return false;
    if (!cowl_axiom_annot_iterate_anon_inds(axiom, iter)) return false;
    return true;
}
