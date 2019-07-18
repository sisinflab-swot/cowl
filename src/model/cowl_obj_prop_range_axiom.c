/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_range_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_str_buf.h"

static CowlObjPropRangeAxiom* cowl_obj_prop_range_axiom_alloc(CowlObjPropExp *prop,
                                                              CowlClsExp *range,
                                                              CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_OBJ_PROP_RANGE_AXIOM, annot,
                                         cowl_obj_prop_exp_hash(prop),
                                         cowl_cls_exp_hash(range));

    CowlObjPropRangeAxiom init = {
        .super = COWL_AXIOM_INIT(COWL_AT_OBJ_PROP_RANGE, hash, annot),
        .prop_exp = cowl_obj_prop_exp_retain(prop),
        .range = cowl_cls_exp_retain(range)
    };

    cowl_struct(CowlObjPropRangeAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_obj_prop_range_axiom_free(CowlObjPropRangeAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_release(axiom->prop_exp);
    cowl_cls_exp_release(axiom->range);
    cowl_axiom_free(axiom);
}

CowlObjPropRangeAxiom* cowl_obj_prop_range_axiom_get(CowlObjPropExp *prop, CowlClsExp *range,
                                                     CowlAnnotationVec *annot) {
    return cowl_obj_prop_range_axiom_alloc(prop, range, annot);
}

CowlObjPropRangeAxiom* cowl_obj_prop_range_axiom_retain(CowlObjPropRangeAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_obj_prop_range_axiom_release(CowlObjPropRangeAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_obj_prop_range_axiom_free(axiom);
    }
}

CowlObjPropExp* cowl_obj_prop_range_axiom_get_prop(CowlObjPropRangeAxiom *axiom) {
    return axiom->prop_exp;
}

CowlClsExp* cowl_obj_prop_range_axiom_get_range(CowlObjPropRangeAxiom *axiom) {
    return axiom->range;
}

CowlAnnotationVec* cowl_obj_prop_range_axiom_get_annot(CowlObjPropRangeAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_obj_prop_range_axiom_to_string(CowlObjPropRangeAxiom *axiom) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_obj_prop_range(buf, axiom);
    return cowl_str_buf_to_string(buf);
}

bool cowl_obj_prop_range_axiom_equals(CowlObjPropRangeAxiom *lhs, CowlObjPropRangeAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
                                  cowl_cls_exp_equals(lhs->range, rhs->range));
}

cowl_uint_t cowl_obj_prop_range_axiom_hash(CowlObjPropRangeAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_obj_prop_range_axiom_iterate_signature(CowlObjPropRangeAxiom *axiom,
                                                 CowlEntityIterator *iter) {
    if (!cowl_obj_prop_exp_iterate_signature(axiom->prop_exp, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(axiom->range, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}

bool cowl_obj_prop_range_axiom_iterate_anon_inds(CowlObjPropRangeAxiom *axiom,
                                                 CowlAnonIndIterator *iter) {
    if (!cowl_cls_exp_iterate_anon_inds(axiom->range, iter)) return false;
    if (!cowl_axiom_annot_iterate_anon_inds(axiom, iter)) return false;
    return true;
}
