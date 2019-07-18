/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_has_key_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_data_prop_exp_set.h"
#include "cowl_obj_prop_exp_set.h"
#include "cowl_str_buf.h"

static CowlHasKeyAxiom* cowl_has_key_axiom_alloc(CowlClsExp *cls_exp, CowlObjPropExpSet *obj_props,
                                                 CowlDataPropExpSet *data_props,
                                                 CowlAnnotationVec *annot) {
    cowl_uint_t obj_props_hash = obj_props ? cowl_obj_prop_exp_set_hash(obj_props) : 0;
    cowl_uint_t data_props_hash = data_props ? cowl_data_prop_exp_set_hash(data_props) : 0;
    cowl_uint_t hash = cowl_axiom_hash_3(COWL_HASH_INIT_HAS_KEY_AXIOM, annot,
                                         cowl_cls_exp_hash(cls_exp),
                                         obj_props_hash, data_props_hash);

    CowlHasKeyAxiom init = {
        .super = COWL_AXIOM_INIT(COWL_AT_HAS_KEY, hash, annot),
        .cls_exp = cowl_cls_exp_retain(cls_exp),
        .obj_props = obj_props,
        .data_props = data_props
    };

    cowl_struct(CowlHasKeyAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_has_key_axiom_free(CowlHasKeyAxiom *axiom) {
    if (!axiom) return;
    cowl_cls_exp_release(axiom->cls_exp);
    cowl_obj_prop_exp_set_free(axiom->obj_props);
    cowl_data_prop_exp_set_free(axiom->data_props);
    cowl_axiom_free(axiom);
}

CowlHasKeyAxiom* cowl_has_key_axiom_get(CowlClsExp *cls_exp, CowlObjPropExpSet *obj_props,
                                        CowlDataPropExpSet *data_props, CowlAnnotationVec *annot) {
    return cowl_has_key_axiom_alloc(cls_exp, obj_props, data_props, annot);
}

CowlHasKeyAxiom* cowl_has_key_axiom_retain(CowlHasKeyAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_has_key_axiom_release(CowlHasKeyAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_has_key_axiom_free(axiom);
    }
}

CowlClsExp* cowl_has_key_axiom_get_cls_exp(CowlHasKeyAxiom *axiom) {
    return axiom->cls_exp;
}

CowlObjPropExpSet* cowl_has_key_axiom_get_obj_props(CowlHasKeyAxiom *axiom) {
    return axiom->obj_props;
}

CowlDataPropExpSet* cowl_has_key_axiom_get_data_props(CowlHasKeyAxiom *axiom) {
    return axiom->data_props;
}

CowlAnnotationVec* cowl_has_key_axiom_get_annot(CowlHasKeyAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_has_key_axiom_to_string(CowlHasKeyAxiom *axiom) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_has_key_axiom(buf, axiom);
    return cowl_str_buf_to_string(buf);
}

bool cowl_has_key_axiom_equals(CowlHasKeyAxiom *lhs, CowlHasKeyAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_cls_exp_equals(lhs->cls_exp, rhs->cls_exp) &&
                                  cowl_obj_prop_exp_set_equals(lhs->obj_props, rhs->obj_props) &&
                                  cowl_data_prop_exp_set_equals(lhs->data_props, rhs->data_props));
}

cowl_uint_t cowl_has_key_axiom_hash(CowlHasKeyAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_has_key_axiom_iterate_signature(CowlHasKeyAxiom *axiom, CowlEntityIterator *iter) {
    if (!cowl_cls_exp_iterate_signature(axiom->cls_exp, iter)) return false;
    if (!cowl_obj_prop_exp_set_iterate_signature(axiom->obj_props, iter)) return false;
    if (!cowl_data_prop_exp_set_iterate_signature(axiom->data_props, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}

bool cowl_has_key_axiom_iterate_anon_inds(CowlHasKeyAxiom *axiom, CowlAnonIndIterator *iter) {
    if (!cowl_cls_exp_iterate_anon_inds(axiom->cls_exp, iter)) return false;
    if (!cowl_axiom_annot_iterate_anon_inds(axiom, iter)) return false;
    return true;
}
