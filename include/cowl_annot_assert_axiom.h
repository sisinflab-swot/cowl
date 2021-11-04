/**
 * Declares CowlAnnotAssertAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_ASSERT_AXIOM_H
#define COWL_ANNOT_ASSERT_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlAnnotValue);
cowl_struct_decl(CowlString);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlAnnotAssertAxiom);
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
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
CowlAnnotAssertAxiom* cowl_annot_assert_axiom_get(CowlAnnotValue *subject, CowlAnnotProp *prop,
                                                  CowlAnnotValue *value, CowlObjectVec *annot);

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
CowlAnnotValue* cowl_annot_assert_axiom_get_subject(CowlAnnotAssertAxiom *axiom);

/**
 * Gets the annotation value.
 *
 * @param axiom The axiom.
 * @return The annotation value.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
CowlAnnotValue* cowl_annot_assert_axiom_get_value(CowlAnnotAssertAxiom *axiom);

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
CowlObjectVec* cowl_annot_assert_axiom_get_annot(CowlAnnotAssertAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error..
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
ulib_uint cowl_annot_assert_axiom_hash(CowlAnnotAssertAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_PUBLIC
bool cowl_annot_assert_axiom_iterate_primitives(CowlAnnotAssertAxiom *axiom,
                                                CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_ANNOT_ASSERT_AXIOM_H
