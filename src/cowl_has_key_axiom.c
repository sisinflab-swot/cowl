/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_has_key_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_object_table.h"
#include "cowl_template.h"

static CowlHasKeyAxiom* cowl_has_key_axiom_alloc(CowlClsExp *cls_exp, CowlObjectTable *obj_props,
                                                 CowlObjectTable *data_props,
                                                 CowlObjectVec *annot) {
    CowlHasKeyAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    ulib_uint obj_props_hash = obj_props ? cowl_object_set_hash(obj_props) : 0;
    ulib_uint data_props_hash = data_props ? cowl_object_set_hash(data_props) : 0;
    ulib_uint hash = cowl_axiom_hash_3(COWL_HASH_INIT_HAS_KEY_AXIOM, annot,
                                       cowl_cls_exp_hash(cls_exp),
                                       obj_props_hash, data_props_hash);

    cowl_axiom_init(CowlHasKeyAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_HAS_KEY, hash, annot),
        .cls_exp = cowl_cls_exp_retain(cls_exp),
        .obj_props = obj_props,
        .data_props = data_props
    );

    return axiom;
}

static void cowl_has_key_axiom_free(CowlHasKeyAxiom *axiom) {
    cowl_cls_exp_release(axiom->cls_exp);
    cowl_object_set_free(axiom->obj_props);
    cowl_object_set_free(axiom->data_props);
    cowl_axiom_free(axiom);
}

CowlHasKeyAxiom* cowl_has_key_axiom_get(CowlClsExp *cls_exp, CowlObjectTable *obj_props,
                                        CowlObjectTable *data_props, CowlObjectVec *annot) {
    if (!cls_exp) return NULL;
    return cowl_has_key_axiom_alloc(cls_exp, obj_props, data_props, annot);
}

CowlHasKeyAxiom* cowl_has_key_axiom_retain(CowlHasKeyAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_has_key_axiom_release(CowlHasKeyAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_has_key_axiom_free(axiom);
    }
}

CowlClsExp* cowl_has_key_axiom_get_cls_exp(CowlHasKeyAxiom *axiom) {
    return axiom->cls_exp;
}

CowlObjectTable* cowl_has_key_axiom_get_obj_props(CowlHasKeyAxiom *axiom) {
    return axiom->obj_props;
}

CowlObjectTable* cowl_has_key_axiom_get_data_props(CowlHasKeyAxiom *axiom) {
    return axiom->data_props;
}

CowlObjectVec* cowl_has_key_axiom_get_annot(CowlHasKeyAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_has_key_axiom_to_string(CowlHasKeyAxiom *axiom)
    COWL_TO_STRING_IMPL(has_key_axiom, axiom)

bool cowl_has_key_axiom_equals(CowlHasKeyAxiom *lhs, CowlHasKeyAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_cls_exp_equals(lhs->cls_exp, rhs->cls_exp) &&
                                  cowl_object_set_equals(lhs->obj_props, rhs->obj_props) &&
                                  cowl_object_set_equals(lhs->data_props, rhs->data_props));
}

ulib_uint cowl_has_key_axiom_hash(CowlHasKeyAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_has_key_axiom_iterate_primitives(CowlHasKeyAxiom *axiom, CowlPrimitiveFlags flags,
                                           CowlIterator *iter) {
    return (cowl_cls_exp_iterate_primitives(axiom->cls_exp, flags, iter) &&
            cowl_object_set_iterate_primitives(axiom->obj_props, flags, iter) &&
            cowl_object_set_iterate_primitives(axiom->data_props, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
