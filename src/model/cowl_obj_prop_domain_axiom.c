/// @author Ivano Bilenchi

#include "cowl_obj_prop_domain_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"

static CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_alloc(CowlObjPropExp *prop,
                                                                CowlClsExp *domain) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_OBJ_PROP_DOMAIN_AXIOM,
                                   cowl_obj_prop_exp_hash(prop),
                                   cowl_cls_exp_hash(domain));

    CowlObjPropDomainAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_OBJ_PROP_DOMAIN, hash),
        .prop_exp = cowl_obj_prop_exp_retain(prop),
        .domain = cowl_cls_exp_retain(domain)
    };

    cowl_struct(CowlObjPropDomainAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_obj_prop_domain_axiom_free(CowlObjPropDomainAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_release(axiom->prop_exp);
    cowl_cls_exp_release(axiom->domain);
    free((void *)axiom);
}

CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_get(CowlObjPropExp *prop, CowlClsExp *domain) {
    return cowl_obj_prop_domain_axiom_alloc(prop, domain);
}

CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_retain(CowlObjPropDomainAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_obj_prop_domain_axiom_release(CowlObjPropDomainAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_obj_prop_domain_axiom_free(axiom);
    }
}

CowlObjPropExp* cowl_obj_prop_domain_axiom_get_prop(CowlObjPropDomainAxiom *axiom) {
    return axiom->prop_exp;
}

CowlClsExp* cowl_obj_prop_domain_axiom_get_domain(CowlObjPropDomainAxiom *axiom) {
    return axiom->domain;
}

bool cowl_obj_prop_domain_axiom_equals(CowlObjPropDomainAxiom *lhs, CowlObjPropDomainAxiom *rhs) {
    return cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
           cowl_cls_exp_equals(lhs->domain, rhs->domain);
}

cowl_uint_t cowl_obj_prop_domain_axiom_hash(CowlObjPropDomainAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_obj_prop_domain_axiom_iterate_signature(CowlObjPropDomainAxiom *axiom,
                                                  void *ctx, CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_iterate_signature(axiom->prop_exp, ctx, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(axiom->domain, ctx, iter)) return false;
    return true;
}
