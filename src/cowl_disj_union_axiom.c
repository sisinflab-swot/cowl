/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_disj_union_axiom_private.h"
#include "cowl_class.h"
#include "cowl_cls_exp_set.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlDisjUnionAxiom* cowl_disj_union_axiom_alloc(CowlClass *cls, CowlClsExpSet *disjoints,
                                                       CowlAnnotationVec *annot) {
    CowlDisjUnionAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint hash = cowl_axiom_hash_2(COWL_HASH_INIT_DISJ_UNION_AXIOM, annot,
                                       cowl_class_hash(cls),
                                       cowl_cls_exp_set_hash(disjoints));

    cowl_axiom_init(CowlDisjUnionAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_DISJ_UNION, hash, annot),
        .cls = cowl_class_retain(cls),
        .disjoints = disjoints
    );

    return axiom;
}

static void cowl_disj_union_axiom_free(CowlDisjUnionAxiom *axiom) {
    if (!axiom) return;
    cowl_class_release(axiom->cls);
    cowl_cls_exp_set_free(axiom->disjoints);
    cowl_axiom_free(axiom);
}

CowlDisjUnionAxiom* cowl_disj_union_axiom_get(CowlClass *cls, CowlClsExpSet *disjoints,
                                              CowlAnnotationVec *annot) {
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

CowlClsExpSet* cowl_disj_union_axiom_get_disjoints(CowlDisjUnionAxiom *axiom) {
    return axiom->disjoints;
}

CowlAnnotationVec* cowl_disj_union_axiom_get_annot(CowlDisjUnionAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_disj_union_axiom_to_string(CowlDisjUnionAxiom *axiom)
    COWL_TO_STRING_IMPL(disj_union_axiom, axiom)

bool cowl_disj_union_axiom_equals(CowlDisjUnionAxiom *lhs, CowlDisjUnionAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_class_equals(lhs->cls, rhs->cls) &&
                                  cowl_cls_exp_set_equals(lhs->disjoints, rhs->disjoints));
}

cowl_uint cowl_disj_union_axiom_hash(CowlDisjUnionAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_disj_union_axiom_iterate_primitives(CowlDisjUnionAxiom *axiom, CowlIterator *iter,
                                              CowlPrimitiveFlags flags) {
    return (cowl_class_iterate_primitives(axiom->cls, iter, flags) &&
            cowl_cls_exp_set_iterate_primitives(axiom->disjoints, iter, flags) &&
            cowl_axiom_annot_iterate_primitives(axiom, iter, flags));
}
