/// @author Ivano Bilenchi

#include "cowl_obj_prop_assert_axiom_private.h"
#include "cowl_hash_utils.h"
#include "cowl_individual.h"
#include "cowl_obj_prop_exp.h"

static CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_alloc(CowlIndividual *source,
                                                                CowlObjPropExp *prop,
                                                                CowlIndividual *target) {
    cowl_uint_t hash = cowl_hash_3(COWL_HASH_INIT_OBJ_PROP_ASSERT_AXIOM,
                                   cowl_individual_hash(source),
                                   cowl_individual_hash(target),
                                   cowl_obj_prop_exp_hash(prop));

    CowlObjPropAssertAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_OBJ_PROP_ASSERTION, hash),
        .source = cowl_individual_retain(source),
        .target = cowl_individual_retain(target),
        .prop_exp = cowl_obj_prop_exp_retain(prop)
    };

    struct CowlObjPropAssertAxiom *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_obj_prop_assert_axiom_free(CowlObjPropAssertAxiom *axiom) {
    if (!axiom) return;
    cowl_individual_release(axiom->source);
    cowl_individual_release(axiom->target);
    cowl_obj_prop_exp_release(axiom->prop_exp);
    free((void *)axiom);
}

CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_get(CowlIndividual *source, CowlObjPropExp *prop,
                                                       CowlIndividual *target) {
    return cowl_obj_prop_assert_axiom_alloc(source, prop, target);
}

CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_retain(CowlObjPropAssertAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_obj_prop_assert_axiom_release(CowlObjPropAssertAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_obj_prop_assert_axiom_free(axiom);
    }
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

bool cowl_obj_prop_assert_axiom_equals(CowlObjPropAssertAxiom *lhs, CowlObjPropAssertAxiom *rhs) {
    return cowl_individual_equals(lhs->source, rhs->source) &&
           cowl_individual_equals(lhs->target, rhs->target) &&
           cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp);
}

cowl_uint_t cowl_obj_prop_assert_axiom_hash(CowlObjPropAssertAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_obj_prop_assert_axiom_iterate_signature(CowlObjPropAssertAxiom *axiom,
                                                  void *ctx, CowlEntityIterator iter) {
    if (!cowl_individual_iterate_signature(axiom->source, ctx, iter)) return false;
    if (!cowl_individual_iterate_signature(axiom->target, ctx, iter)) return false;
    if (!cowl_obj_prop_exp_iterate_signature(axiom->prop_exp, ctx, iter)) return false;
    return true;
}
