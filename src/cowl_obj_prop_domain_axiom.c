/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_domain_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_template.h"

static CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_alloc(CowlObjPropExp *prop,
                                                                CowlClsExp *domain,
                                                                CowlObjectVec *annot) {
    CowlObjPropDomainAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    ulib_uint hash = cowl_axiom_hash_2(COWL_HASH_INIT_OBJ_PROP_DOMAIN_AXIOM, annot,
                                       cowl_obj_prop_exp_hash(prop),
                                       cowl_cls_exp_hash(domain));

    cowl_axiom_init(CowlObjPropDomainAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_OBJ_PROP_DOMAIN, hash, annot),
        .prop_exp = cowl_obj_prop_exp_retain(prop),
        .domain = cowl_cls_exp_retain(domain)
    );

    return axiom;
}

static void cowl_obj_prop_domain_axiom_free(CowlObjPropDomainAxiom *axiom) {
    cowl_obj_prop_exp_release(axiom->prop_exp);
    cowl_cls_exp_release(axiom->domain);
    cowl_axiom_free(axiom);
}

CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_get(CowlObjPropExp *prop, CowlClsExp *domain,
                                                       CowlObjectVec *annot) {
    if (!(prop && domain)) return NULL;
    return cowl_obj_prop_domain_axiom_alloc(prop, domain, annot);
}

CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_retain(CowlObjPropDomainAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_obj_prop_domain_axiom_release(CowlObjPropDomainAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_obj_prop_domain_axiom_free(axiom);
    }
}

CowlObjPropExp* cowl_obj_prop_domain_axiom_get_prop(CowlObjPropDomainAxiom *axiom) {
    return axiom->prop_exp;
}

CowlClsExp* cowl_obj_prop_domain_axiom_get_domain(CowlObjPropDomainAxiom *axiom) {
    return axiom->domain;
}

CowlObjectVec* cowl_obj_prop_domain_axiom_get_annot(CowlObjPropDomainAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_obj_prop_domain_axiom_to_string(CowlObjPropDomainAxiom *axiom)
    COWL_TO_STRING_IMPL(obj_prop_domain, axiom)

bool cowl_obj_prop_domain_axiom_equals(CowlObjPropDomainAxiom *lhs, CowlObjPropDomainAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
                                  cowl_cls_exp_equals(lhs->domain, rhs->domain));
}

ulib_uint cowl_obj_prop_domain_axiom_hash(CowlObjPropDomainAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_obj_prop_domain_axiom_iterate_primitives(CowlObjPropDomainAxiom *axiom,
                                                   CowlPrimitiveFlags flags, CowlIterator *iter) {
    return (cowl_obj_prop_exp_iterate_primitives(axiom->prop_exp, flags, iter) &&
            cowl_cls_exp_iterate_primitives(axiom->domain, flags, iter) &&
            cowl_axiom_annot_iterate_primitives(axiom, flags, iter));
}
