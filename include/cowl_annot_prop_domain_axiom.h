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
/// @endcond

/**
 * Represents an [AnnotationPropertyDomain] axiom in the OWL 2 specification.
 *
 * [AnnotationPropertyDomain]: https://www.w3.org/TR/owl2-syntax/#Annotation_Property_Domain
 *
 * @superstruct{CowlAxiom}
 * @struct CowlAnnotPropDomainAxiom
 */
cowl_struct_decl(CowlAnnotPropDomainAxiom);

/**
 * @defgroup CowlAnnotPropDomainAxiom CowlAnnotPropDomainAxiom API
 * @{
 */

/**
 * Returns an annotation property domain axiom.
 *
 * @param prop The annotation property.
 * @param domain Domain of the annotation property.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
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
 */
COWL_PURE
COWL_INLINE
CowlAnnotProp *cowl_annot_prop_domain_axiom_get_prop(CowlAnnotPropDomainAxiom *axiom) {
    return (CowlAnnotProp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the domain of the annotation property.
 *
 * @param axiom The axiom.
 * @return Domain of the annotation property.
 */
COWL_PURE
COWL_INLINE
CowlIRI *cowl_annot_prop_domain_axiom_get_domain(CowlAnnotPropDomainAxiom *axiom) {
    return (CowlIRI *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_DOMAIN_AXIOM_H
