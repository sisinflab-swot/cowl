/// @author Ivano Bilenchi

#include "cowl_data_prop_assert_axiom_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_individual.h"
#include "cowl_literal.h"

static CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_alloc(CowlAxiomType type,
                                                                  CowlIndividual *source,
                                                                  CowlDataPropExp *prop,
                                                                  CowlLiteral *target,
                                                                  CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_4(COWL_HASH_INIT_DATA_PROP_ASSERT_AXIOM, annot, type,
                                         cowl_individual_hash(source),
                                         cowl_data_prop_exp_hash(prop),
                                         cowl_literal_hash(target));

    CowlDataPropAssertAxiom init = {
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .source = cowl_individual_retain(source),
        .prop = cowl_data_prop_exp_retain(prop),
        .target = cowl_literal_retain(target)
    };

    cowl_struct(CowlDataPropAssertAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_data_prop_assert_axiom_free(CowlDataPropAssertAxiom *axiom) {
    if (!axiom) return;
    cowl_individual_release(axiom->source);
    cowl_data_prop_exp_release(axiom->prop);
    cowl_literal_release(axiom->target);
    cowl_axiom_free(axiom);
}

CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_get(CowlIndividual *source,
                                                         CowlDataPropExp *prop,
                                                         CowlLiteral *target,
                                                         CowlAnnotationVec *annot) {
    return cowl_data_prop_assert_axiom_alloc(CAT_DATA_PROP_ASSERTION, source, prop, target, annot);
}

CowlDataPropAssertAxiom* cowl_neg_data_prop_assert_axiom_get(CowlIndividual *source,
                                                             CowlDataPropExp *prop,
                                                             CowlLiteral *target,
                                                             CowlAnnotationVec *annot) {
    return cowl_data_prop_assert_axiom_alloc(CAT_NEGATIVE_DATA_PROP_ASSERTION,
                                             source, prop, target, annot);
}

CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_retain(CowlDataPropAssertAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_data_prop_assert_axiom_release(CowlDataPropAssertAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_data_prop_assert_axiom_free(axiom);
    }
}

bool cowl_data_prop_assert_axiom_is_negative(CowlDataPropAssertAxiom *axiom) {
    return cowl_axiom_flags_get_type(axiom->super.flags) == CAT_NEGATIVE_DATA_PROP_ASSERTION;
}

CowlIndividual* cowl_data_prop_assert_axiom_get_source(CowlDataPropAssertAxiom *axiom) {
    return axiom->source;
}

CowlLiteral* cowl_data_prop_assert_axiom_get_target(CowlDataPropAssertAxiom *axiom) {
    return axiom->target;
}

CowlDataPropExp* cowl_data_prop_assert_axiom_get_prop(CowlDataPropAssertAxiom *axiom) {
    return axiom->prop;
}

CowlAnnotationVec* cowl_data_prop_assert_axiom_get_annot(CowlDataPropAssertAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

bool cowl_data_prop_assert_axiom_equals(CowlDataPropAssertAxiom *lhs,
                                        CowlDataPropAssertAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_literal_equals(lhs->target, rhs->target) &&
                                  cowl_data_prop_exp_equals(lhs->prop, rhs->prop) &&
                                  cowl_individual_equals(lhs->source, rhs->source));
}

cowl_uint_t cowl_data_prop_assert_axiom_hash(CowlDataPropAssertAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_data_prop_assert_axiom_iterate_signature(CowlDataPropAssertAxiom *axiom,
                                                   void *ctx, CowlEntityIterator iter) {
    if (!cowl_individual_iterate_signature(axiom->source, ctx, iter)) return false;
    if (!cowl_data_prop_exp_iterate_signature(axiom->prop, ctx, iter)) return false;
    if (!cowl_literal_iterate_signature(axiom->target, ctx, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, ctx, iter)) return false;
    return true;
}
