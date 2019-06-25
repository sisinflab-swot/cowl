/// @author Ivano Bilenchi

#ifndef COWL_ANNOT_PROP_DOMAIN_AXIOM_H
#define COWL_ANNOT_PROP_DOMAIN_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlIRI);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlAnnotPropDomainAxiom);

CowlAnnotPropDomainAxiom* cowl_annot_prop_domain_axiom_get(CowlAnnotProp *prop, CowlIRI *domain,
                                                           CowlAnnotationVec *annot);
CowlAnnotPropDomainAxiom* cowl_annot_prop_domain_axiom_retain(CowlAnnotPropDomainAxiom *axiom);
void cowl_annot_prop_domain_axiom_release(CowlAnnotPropDomainAxiom *axiom);

CowlAnnotProp* cowl_annot_prop_domain_axiom_get_prop(CowlAnnotPropDomainAxiom *axiom);
CowlIRI* cowl_annot_prop_domain_axiom_get_domain(CowlAnnotPropDomainAxiom *axiom);
CowlAnnotationVec* cowl_annot_prop_domain_axiom_get_annot(CowlAnnotPropDomainAxiom *axiom);

bool cowl_annot_prop_domain_axiom_equals(CowlAnnotPropDomainAxiom *lhs,
                                         CowlAnnotPropDomainAxiom *rhs);
cowl_uint_t cowl_annot_prop_domain_axiom_hash(CowlAnnotPropDomainAxiom *axiom);

bool cowl_annot_prop_domain_axiom_iterate_signature(CowlAnnotPropDomainAxiom *axiom,
                                                    void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_DOMAIN_AXIOM_H
