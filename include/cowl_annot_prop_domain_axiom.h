/**
 * Declares CowlAnnotPropDomainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
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
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);
cowl_struct_decl(CowlAnnotPropDomainAxiom);
cowl_struct_decl(CowlString);
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
 * @param annot The annotations.
 * @return Retained axiom.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_PUBLIC
CowlAnnotPropDomainAxiom* cowl_annot_prop_domain_axiom_get(CowlAnnotProp *prop, CowlIRI *domain,
                                                           CowlAnnotationVec *annot);

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
CowlAnnotationVec* cowl_annot_prop_domain_axiom_get_annot(CowlAnnotPropDomainAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation.
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
cowl_uint_t cowl_annot_prop_domain_axiom_hash(CowlAnnotPropDomainAxiom *axiom);

/**
 * Iterates over the signature of the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter Entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_PUBLIC
bool cowl_annot_prop_domain_axiom_iterate_signature(CowlAnnotPropDomainAxiom *axiom,
                                                    CowlEntityIterator *iter);

/**
 * Iterates over the anonymous individuals referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter The anonymous individual iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAnnotPropDomainAxiom
 */
COWL_PUBLIC
bool cowl_annot_prop_domain_axiom_iterate_anon_inds(CowlAnnotPropDomainAxiom *axiom,
                                                    CowlAnonIndIterator *iter);

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_DOMAIN_AXIOM_H
