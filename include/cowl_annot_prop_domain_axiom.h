/**
 * Declares CowlAnnotPropDomainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
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
CowlAnnotPropDomainAxiom* cowl_annot_prop_domain_axiom(CowlAnnotProp *prop, CowlIRI *domain,
                                                       CowlVector *annot) {
    return (CowlAnnotPropDomainAxiom *)cowl_get_impl_2_annot(COWL_OT_A_ANNOT_PROP_DOMAIN,
                                                             prop, domain, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_INLINE
CowlAnnotPropDomainAxiom* cowl_annot_prop_domain_axiom_retain(CowlAnnotPropDomainAxiom *axiom) {
    return (CowlAnnotPropDomainAxiom *)cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_INLINE
void cowl_annot_prop_domain_axiom_release(CowlAnnotPropDomainAxiom *axiom) {
    cowl_release_impl(axiom);
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
CowlAnnotProp* cowl_annot_prop_domain_axiom_get_prop(CowlAnnotPropDomainAxiom *axiom) {
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
CowlIRI* cowl_annot_prop_domain_axiom_get_domain(CowlAnnotPropDomainAxiom *axiom) {
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
CowlVector* cowl_annot_prop_domain_axiom_get_annot(CowlAnnotPropDomainAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_INLINE
CowlString* cowl_annot_prop_domain_axiom_to_string(CowlAnnotPropDomainAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_INLINE
bool cowl_annot_prop_domain_axiom_equals(CowlAnnotPropDomainAxiom *lhs,
                                         CowlAnnotPropDomainAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_INLINE
ulib_uint cowl_annot_prop_domain_axiom_hash(CowlAnnotPropDomainAxiom *axiom) {
    return cowl_hash_impl(axiom);
}

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_INLINE
bool cowl_annot_prop_domain_axiom_iterate_primitives(CowlAnnotPropDomainAxiom *axiom,
                                                     CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_DOMAIN_AXIOM_H
