/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_sub_annot_prop_axiom_private.h"
#include "cowl_annot_prop.h"
#include "cowl_str_buf.h"

static CowlSubAnnotPropAxiom* cowl_sub_annot_prop_axiom_alloc(CowlAnnotProp *sub,
                                                              CowlAnnotProp *super,
                                                              CowlAnnotationVec *annot) {
    CowlSubAnnotPropAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_SUB_ANNOT_PROP_AXIOM, annot,
                                         cowl_annot_prop_hash(sub),
                                         cowl_annot_prop_hash(super));

    cowl_axiom_init(CowlSubAnnotPropAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_SUB_ANNOT_PROP, hash, annot),
        .sub_prop = cowl_annot_prop_retain(sub),
        .super_prop = cowl_annot_prop_retain(super)
    );

    return axiom;
}

static void cowl_sub_annot_prop_axiom_free(CowlSubAnnotPropAxiom *axiom) {
    if (!axiom) return;
    cowl_annot_prop_release(axiom->sub_prop);
    cowl_annot_prop_release(axiom->super_prop);
    cowl_axiom_free(axiom);
}

CowlSubAnnotPropAxiom* cowl_sub_annot_prop_axiom_get(CowlAnnotProp *sub, CowlAnnotProp *super,
                                                     CowlAnnotationVec *annot) {
    return cowl_sub_annot_prop_axiom_alloc(sub, super, annot);
}

CowlSubAnnotPropAxiom* cowl_sub_annot_prop_axiom_retain(CowlSubAnnotPropAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_sub_annot_prop_axiom_release(CowlSubAnnotPropAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_sub_annot_prop_axiom_free(axiom);
    }
}

CowlAnnotProp* cowl_sub_annot_prop_axiom_get_super(CowlSubAnnotPropAxiom *axiom) {
    return axiom->super_prop;
}

CowlAnnotProp* cowl_sub_annot_prop_axiom_get_sub(CowlSubAnnotPropAxiom *axiom) {
    return axiom->sub_prop;
}

CowlAnnotationVec* cowl_sub_annot_prop_axiom_get_annot(CowlSubAnnotPropAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_sub_annot_prop_axiom_to_string(CowlSubAnnotPropAxiom *axiom) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_sub_annot_prop_axiom(buf, axiom);
    return cowl_str_buf_to_string(buf);
}

bool cowl_sub_annot_prop_axiom_equals(CowlSubAnnotPropAxiom *lhs, CowlSubAnnotPropAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_annot_prop_equals(lhs->super_prop, rhs->super_prop) &&
                                  cowl_annot_prop_equals(lhs->sub_prop, rhs->sub_prop));
}

cowl_uint_t cowl_sub_annot_prop_axiom_hash(CowlSubAnnotPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_sub_annot_prop_axiom_iterate_signature(CowlSubAnnotPropAxiom *axiom,
                                                 CowlEntityIterator *iter) {
    if (!cowl_annot_prop_iterate_signature(axiom->super_prop, iter)) return false;
    if (!cowl_annot_prop_iterate_signature(axiom->sub_prop, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}

bool cowl_sub_annot_prop_axiom_iterate_anon_inds(CowlSubAnnotPropAxiom *axiom,
                                                 CowlAnonIndIterator *iter) {
    return cowl_axiom_annot_iterate_anon_inds(axiom, iter);
}
