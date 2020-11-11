/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_prop_domain_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_data_prop_exp.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_alloc(CowlDataPropExp *prop,
                                                                  CowlClsExp *domain,
                                                                  CowlAnnotationVec *annot) {
    CowlDataPropDomainAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint hash = cowl_axiom_hash_2(COWL_HASH_INIT_DATA_PROP_DOMAIN_AXIOM, annot,
                                       cowl_data_prop_exp_hash(prop),
                                       cowl_cls_exp_hash(domain));

    cowl_axiom_init(CowlDataPropDomainAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_DATA_PROP_DOMAIN, hash, annot),
        .prop_exp = cowl_data_prop_exp_retain(prop),
        .domain = cowl_cls_exp_retain(domain)
    );

    return axiom;
}

static void cowl_data_prop_domain_axiom_free(CowlDataPropDomainAxiom *axiom) {
    if (!axiom) return;
    cowl_data_prop_exp_release(axiom->prop_exp);
    cowl_cls_exp_release(axiom->domain);
    cowl_axiom_free(axiom);
}

CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_get(CowlDataPropExp *prop, CowlClsExp *domain,
                                                         CowlAnnotationVec *annot) {
    if (!(prop && domain)) return NULL;
    return cowl_data_prop_domain_axiom_alloc(prop, domain, annot);
}

CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_retain(CowlDataPropDomainAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_data_prop_domain_axiom_release(CowlDataPropDomainAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_data_prop_domain_axiom_free(axiom);
    }
}

CowlDataPropExp* cowl_data_prop_domain_axiom_get_prop(CowlDataPropDomainAxiom *axiom) {
    return axiom->prop_exp;
}

CowlClsExp* cowl_data_prop_domain_axiom_get_domain(CowlDataPropDomainAxiom *axiom) {
    return axiom->domain;
}

CowlAnnotationVec* cowl_data_prop_domain_axiom_get_annot(CowlDataPropDomainAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_data_prop_domain_axiom_to_string(CowlDataPropDomainAxiom *axiom)
    COWL_TO_STRING_IMPL(data_prop_domain, axiom)

bool cowl_data_prop_domain_axiom_equals(CowlDataPropDomainAxiom *lhs,
                                        CowlDataPropDomainAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_data_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
                                  cowl_cls_exp_equals(lhs->domain, rhs->domain));
}

cowl_uint cowl_data_prop_domain_axiom_hash(CowlDataPropDomainAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_data_prop_domain_axiom_iterate_primitives(CowlDataPropDomainAxiom *axiom,
                                                    CowlIterator *iter, CowlPrimitiveFlags flags) {
    return (cowl_data_prop_exp_iterate_primitives(axiom->prop_exp, iter, flags) &&
            cowl_cls_exp_iterate_primitives(axiom->domain, iter, flags) &&
            cowl_axiom_annot_iterate_primitives(axiom, iter, flags));
}
