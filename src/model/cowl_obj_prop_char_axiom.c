/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_char_axiom_private.h"
#include "cowl_obj_prop_exp_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_alloc(CowlAxiomType type,
                                                            CowlObjPropExp *prop,
                                                            CowlAnnotationVec *annot) {
    CowlObjPropCharAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_OBJ_PROP_CHAR_AXIOM, annot, type,
                                         cowl_obj_prop_exp_hash(prop));

    cowl_axiom_init(CowlObjPropCharAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .prop_exp = cowl_obj_prop_exp_retain(prop)
    );

    return axiom;
}

static void cowl_obj_prop_char_axiom_free(CowlObjPropCharAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_release(axiom->prop_exp);
    cowl_axiom_free(axiom);
}

CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_get(CowlCharAxiomType type,
                                                   CowlObjPropExp *prop,
                                                   CowlAnnotationVec *annot) {
    CowlAxiomType axiom_type = (CowlAxiomType)type + COWL_AT_FUNC_OBJ_PROP;
    return cowl_obj_prop_char_axiom_alloc(axiom_type, prop, annot);
}

CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_retain(CowlObjPropCharAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_obj_prop_char_axiom_release(CowlObjPropCharAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_obj_prop_char_axiom_free(axiom);
    }
}

CowlCharAxiomType cowl_obj_prop_char_axiom_get_type(CowlObjPropCharAxiom *axiom) {
    CowlAxiomFlags flags = axiom->super.flags;
    return (CowlCharAxiomType)(cowl_axiom_flags_get_type(flags) - COWL_AT_FUNC_OBJ_PROP);
}

CowlObjPropExp* cowl_obj_prop_char_axiom_get_prop(CowlObjPropCharAxiom *axiom) {
    return axiom->prop_exp;
}

CowlAnnotationVec* cowl_obj_prop_char_axiom_get_annot(CowlObjPropCharAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_obj_prop_char_axiom_to_string(CowlObjPropCharAxiom *axiom)
    COWL_TO_STRING_IMPL(obj_prop_char, axiom)

bool cowl_obj_prop_char_axiom_equals(CowlObjPropCharAxiom *lhs, CowlObjPropCharAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs, cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp));
}

cowl_uint_t cowl_obj_prop_char_axiom_hash(CowlObjPropCharAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_obj_prop_char_axiom_iterate_signature(CowlObjPropCharAxiom *axiom,
                                                CowlEntityIterator *iter) {
    if (!cowl_obj_prop_exp_iterate_signature(axiom->prop_exp, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}

bool cowl_obj_prop_char_axiom_iterate_anon_inds(CowlObjPropCharAxiom *axiom,
                                                CowlAnonIndIterator *iter) {
    return cowl_axiom_annot_iterate_anon_inds(axiom, iter);
}
