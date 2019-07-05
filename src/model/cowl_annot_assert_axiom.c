/// @author Ivano Bilenchi

#include "cowl_annot_assert_axiom_private.h"
#include "cowl_annot_prop.h"

static CowlAnnotAssertAxiom* cowl_annot_assert_axiom_alloc(CowlAnnotValue subject,
                                                           CowlAnnotProp *prop,
                                                           CowlAnnotValue value,
                                                           CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_3(COWL_HASH_INIT_ANNOT_ASSERT_AXIOM, annot,
                                         cowl_annot_prop_hash(prop),
                                         cowl_annot_value_hash(subject),
                                         cowl_annot_value_hash(value));

    CowlAnnotAssertAxiom init = {
        .super = COWL_AXIOM_INIT(COWL_AT_ANNOT_ASSERT, hash, annot),
        .subject = cowl_annot_value_retain(subject),
        .prop = cowl_annot_prop_retain(prop),
        .value = cowl_annot_value_retain(value)
    };

    cowl_struct(CowlAnnotAssertAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_annot_assert_axiom_free(CowlAnnotAssertAxiom *axiom) {
    if (!axiom) return;
    cowl_annot_value_release(axiom->subject);
    cowl_annot_value_release(axiom->value);
    cowl_annot_prop_release(axiom->prop);
    cowl_axiom_free(axiom);
}

CowlAnnotAssertAxiom* cowl_annot_assert_axiom_get(CowlAnnotValue subject, CowlAnnotProp *prop,
                                                  CowlAnnotValue value, CowlAnnotationVec *annot) {
    return cowl_annot_assert_axiom_alloc(subject, prop, value, annot);
}

CowlAnnotAssertAxiom* cowl_annot_assert_axiom_retain(CowlAnnotAssertAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_annot_assert_axiom_release(CowlAnnotAssertAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_annot_assert_axiom_free(axiom);
    }
}

CowlAnnotValue cowl_annot_assert_axiom_get_subject(CowlAnnotAssertAxiom *axiom) {
    return axiom->subject;
}

CowlAnnotValue cowl_annot_assert_axiom_get_value(CowlAnnotAssertAxiom *axiom) {
    return axiom->value;
}

CowlAnnotProp* cowl_annot_assert_axiom_get_prop(CowlAnnotAssertAxiom *axiom) {
    return axiom->prop;
}

CowlAnnotationVec* cowl_annot_assert_axiom_get_annot(CowlAnnotAssertAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

bool cowl_annot_assert_axiom_equals(CowlAnnotAssertAxiom *lhs, CowlAnnotAssertAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_annot_prop_equals(lhs->prop, rhs->prop) &&
                                  cowl_annot_value_equals(lhs->subject, rhs->subject) &&
                                  cowl_annot_value_equals(lhs->value, rhs->value));
}

cowl_uint_t cowl_annot_assert_axiom_hash(CowlAnnotAssertAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_annot_assert_axiom_iterate_signature(CowlAnnotAssertAxiom *axiom,
                                               CowlEntityIterator *iter) {
    if (!cowl_annot_prop_iterate_signature(axiom->prop, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}
