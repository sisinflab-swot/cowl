/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_assert_axiom_private.h"
#include "cowl_individual.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_template.h"

static CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_alloc(CowlAxiomType type,
                                                                CowlIndividual *source,
                                                                CowlObjPropExp *prop,
                                                                CowlIndividual *target,
                                                                CowlObjectVec *annot) {
    CowlObjPropAssertAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    ulib_uint hash = cowl_axiom_hash_4(COWL_HASH_INIT_OBJ_PROP_ASSERT_AXIOM, annot, type,
                                       cowl_individual_hash(source),
                                       cowl_individual_hash(target),
                                       cowl_obj_prop_exp_hash(prop));

    cowl_axiom_init(CowlObjPropAssertAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .subject = cowl_individual_retain(source),
        .object = cowl_individual_retain(target),
        .prop_exp = cowl_obj_prop_exp_retain(prop)
    );

    return axiom;
}

static void cowl_obj_prop_assert_axiom_free(CowlObjPropAssertAxiom *axiom) {
    cowl_individual_release(axiom->subject);
    cowl_individual_release(axiom->object);
    cowl_obj_prop_exp_release(axiom->prop_exp);
    cowl_axiom_free(axiom);
}

CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_get(CowlIndividual *subject,
                                                       CowlObjPropExp *prop,
                                                       CowlIndividual *object,
                                                       CowlObjectVec *annot) {
    if (!(subject && prop && object)) return NULL;
    return cowl_obj_prop_assert_axiom_alloc(COWL_AT_OBJ_PROP_ASSERT, subject, prop, object, annot);
}

CowlObjPropAssertAxiom* cowl_neg_obj_prop_assert_axiom_get(CowlIndividual *subject,
                                                           CowlObjPropExp *prop,
                                                           CowlIndividual *object,
                                                           CowlObjectVec *annot) {
    return cowl_obj_prop_assert_axiom_alloc(COWL_AT_NEG_OBJ_PROP_ASSERT, subject, prop,
                                            object, annot);
}

CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_retain(CowlObjPropAssertAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_obj_prop_assert_axiom_release(CowlObjPropAssertAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_obj_prop_assert_axiom_free(axiom);
    }
}

bool cowl_obj_prop_assert_axiom_is_negative(CowlObjPropAssertAxiom *axiom) {
    return cowl_get_type(axiom) == COWL_OT_A_NEG_OBJ_PROP_ASSERT;
}

CowlIndividual* cowl_obj_prop_assert_axiom_get_subject(CowlObjPropAssertAxiom *axiom) {
    return axiom->subject;
}

CowlIndividual* cowl_obj_prop_assert_axiom_get_object(CowlObjPropAssertAxiom *axiom) {
    return axiom->object;
}

CowlObjPropExp* cowl_obj_prop_assert_axiom_get_prop(CowlObjPropAssertAxiom *axiom) {
    return axiom->prop_exp;
}

CowlObjectVec* cowl_obj_prop_assert_axiom_get_annot(CowlObjPropAssertAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_obj_prop_assert_axiom_to_string(CowlObjPropAssertAxiom *axiom)
    COWL_TO_STRING_IMPL(obj_prop_assert, axiom)

bool cowl_obj_prop_assert_axiom_equals(CowlObjPropAssertAxiom *lhs, CowlObjPropAssertAxiom *rhs) {
    return cowl_object_type_equals(lhs, rhs) &&
           cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_individual_equals(lhs->subject, rhs->subject) &&
                                  cowl_individual_equals(lhs->object, rhs->object) &&
                                  cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp));
}

ulib_uint cowl_obj_prop_assert_axiom_hash(CowlObjPropAssertAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_obj_prop_assert_axiom_iterate_primitives(CowlObjPropAssertAxiom *axiom,
                                                   CowlPrimitiveFlags flags, CowlIterator *iter) {
    return (cowl_individual_iterate_primitives(axiom->subject, flags, iter) &&
            cowl_individual_iterate_primitives(axiom->object, flags, iter) &&
            cowl_obj_prop_exp_iterate_primitives(axiom->prop_exp, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
