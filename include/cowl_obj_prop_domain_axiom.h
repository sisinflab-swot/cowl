/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_DOMAIN_AXIOM_H
#define COWL_OBJ_PROP_DOMAIN_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlObjPropExp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlObjPropDomainAxiom);

CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_get(CowlObjPropExp *prop, CowlClsExp *domain,
                                                       CowlAnnotationVec *annot);
CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_retain(CowlObjPropDomainAxiom *axiom);
void cowl_obj_prop_domain_axiom_release(CowlObjPropDomainAxiom *axiom);

CowlObjPropExp* cowl_obj_prop_domain_axiom_get_prop(CowlObjPropDomainAxiom *axiom);
CowlClsExp* cowl_obj_prop_domain_axiom_get_domain(CowlObjPropDomainAxiom *axiom);
CowlAnnotationVec* cowl_obj_prop_domain_axiom_get_annot(CowlObjPropDomainAxiom *axiom);

bool cowl_obj_prop_domain_axiom_equals(CowlObjPropDomainAxiom *lhs, CowlObjPropDomainAxiom *rhs);
cowl_uint_t cowl_obj_prop_domain_axiom_hash(CowlObjPropDomainAxiom *axiom);

bool cowl_obj_prop_domain_axiom_iterate_signature(CowlObjPropDomainAxiom *axiom,
                                                  void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_DOMAIN_AXIOM_H
