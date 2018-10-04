/// @author Ivano Bilenchi

#include "cowl_obj_prop_assert_axiom_private.h"
#include "cowl_hash_utils.h"
#include "cowl_individual.h"
#include "cowl_obj_prop_exp.h"

CowlIndividual const* cowl_obj_prop_assert_axiom_get_source(CowlObjPropAssertAxiom const *axiom) {
    return axiom->source;
}

CowlIndividual const* cowl_obj_prop_assert_axiom_get_target(CowlObjPropAssertAxiom const *axiom) {
    return axiom->target;
}

CowlObjPropExp const* cowl_obj_prop_assert_axiom_get_prop(CowlObjPropAssertAxiom const *axiom) {
    return axiom->prop_exp;
}

bool cowl_obj_prop_assert_axiom_enum_signature(CowlObjPropAssertAxiom const *axiom,
                                               void *ctx, CowlEntityIterator iter) {
    if (!cowl_individual_enum_signature(axiom->source, ctx, iter)) return false;
    if (!cowl_individual_enum_signature(axiom->target, ctx, iter)) return false;
    if (!cowl_obj_prop_exp_enum_signature(axiom->prop_exp, ctx, iter)) return false;
    return true;
}

bool cowl_obj_prop_assert_axiom_equals(CowlObjPropAssertAxiom const *lhs,
                                       CowlObjPropAssertAxiom const *rhs) {
    return cowl_individual_equals(lhs->source, rhs->source) &&
           cowl_individual_equals(lhs->target, rhs->target) &&
           cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp);
}

uint32_t cowl_obj_prop_assert_axiom_hash(CowlObjPropAssertAxiom const *axiom) {
    return cowl_hash_3(COWL_HASH_INIT_OBJ_PROP_ASSERT_AXIOM,
                       cowl_individual_hash(axiom->source),
                       cowl_individual_hash(axiom->target),
                       cowl_obj_prop_exp_hash(axiom->prop_exp));
}
