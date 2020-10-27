/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_obj_prop_axiom_private.h"
#include "cowl_obj_prop_exp_set.h"
#include "cowl_macros.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_alloc(CowlAxiomType type,
                                                            CowlObjPropExpSet *props,
                                                            CowlAnnotationVec *annot) {
    CowlNAryObjPropAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_NARY_OBJ_PROP_AXIOM, annot, type,
                                         cowl_obj_prop_exp_set_hash(props));

    cowl_axiom_init(CowlNAryObjPropAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .props = props
    );

    return axiom;
}

static void cowl_nary_obj_prop_axiom_free(CowlNAryObjPropAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_set_free(axiom->props);
    cowl_axiom_free(axiom);
}

CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_get(CowlNAryAxiomType type,
                                                   CowlObjPropExpSet *props,
                                                   CowlAnnotationVec *annot) {
    if (!(props && cowl_enum_value_is_valid(NAT, type))) return NULL;
    CowlAxiomType axiom_type = (CowlAxiomType)type + COWL_AT_EQUIV_OBJ_PROP;
    return cowl_nary_obj_prop_axiom_alloc(axiom_type, props, annot);
}

CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_retain(CowlNAryObjPropAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_nary_obj_prop_axiom_release(CowlNAryObjPropAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_nary_obj_prop_axiom_free(axiom);
    }
}

CowlNAryAxiomType cowl_nary_obj_prop_axiom_get_type(CowlNAryObjPropAxiom *axiom) {
    return (CowlNAryAxiomType)(cowl_get_type(axiom) - COWL_OT_A_EQUIV_OBJ_PROP);
}

CowlObjPropExpSet* cowl_nary_obj_prop_axiom_get_props(CowlNAryObjPropAxiom *axiom) {
    return axiom->props;
}

CowlAnnotationVec* cowl_nary_obj_prop_axiom_get_annot(CowlNAryObjPropAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_nary_obj_prop_axiom_to_string(CowlNAryObjPropAxiom *axiom)
    COWL_TO_STRING_IMPL(nary_obj_prop_axiom, axiom)

bool cowl_nary_obj_prop_axiom_equals(CowlNAryObjPropAxiom *lhs, CowlNAryObjPropAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs, cowl_obj_prop_exp_set_equals(lhs->props, rhs->props));
}

cowl_uint_t cowl_nary_obj_prop_axiom_hash(CowlNAryObjPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_obj_prop_axiom_iterate_signature(CowlNAryObjPropAxiom *axiom,
                                                CowlEntityIterator *iter) {
    if (cowl_obj_prop_exp_set_iterate_signature(axiom->props, iter) &&
        cowl_axiom_annot_iterate_signature(axiom, iter)) {
        return true;
    }
    return false;
}

bool cowl_nary_obj_prop_axiom_iterate_primitives(CowlNAryObjPropAxiom *axiom,
                                                 CowlPrimitiveIterator *iter) {
    if (cowl_obj_prop_exp_set_iterate_primitives(axiom->props, iter) &&
        cowl_axiom_annot_iterate_primitives(axiom, iter)) {
        return true;
    }
    return false;
}
