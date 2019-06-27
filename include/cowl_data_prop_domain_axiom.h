/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_DOMAIN_AXIOM_H
#define COWL_DATA_PROP_DOMAIN_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataPropExp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlDataPropDomainAxiom);

CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_get(CowlDataPropExp *prop, CowlClsExp *domain,
                                                         CowlAnnotationVec *annot);
CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_retain(CowlDataPropDomainAxiom *axiom);
void cowl_data_prop_domain_axiom_release(CowlDataPropDomainAxiom *axiom);

CowlDataPropExp* cowl_data_prop_domain_axiom_get_prop(CowlDataPropDomainAxiom *axiom);
CowlClsExp* cowl_data_prop_domain_axiom_get_domain(CowlDataPropDomainAxiom *axiom);
CowlAnnotationVec* cowl_data_prop_domain_axiom_get_annot(CowlDataPropDomainAxiom *axiom);

bool cowl_data_prop_domain_axiom_equals(CowlDataPropDomainAxiom *lhs, CowlDataPropDomainAxiom *rhs);
cowl_uint_t cowl_data_prop_domain_axiom_hash(CowlDataPropDomainAxiom *axiom);

bool cowl_data_prop_domain_axiom_iterate_signature(CowlDataPropDomainAxiom *axiom,
                                                   CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_DATA_PROP_DOMAIN_AXIOM_H
