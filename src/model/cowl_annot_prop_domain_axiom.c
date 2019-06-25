/// @author Ivano Bilenchi

#include "cowl_annot_prop_domain_axiom_private.h"
#include "cowl_annot_prop.h"
#include "cowl_iri.h"

static CowlAnnotPropDomainAxiom* cowl_annot_prop_domain_axiom_alloc(CowlAnnotProp *prop,
                                                                    CowlIRI *domain,
                                                                    CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_ANNOT_PROP_DOMAIN_AXIOM, annot,
                                         cowl_annot_prop_hash(prop),
                                         cowl_iri_hash(domain));

    CowlAnnotPropDomainAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_ANNOT_PROP_DOMAIN, hash, annot),
        .prop = cowl_annot_prop_retain(prop),
        .domain = cowl_iri_retain(domain)
    };

    cowl_struct(CowlAnnotPropDomainAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_annot_prop_domain_axiom_free(CowlAnnotPropDomainAxiom *axiom) {
    if (!axiom) return;
    cowl_annot_prop_release(axiom->prop);
    cowl_iri_release(axiom->domain);
    cowl_axiom_free(axiom);
}

CowlAnnotPropDomainAxiom* cowl_annot_prop_domain_axiom_get(CowlAnnotProp *prop, CowlIRI *domain,
                                                           CowlAnnotationVec *annot) {
    return cowl_annot_prop_domain_axiom_alloc(prop, domain, annot);
}

CowlAnnotPropDomainAxiom* cowl_annot_prop_domain_axiom_retain(CowlAnnotPropDomainAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_annot_prop_domain_axiom_release(CowlAnnotPropDomainAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_annot_prop_domain_axiom_free(axiom);
    }
}

CowlAnnotProp* cowl_annot_prop_domain_axiom_get_prop(CowlAnnotPropDomainAxiom *axiom) {
    return axiom->prop;
}

CowlIRI* cowl_annot_prop_domain_axiom_get_domain(CowlAnnotPropDomainAxiom *axiom) {
    return axiom->domain;
}

CowlAnnotationVec* cowl_annot_prop_domain_axiom_get_annot(CowlAnnotPropDomainAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

bool cowl_annot_prop_domain_axiom_equals(CowlAnnotPropDomainAxiom *lhs,
                                         CowlAnnotPropDomainAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_iri_equals(lhs->domain, rhs->domain) &&
                                  cowl_annot_prop_equals(lhs->prop, rhs->prop));
}

cowl_uint_t cowl_annot_prop_domain_axiom_hash(CowlAnnotPropDomainAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_annot_prop_domain_axiom_iterate_signature(CowlAnnotPropDomainAxiom *axiom,
                                                    void *ctx, CowlEntityIterator iter) {
    if (!cowl_annot_prop_iterate_signature(axiom->prop, ctx, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, ctx, iter)) return false;
    return true;
}
