/// @author Ivano Bilenchi

#include "cowl_data_prop_assert_axiom_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_hash_utils.h"
#include "cowl_individual.h"
#include "cowl_literal.h"

static CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_alloc(CowlAxiomType type,
                                                                  CowlIndividual *source,
                                                                  CowlDataPropExp *prop,
                                                                  CowlLiteral *target) {
    cowl_uint_t hash = cowl_hash_4(COWL_HASH_INIT_DATA_PROP_ASSERT_AXIOM, type,
                                   cowl_individual_hash(source),
                                   cowl_data_prop_exp_hash(prop),
                                   cowl_literal_hash(target));

    CowlDataPropAssertAxiom init = {
        .super = COWL_AXIOM_INIT(type, hash),
        .source = cowl_individual_retain(source),
        .prop = cowl_data_prop_exp_retain(prop),
        .target = cowl_literal_retain(target)
    };

    cowl_struct(CowlDataPropAssertAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_data_prop_assert_axiom_free(CowlDataPropAssertAxiom *axiom) {
    if (!axiom) return;
    cowl_individual_release(axiom->source);
    cowl_data_prop_exp_release(axiom->prop);
    cowl_literal_release(axiom->target);
    free((void *)axiom);
}

CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_get(CowlIndividual *source,
                                                         CowlDataPropExp *prop,
                                                         CowlLiteral *target) {
    return cowl_data_prop_assert_axiom_alloc(CAT_DATA_PROP_ASSERTION, source, prop, target);
}

CowlDataPropAssertAxiom* cowl_neg_data_prop_assert_axiom_get(CowlIndividual *source,
                                                             CowlDataPropExp *prop,
                                                             CowlLiteral *target) {
    return cowl_data_prop_assert_axiom_alloc(CAT_NEGATIVE_DATA_PROP_ASSERTION,
                                             source, prop, target);
}

CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_retain(CowlDataPropAssertAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_data_prop_assert_axiom_release(CowlDataPropAssertAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_data_prop_assert_axiom_free(axiom);
    }
}

bool cowl_data_prop_assert_axiom_is_negative(CowlDataPropAssertAxiom *axiom) {
    return axiom->super.type == CAT_NEGATIVE_DATA_PROP_ASSERTION;
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

bool cowl_data_prop_assert_axiom_equals(CowlDataPropAssertAxiom *lhs,
                                        CowlDataPropAssertAxiom *rhs) {
    return lhs->super.type == rhs->super.type &&
           cowl_literal_equals(lhs->target, rhs->target) &&
           cowl_data_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_individual_equals(lhs->source, rhs->source);
}

cowl_uint_t cowl_data_prop_assert_axiom_hash(CowlDataPropAssertAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_data_prop_assert_axiom_iterate_signature(CowlDataPropAssertAxiom *axiom,
                                                   void *ctx, CowlEntityIterator iter) {
    if (!cowl_individual_iterate_signature(axiom->source, ctx, iter)) return false;
    if (!cowl_data_prop_exp_iterate_signature(axiom->prop, ctx, iter)) return false;
    if (!cowl_literal_iterate_signature(axiom->target, ctx, iter)) return false;
    return true;
}
