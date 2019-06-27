/// @author Ivano Bilenchi

#include "cowl_obj_prop_assert_axiom_private.h"
#include "cowl_individual.h"
#include "cowl_obj_prop_exp.h"

static CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_alloc(CowlAxiomType type,
                                                                CowlIndividual *source,
                                                                CowlObjPropExp *prop,
                                                                CowlIndividual *target,
                                                                CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_4(COWL_HASH_INIT_OBJ_PROP_ASSERT_AXIOM, annot, type,
                                         cowl_individual_hash(source),
                                         cowl_individual_hash(target),
                                         cowl_obj_prop_exp_hash(prop));

    CowlObjPropAssertAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_OBJ_PROP_ASSERTION, hash, annot),
        .source = cowl_individual_retain(source),
        .target = cowl_individual_retain(target),
        .prop_exp = cowl_obj_prop_exp_retain(prop)
    };

    cowl_struct(CowlObjPropAssertAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_obj_prop_assert_axiom_free(CowlObjPropAssertAxiom *axiom) {
    if (!axiom) return;
    cowl_individual_release(axiom->source);
    cowl_individual_release(axiom->target);
    cowl_obj_prop_exp_release(axiom->prop_exp);
    cowl_axiom_free(axiom);
}

CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_get(CowlIndividual *source,
                                                       CowlObjPropExp *prop,
                                                       CowlIndividual *target,
                                                       CowlAnnotationVec *annot) {
    return cowl_obj_prop_assert_axiom_alloc(CAT_OBJ_PROP_ASSERTION, source, prop, target, annot);
}

CowlObjPropAssertAxiom* cowl_neg_obj_prop_assert_axiom_get(CowlIndividual *source,
                                                           CowlObjPropExp *prop,
                                                           CowlIndividual *target,
                                                           CowlAnnotationVec *annot) {
    return cowl_obj_prop_assert_axiom_alloc(CAT_NEGATIVE_OBJ_PROP_ASSERTION, source, prop,
                                            target, annot);
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
    return cowl_axiom_flags_get_type(axiom->super.flags) == CAT_NEGATIVE_OBJ_PROP_ASSERTION;
}

CowlIndividual* cowl_obj_prop_assert_axiom_get_source(CowlObjPropAssertAxiom *axiom) {
    return axiom->source;
}

CowlIndividual* cowl_obj_prop_assert_axiom_get_target(CowlObjPropAssertAxiom *axiom) {
    return axiom->target;
}

CowlObjPropExp* cowl_obj_prop_assert_axiom_get_prop(CowlObjPropAssertAxiom *axiom) {
    return axiom->prop_exp;
}

CowlAnnotationVec* cowl_obj_prop_assert_axiom_get_annot(CowlObjPropAssertAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

bool cowl_obj_prop_assert_axiom_equals(CowlObjPropAssertAxiom *lhs, CowlObjPropAssertAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_individual_equals(lhs->source, rhs->source) &&
                                  cowl_individual_equals(lhs->target, rhs->target) &&
                                  cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp));
}

cowl_uint_t cowl_obj_prop_assert_axiom_hash(CowlObjPropAssertAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_obj_prop_assert_axiom_iterate_signature(CowlObjPropAssertAxiom *axiom,
                                                  CowlEntityIterator *iter) {
    if (!cowl_individual_iterate_signature(axiom->source, iter)) return false;
    if (!cowl_individual_iterate_signature(axiom->target, iter)) return false;
    if (!cowl_obj_prop_exp_iterate_signature(axiom->prop_exp, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}
