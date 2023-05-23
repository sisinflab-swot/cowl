/**
 * Declares CowlAnnotPropDomainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_PROP_DOMAIN_AXIOM_H
#define COWL_ANNOT_PROP_DOMAIN_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlAnnotPropDomainAxiom);
/// @endcond

/**
 * Represents an [AnnotationPropertyDomain] axiom in the OWL 2 specification.
 *
 * [AnnotationPropertyDomain]: https://www.w3.org/TR/owl2-syntax/#Annotation_Property_Domain
 *
 * @struct CowlAnnotPropDomainAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained annotation property domain axiom.
 *
 * @param prop The annotation property.
 * @param domain Domain of the annotation property.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_INLINE
CowlAnnotPropDomainAxiom *
cowl_annot_prop_domain_axiom(CowlAnnotProp *prop, CowlIRI *domain, CowlVector *annot) {
    return (CowlAnnotPropDomainAxiom *)cowl_get_impl_2_annot(COWL_OT_A_ANNOT_PROP_DOMAIN, prop,
                                                             domain, annot);
}

/**
 * Gets the annotation property.
 *
 * @param axiom The axiom.
 * @return The annotation property.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_INLINE
CowlAnnotProp *cowl_annot_prop_domain_axiom_get_prop(CowlAnnotPropDomainAxiom *axiom) {
    return (CowlAnnotProp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the domain of the annotation property.
 *
 * @param axiom The axiom.
 * @return Domain of the annotation property.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_INLINE
CowlIRI *cowl_annot_prop_domain_axiom_get_domain(CowlAnnotPropDomainAxiom *axiom) {
    return (CowlIRI *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_INLINE
CowlVector *cowl_annot_prop_domain_axiom_get_annot(CowlAnnotPropDomainAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_DOMAIN_AXIOM_H
