/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_inv_obj_prop_axiom_private.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_alloc(CowlObjPropExp *first,
                                                          CowlObjPropExp *second,
                                                          CowlAnnotationVec *annot) {
    CowlInvObjPropAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint hash = cowl_axiom_hash_2(COWL_HASH_INIT_INV_OBJ_PROP_AXIOM, annot,
                                       cowl_obj_prop_exp_hash(first),
                                       cowl_obj_prop_exp_hash(second));

    cowl_axiom_init(CowlInvObjPropAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_INV_OBJ_PROP, hash, annot),
        .first = cowl_obj_prop_exp_retain(first),
        .second = cowl_obj_prop_exp_retain(second)
    );

    return axiom;
}

static void cowl_inv_obj_prop_axiom_free(CowlInvObjPropAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_release(axiom->first);
    cowl_obj_prop_exp_release(axiom->second);
    cowl_axiom_free(axiom);
}

CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_get(CowlObjPropExp *first, CowlObjPropExp *second,
                                                 CowlAnnotationVec *annot) {
    if (!(first && second)) return NULL;
    return cowl_inv_obj_prop_axiom_alloc(first, second, annot);
}

CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_retain(CowlInvObjPropAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_inv_obj_prop_axiom_release(CowlInvObjPropAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_inv_obj_prop_axiom_free(axiom);
    }
}

CowlObjPropExp* cowl_inv_obj_prop_axiom_get_first_prop(CowlInvObjPropAxiom *axiom) {
    return axiom->first;
}

CowlObjPropExp* cowl_inv_obj_prop_axiom_get_second_prop(CowlInvObjPropAxiom *axiom) {
    return axiom->second;
}

CowlAnnotationVec* cowl_inv_obj_prop_axiom_get_annot(CowlInvObjPropAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_inv_obj_prop_axiom_to_string(CowlInvObjPropAxiom *axiom)
    COWL_TO_STRING_IMPL(inv_obj_prop_axiom, axiom)

bool cowl_inv_obj_prop_axiom_equals(CowlInvObjPropAxiom *lhs, CowlInvObjPropAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_obj_prop_exp_equals(lhs->first, rhs->first) &&
                                  cowl_obj_prop_exp_equals(lhs->second, rhs->second));
}

cowl_uint cowl_inv_obj_prop_axiom_hash(CowlInvObjPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_inv_obj_prop_axiom_iterate_primitives(CowlInvObjPropAxiom *axiom, CowlIterator *iter,
                                                CowlPrimitiveFlags flags) {
    return (cowl_obj_prop_exp_iterate_primitives(axiom->first, iter, flags) &&
            cowl_obj_prop_exp_iterate_primitives(axiom->second, iter, flags) &&
            cowl_axiom_annot_iterate_primitives(axiom, iter, flags));
}
