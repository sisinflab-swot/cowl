/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_range_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlObjPropRangeAxiom* cowl_obj_prop_range_axiom_alloc(CowlObjPropExp *prop,
                                                              CowlClsExp *range,
                                                              CowlAnnotationVec *annot) {
    CowlObjPropRangeAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_OBJ_PROP_RANGE_AXIOM, annot,
                                         cowl_obj_prop_exp_hash(prop),
                                         cowl_cls_exp_hash(range));

    cowl_axiom_init(CowlObjPropRangeAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_OBJ_PROP_RANGE, hash, annot),
        .prop_exp = cowl_obj_prop_exp_retain(prop),
        .range = cowl_cls_exp_retain(range)
    );

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
    if (!(prop && range)) return NULL;
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

CowlString* cowl_obj_prop_range_axiom_to_string(CowlObjPropRangeAxiom *axiom)
    COWL_TO_STRING_IMPL(obj_prop_range, axiom)

bool cowl_obj_prop_range_axiom_equals(CowlObjPropRangeAxiom *lhs, CowlObjPropRangeAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
                                  cowl_cls_exp_equals(lhs->range, rhs->range));
}

cowl_uint_t cowl_obj_prop_range_axiom_hash(CowlObjPropRangeAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_obj_prop_range_axiom_iterate(CowlObjPropRangeAxiom *axiom, CowlIterator *iter) {
    if (cowl_obj_prop_exp_iterate(axiom->prop_exp, iter) &&
        cowl_cls_exp_iterate(axiom->range, iter) &&
        cowl_axiom_annot_iterate(axiom, iter)) {
        return true;
    }
    return false;
}
