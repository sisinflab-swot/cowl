/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_DOMAIN_AXIOM_PRIVATE_H
#define COWL_DATA_PROP_DOMAIN_AXIOM_PRIVATE_H

#include "cowl_data_prop_domain_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDataPropDomainAxiom) {
    CowlAxiom super;
    CowlDataPropExp *prop_exp;
    CowlClsExp *domain;
};

COWL_END_DECLS

#endif // COWL_DATA_PROP_DOMAIN_AXIOM_PRIVATE_H
