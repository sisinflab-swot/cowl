/// @author Ivano Bilenchi

#include "cowl_obj_prop_domain_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"

CowlObjPropExp const* cowl_obj_prop_domain_axiom_get_prop(CowlObjPropDomainAxiom const *axiom) {
    return axiom->prop_exp;
}

CowlClsExp const* cowl_obj_prop_domain_axiom_get_domain(CowlObjPropDomainAxiom const *axiom) {
    return axiom->domain;
}

bool cowl_obj_prop_domain_axiom_enum_signature(CowlObjPropDomainAxiom const *axiom,
                                               void *ctx, CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_enum_signature(axiom->prop_exp, ctx, iter)) return false;
    if (!cowl_cls_exp_enum_signature(axiom->domain, ctx, iter)) return false;
    return true;
}

bool cowl_obj_prop_domain_axiom_equals(CowlObjPropDomainAxiom const *lhs,
                                       CowlObjPropDomainAxiom const *rhs) {
    return cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
           cowl_cls_exp_equals(lhs->domain, rhs->domain);
}

uint32_t cowl_obj_prop_domain_axiom_hash(CowlObjPropDomainAxiom const *axiom) {
    return cowl_hash_2(COWL_HASH_INIT_OBJ_PROP_DOMAIN_AXIOM,
                       cowl_obj_prop_exp_hash(axiom->prop_exp),
                       cowl_cls_exp_hash(axiom->domain));
}
