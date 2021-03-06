/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_assert_axiom_private.h"
#include "cowl_individual.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_alloc(CowlAxiomType type,
                                                                CowlIndividual *source,
                                                                CowlObjPropExp *prop,
                                                                CowlIndividual *target,
                                                                CowlAnnotationVec *annot) {
    CowlObjPropAssertAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint hash = cowl_axiom_hash_4(COWL_HASH_INIT_OBJ_PROP_ASSERT_AXIOM, annot, type,
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
    if (!axiom) return;
    cowl_individual_release(axiom->subject);
    cowl_individual_release(axiom->object);
    cowl_obj_prop_exp_release(axiom->prop_exp);
    cowl_axiom_free(axiom);
}

CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_get(CowlIndividual *subject,
                                                       CowlObjPropExp *prop,
                                                       CowlIndividual *object,
                                                       CowlAnnotationVec *annot) {
    if (!(subject && prop && object)) return NULL;
    return cowl_obj_prop_assert_axiom_alloc(COWL_AT_OBJ_PROP_ASSERT, subject, prop, object, annot);
}

CowlObjPropAssertAxiom* cowl_neg_obj_prop_assert_axiom_get(CowlIndividual *subject,
                                                           CowlObjPropExp *prop,
                                                           CowlIndividual *object,
                                                           CowlAnnotationVec *annot) {
    return cowl_obj_prop_assert_axiom_alloc(COWL_AT_NEG_OBJ_PROP_ASSERT, subject, prop,
                                            object, annot);
}

CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_retain(CowlObjPropAssertAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_obj_prop_assert_axiom_release(CowlObjPropAssertAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
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

CowlAnnotationVec* cowl_obj_prop_assert_axiom_get_annot(CowlObjPropAssertAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_obj_prop_assert_axiom_to_string(CowlObjPropAssertAxiom *axiom)
    COWL_TO_STRING_IMPL(obj_prop_assert, axiom)

bool cowl_obj_prop_assert_axiom_equals(CowlObjPropAssertAxiom *lhs, CowlObjPropAssertAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_individual_equals(lhs->subject, rhs->subject) &&
                                  cowl_individual_equals(lhs->object, rhs->object) &&
                                  cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp));
}

cowl_uint cowl_obj_prop_assert_axiom_hash(CowlObjPropAssertAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_obj_prop_assert_axiom_iterate_primitives(CowlObjPropAssertAxiom *axiom,
                                                   CowlIterator *iter, CowlPrimitiveFlags flags) {
    return (cowl_individual_iterate_primitives(axiom->subject, iter, flags) &&
            cowl_individual_iterate_primitives(axiom->object, iter, flags) &&
            cowl_obj_prop_exp_iterate_primitives(axiom->prop_exp, iter, flags) &&
            cowl_axiom_annot_iterate_primitives(axiom, iter, flags));
}
