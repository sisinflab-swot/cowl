/// @author Ivano Bilenchi

#include "cowl_data_prop_domain_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_data_prop_exp.h"
#include "cowl_hash_utils.h"

static CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_alloc(CowlDataPropExp *prop,
                                                                CowlClsExp *domain) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_DATA_PROP_DOMAIN_AXIOM,
                                   cowl_data_prop_exp_hash(prop),
                                   cowl_cls_exp_hash(domain));

    CowlDataPropDomainAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_DATA_PROP_DOMAIN, hash),
        .prop_exp = cowl_data_prop_exp_retain(prop),
        .domain = cowl_cls_exp_retain(domain)
    };

    cowl_struct(CowlDataPropDomainAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_data_prop_domain_axiom_free(CowlDataPropDomainAxiom *axiom) {
    if (!axiom) return;
    cowl_data_prop_exp_release(axiom->prop_exp);
    cowl_cls_exp_release(axiom->domain);
    free((void *)axiom);
}

CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_get(CowlDataPropExp *prop, CowlClsExp *domain) {
    return cowl_data_prop_domain_axiom_alloc(prop, domain);
}

CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_retain(CowlDataPropDomainAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_data_prop_domain_axiom_release(CowlDataPropDomainAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_data_prop_domain_axiom_free(axiom);
    }
}

CowlDataPropExp* cowl_data_prop_domain_axiom_get_prop(CowlDataPropDomainAxiom *axiom) {
    return axiom->prop_exp;
}

CowlClsExp* cowl_data_prop_domain_axiom_get_domain(CowlDataPropDomainAxiom *axiom) {
    return axiom->domain;
}

bool cowl_data_prop_domain_axiom_equals(CowlDataPropDomainAxiom *lhs, CowlDataPropDomainAxiom *rhs) {
    return cowl_data_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
           cowl_cls_exp_equals(lhs->domain, rhs->domain);
}

cowl_uint_t cowl_data_prop_domain_axiom_hash(CowlDataPropDomainAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_data_prop_domain_axiom_iterate_signature(CowlDataPropDomainAxiom *axiom,
                                                  void *ctx, CowlEntityIterator iter) {
    if (!cowl_data_prop_exp_iterate_signature(axiom->prop_exp, ctx, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(axiom->domain, ctx, iter)) return false;
    return true;
}
