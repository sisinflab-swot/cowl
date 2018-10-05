/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_DOMAIN_AXIOM_H
#define COWL_OBJ_PROP_DOMAIN_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;
typedef struct CowlObjPropExp CowlObjPropExp;

typedef struct CowlObjPropDomainAxiom CowlObjPropDomainAxiom;

CowlObjPropExp const* cowl_obj_prop_domain_axiom_get_prop(CowlObjPropDomainAxiom const *axiom);
CowlClsExp const* cowl_obj_prop_domain_axiom_get_domain(CowlObjPropDomainAxiom const *axiom);

bool cowl_obj_prop_domain_axiom_equals(CowlObjPropDomainAxiom const *lhs,
                                       CowlObjPropDomainAxiom const *rhs);
uint32_t cowl_obj_prop_domain_axiom_hash(CowlObjPropDomainAxiom const *axiom);

bool cowl_obj_prop_domain_axiom_iterate_signature(CowlObjPropDomainAxiom const *axiom,
                                                  void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_DOMAIN_AXIOM_H
