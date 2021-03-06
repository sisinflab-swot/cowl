/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_PROP_DOMAIN_AXIOM_PRIVATE_H
#define COWL_ANNOT_PROP_DOMAIN_AXIOM_PRIVATE_H

#include "cowl_annot_prop_domain_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlAnnotPropDomainAxiom,
    CowlAnnotProp *prop;
    CowlIRI *domain;
);

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_DOMAIN_AXIOM_PRIVATE_H
