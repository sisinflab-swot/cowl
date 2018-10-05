/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_DOMAIN_AXIOM_PRIVATE_H
#define COWL_OBJ_PROP_DOMAIN_AXIOM_PRIVATE_H

#include "cowl_obj_prop_domain_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

typedef struct CowlObjPropDomainAxiom {
    CowlAxiom super;
    CowlObjPropExp const *prop_exp;
    CowlClsExp const *domain;
} CowlObjPropDomainAxiom;

COWL_END_DECLS

#endif // COWL_OBJ_PROP_DOMAIN_AXIOM_PRIVATE_H
