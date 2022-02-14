/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_char_axiom_private.h"
#include "cowl_macros.h"
#include "cowl_obj_prop_exp_private.h"
#include "cowl_template.h"

static CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_alloc(CowlAxiomType type,
                                                            CowlObjPropExp *prop,
                                                            CowlObjectVec *annot) {
    CowlObjPropCharAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    ulib_uint hash = cowl_axiom_hash_2(COWL_HASH_INIT_OBJ_PROP_CHAR_AXIOM, annot, type,
                                       cowl_obj_prop_exp_hash(prop));

    cowl_axiom_init(CowlObjPropCharAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .prop_exp = cowl_obj_prop_exp_retain(prop)
    );

    return axiom;
}

static void cowl_obj_prop_char_axiom_free(CowlObjPropCharAxiom *axiom) {
    cowl_obj_prop_exp_release(axiom->prop_exp);
    cowl_axiom_free(axiom);
}

CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_get(CowlCharAxiomType type,
                                                   CowlObjPropExp *prop,
                                                   CowlObjectVec *annot) {
    if (!(prop && cowl_enum_value_is_valid(CAT, type))) return NULL;
    CowlAxiomType axiom_type = (CowlAxiomType)type + COWL_AT_FUNC_OBJ_PROP;
    return cowl_obj_prop_char_axiom_alloc(axiom_type, prop, annot);
}

CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_retain(CowlObjPropCharAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_obj_prop_char_axiom_release(CowlObjPropCharAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_obj_prop_char_axiom_free(axiom);
    }
}

CowlCharAxiomType cowl_obj_prop_char_axiom_get_type(CowlObjPropCharAxiom *axiom) {
    return (CowlCharAxiomType)(cowl_get_type(axiom) - COWL_OT_A_FUNC_OBJ_PROP);
}

CowlObjPropExp* cowl_obj_prop_char_axiom_get_prop(CowlObjPropCharAxiom *axiom) {
    return axiom->prop_exp;
}

CowlObjectVec* cowl_obj_prop_char_axiom_get_annot(CowlObjPropCharAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_obj_prop_char_axiom_to_string(CowlObjPropCharAxiom *axiom)
    COWL_TO_STRING_IMPL(obj_prop_char, axiom)

bool cowl_obj_prop_char_axiom_equals(CowlObjPropCharAxiom *lhs, CowlObjPropCharAxiom *rhs) {
    return cowl_object_type_equals(lhs, rhs) &&
           cowl_axiom_equals_impl(lhs, rhs, cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp));
}

ulib_uint cowl_obj_prop_char_axiom_hash(CowlObjPropCharAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_obj_prop_char_axiom_iterate_primitives(CowlObjPropCharAxiom *axiom,
                                                 CowlPrimitiveFlags flags, CowlIterator *iter) {
    return (cowl_obj_prop_exp_iterate_primitives(axiom->prop_exp, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
