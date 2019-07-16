/**
 * Declares CowlAnnotAssertAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_ASSERT_AXIOM_H
#define COWL_ANNOT_ASSERT_AXIOM_H

#include "cowl_annot_value.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);
cowl_struct_decl(CowlAnnotAssertAxiom);
cowl_struct_decl(CowlString);
/// @endcond

/**
 * Represents an [AnnotationAssertion] axiom in the OWL 2 specification.
 *
 * [AnnotationAssertion]: https://www.w3.org/TR/owl2-syntax/#Annotation_Assertion
 *
 * @struct CowlAnnotAssertAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained annotation assertion axiom.
 *
 * @param subject The annotation subject.
 * @param prop The annotation property.
 * @param value The annotation value.
 * @param annot The annotations.
 * @return Retained axiom.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
CowlAnnotAssertAxiom* cowl_annot_assert_axiom_get(CowlAnnotValue subject, CowlAnnotProp *prop,
                                                  CowlAnnotValue value, CowlAnnotationVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
CowlAnnotAssertAxiom* cowl_annot_assert_axiom_retain(CowlAnnotAssertAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
void cowl_annot_assert_axiom_release(CowlAnnotAssertAxiom *axiom);

/**
 * Gets the annotation subject.
 *
 * @param axiom The axiom.
 * @return The annotation subject.
 *
 * @note The annotation subject can only be an anonymous individual or an IRI.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
CowlAnnotValue cowl_annot_assert_axiom_get_subject(CowlAnnotAssertAxiom *axiom);

/**
 * Gets the annotation value.
 *
 * @param axiom The axiom.
 * @return The annotation value.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
CowlAnnotValue cowl_annot_assert_axiom_get_value(CowlAnnotAssertAxiom *axiom);

/**
 * Gets the annotation property.
 *
 * @param axiom The axiom.
 * @return The annotation property.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
CowlAnnotProp* cowl_annot_assert_axiom_get_prop(CowlAnnotAssertAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
CowlAnnotationVec* cowl_annot_assert_axiom_get_annot(CowlAnnotAssertAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
CowlString* cowl_annot_assert_axiom_to_string(CowlAnnotAssertAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
bool cowl_annot_assert_axiom_equals(CowlAnnotAssertAxiom *lhs, CowlAnnotAssertAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
cowl_uint_t cowl_annot_assert_axiom_hash(CowlAnnotAssertAxiom *axiom);

/**
 * Iterates over the signature of the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
bool cowl_annot_assert_axiom_iterate_signature(CowlAnnotAssertAxiom *axiom,
                                               CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_ANNOT_ASSERT_AXIOM_H
