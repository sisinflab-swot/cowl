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
#include "cowl_macros.h"
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
    if (!(prop && cowl_enum_value_is_valid(CAT, type))) return NULL;
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
    return (CowlCharAxiomType)(cowl_get_type(axiom) - COWL_OT_A_FUNC_OBJ_PROP);
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

bool cowl_obj_prop_char_axiom_iterate_primitives(CowlObjPropCharAxiom *axiom, CowlIterator *iter,
                                                 CowlPrimitiveFlags flags) {
    return (cowl_obj_prop_exp_iterate_primitives(axiom->prop_exp, iter, flags) &&
            cowl_axiom_annot_iterate_primitives(axiom, iter, flags));
}
