/**
 * Declares CowlAnnotPropDomainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_PROP_DOMAIN_AXIOM_H
#define COWL_ANNOT_PROP_DOMAIN_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
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
COWL_PUBLIC
CowlAnnotPropDomainAxiom* cowl_annot_prop_domain_axiom_get(CowlAnnotProp *prop, CowlIRI *domain,
                                                           CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_PUBLIC
CowlAnnotPropDomainAxiom* cowl_annot_prop_domain_axiom_retain(CowlAnnotPropDomainAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_PUBLIC
void cowl_annot_prop_domain_axiom_release(CowlAnnotPropDomainAxiom *axiom);

/**
 * Gets the annotation property.
 *
 * @param axiom The axiom.
 * @return The annotation property.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_PUBLIC
CowlAnnotProp* cowl_annot_prop_domain_axiom_get_prop(CowlAnnotPropDomainAxiom *axiom);

/**
 * Gets the domain of the annotation property.
 *
 * @param axiom The axiom.
 * @return Domain of the annotation property.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_PUBLIC
CowlIRI* cowl_annot_prop_domain_axiom_get_domain(CowlAnnotPropDomainAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_annot_prop_domain_axiom_get_annot(CowlAnnotPropDomainAxiom *axiom);

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
COWL_PUBLIC
CowlString* cowl_annot_prop_domain_axiom_to_string(CowlAnnotPropDomainAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_PUBLIC
bool cowl_annot_prop_domain_axiom_equals(CowlAnnotPropDomainAxiom *lhs,
                                         CowlAnnotPropDomainAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_PUBLIC
ulib_uint cowl_annot_prop_domain_axiom_hash(CowlAnnotPropDomainAxiom *axiom);

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
COWL_PUBLIC
bool cowl_annot_prop_domain_axiom_iterate_primitives(CowlAnnotPropDomainAxiom *axiom,
                                                     CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_DOMAIN_AXIOM_H
