/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_sub_cls_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_template.h"

static CowlSubClsAxiom* cowl_sub_cls_axiom_alloc(CowlClsExp *sub, CowlClsExp *super,
                                                 CowlObjectVec *annot) {
    CowlSubClsAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    ulib_uint hash = cowl_axiom_hash_2(COWL_HASH_INIT_SUBCLASS_AXIOM, annot,
                                       cowl_cls_exp_hash(super),
                                       cowl_cls_exp_hash(sub));

    cowl_axiom_init(CowlSubClsAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_SUB_CLASS, hash, annot),
        .super_class = cowl_cls_exp_retain(super),
        .sub_class = cowl_cls_exp_retain(sub)
    );

    return axiom;
}

static void cowl_sub_cls_axiom_free(CowlSubClsAxiom *axiom) {
    cowl_cls_exp_release(axiom->super_class);
    cowl_cls_exp_release(axiom->sub_class);
    cowl_axiom_free(axiom);
}

CowlSubClsAxiom* cowl_sub_cls_axiom_get(CowlClsExp *sub, CowlClsExp *super,
                                        CowlObjectVec *annot) {
    if (!(sub && super)) return NULL;
    return cowl_sub_cls_axiom_alloc(sub, super, annot);
}

CowlSubClsAxiom* cowl_sub_cls_axiom_retain(CowlSubClsAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_sub_cls_axiom_release(CowlSubClsAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_sub_cls_axiom_free(axiom);
    }
}

CowlClsExp* cowl_sub_cls_axiom_get_super(CowlSubClsAxiom *axiom) {
    return axiom->super_class;
}

CowlClsExp* cowl_sub_cls_axiom_get_sub(CowlSubClsAxiom *axiom) {
    return axiom->sub_class;
}

CowlObjectVec* cowl_sub_cls_axiom_get_annot(CowlSubClsAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_sub_cls_axiom_to_string(CowlSubClsAxiom *axiom)
    COWL_TO_STRING_IMPL(sub_cls_axiom, axiom)

bool cowl_sub_cls_axiom_equals(CowlSubClsAxiom *lhs, CowlSubClsAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_cls_exp_equals(lhs->sub_class, rhs->sub_class) &&
                                  cowl_cls_exp_equals(lhs->super_class, rhs->super_class));
}

ulib_uint cowl_sub_cls_axiom_hash(CowlSubClsAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_sub_cls_axiom_iterate_primitives(CowlSubClsAxiom *axiom, CowlPrimitiveFlags flags,
                                           CowlIterator *iter) {
    return (cowl_cls_exp_iterate_primitives(axiom->super_class, flags, iter) &&
            cowl_cls_exp_iterate_primitives(axiom->sub_class, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
