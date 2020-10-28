/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annot_prop_domain_axiom_private.h"
#include "cowl_annot_prop.h"
#include "cowl_iri.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlAnnotPropDomainAxiom* cowl_annot_prop_domain_axiom_alloc(CowlAnnotProp *prop,
                                                                    CowlIRI *domain,
                                                                    CowlAnnotationVec *annot) {
    CowlAnnotPropDomainAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_ANNOT_PROP_DOMAIN_AXIOM, annot,
                                         cowl_annot_prop_hash(prop),
                                         cowl_iri_hash(domain));

    cowl_axiom_init(CowlAnnotPropDomainAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_ANNOT_PROP_DOMAIN, hash, annot),
        .prop = cowl_annot_prop_retain(prop),
        .domain = cowl_iri_retain(domain)
    );

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
    if (!(prop && domain)) return NULL;
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

CowlString* cowl_annot_prop_domain_axiom_to_string(CowlAnnotPropDomainAxiom *axiom)
    COWL_TO_STRING_IMPL(annot_prop_domain_axiom, axiom)

bool cowl_annot_prop_domain_axiom_equals(CowlAnnotPropDomainAxiom *lhs,
                                         CowlAnnotPropDomainAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_iri_equals(lhs->domain, rhs->domain) &&
                                  cowl_annot_prop_equals(lhs->prop, rhs->prop));
}

cowl_uint_t cowl_annot_prop_domain_axiom_hash(CowlAnnotPropDomainAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_annot_prop_domain_axiom_iterate(CowlAnnotPropDomainAxiom *axiom, CowlIterator *iter) {
    if (cowl_annot_prop_iterate(axiom->prop, iter) &&
        cowl_axiom_annot_iterate(axiom, iter)) {
        return true;
    }
    return false;
}
