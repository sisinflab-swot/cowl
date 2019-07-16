/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_domain_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_str_buf.h"

static CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_alloc(CowlObjPropExp *prop,
                                                                CowlClsExp *domain,
                                                                CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_OBJ_PROP_DOMAIN_AXIOM, annot,
                                         cowl_obj_prop_exp_hash(prop),
                                         cowl_cls_exp_hash(domain));

    CowlObjPropDomainAxiom init = {
        .super = COWL_AXIOM_INIT(COWL_AT_OBJ_PROP_DOMAIN, hash, annot),
        .prop_exp = cowl_obj_prop_exp_retain(prop),
        .domain = cowl_cls_exp_retain(domain)
    };

    cowl_struct(CowlObjPropDomainAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_obj_prop_domain_axiom_free(CowlObjPropDomainAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_release(axiom->prop_exp);
    cowl_cls_exp_release(axiom->domain);
    cowl_axiom_free(axiom);
}

CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_get(CowlObjPropExp *prop, CowlClsExp *domain,
                                                       CowlAnnotationVec *annot) {
    return cowl_obj_prop_domain_axiom_alloc(prop, domain, annot);
}

CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_retain(CowlObjPropDomainAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_obj_prop_domain_axiom_release(CowlObjPropDomainAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_obj_prop_domain_axiom_free(axiom);
    }
}

CowlObjPropExp* cowl_obj_prop_domain_axiom_get_prop(CowlObjPropDomainAxiom *axiom) {
    return axiom->prop_exp;
}

CowlClsExp* cowl_obj_prop_domain_axiom_get_domain(CowlObjPropDomainAxiom *axiom) {
    return axiom->domain;
}

CowlAnnotationVec* cowl_obj_prop_domain_axiom_get_annot(CowlObjPropDomainAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_obj_prop_domain_axiom_to_string(CowlObjPropDomainAxiom *axiom) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_obj_prop_domain(buf, axiom);
    return cowl_str_buf_to_string(buf);
}

bool cowl_obj_prop_domain_axiom_equals(CowlObjPropDomainAxiom *lhs, CowlObjPropDomainAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
                                  cowl_cls_exp_equals(lhs->domain, rhs->domain));
}

cowl_uint_t cowl_obj_prop_domain_axiom_hash(CowlObjPropDomainAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_obj_prop_domain_axiom_iterate_signature(CowlObjPropDomainAxiom *axiom,
                                                  CowlEntityIterator *iter) {
    if (!cowl_obj_prop_exp_iterate_signature(axiom->prop_exp, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(axiom->domain, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}
