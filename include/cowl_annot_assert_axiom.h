/**
 * Declares CowlAnnotAssertAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_ASSERT_AXIOM_H
#define COWL_ANNOT_ASSERT_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlAnnotValue);
cowl_struct_decl(CowlVector);
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
 * @param prop The annotation property.
 * @param subject The annotation subject.
 * @param value The annotation value.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_INLINE
CowlAnnotAssertAxiom *cowl_annot_assert_axiom(CowlAnnotProp *prop, CowlAnyAnnotValue *subject,
                                              CowlAnyAnnotValue *value, CowlVector *annot) {
    return (CowlAnnotAssertAxiom *)cowl_get_impl_3_annot(COWL_OT_A_ANNOT_ASSERT, prop, subject,
                                                         value, annot);
}

/**
 * Gets the annotation property.
 *
 * @param axiom The axiom.
 * @return The annotation property.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_INLINE
CowlAnnotProp *cowl_annot_assert_axiom_get_prop(CowlAnnotAssertAxiom *axiom) {
    return (CowlAnnotProp *)cowl_get_field(axiom, 0);
}

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
COWL_INLINE
CowlAnnotValue *cowl_annot_assert_axiom_get_subject(CowlAnnotAssertAxiom *axiom) {
    return (CowlAnnotValue *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotation value.
 *
 * @param axiom The axiom.
 * @return The annotation value.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_INLINE
CowlAnnotValue *cowl_annot_assert_axiom_get_value(CowlAnnotAssertAxiom *axiom) {
    return (CowlAnnotValue *)cowl_get_field(axiom, 2);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_INLINE
CowlVector *cowl_annot_assert_axiom_get_annot(CowlAnnotAssertAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

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
COWL_INLINE
CowlString *cowl_annot_assert_axiom_to_string(CowlAnnotAssertAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_INLINE
bool cowl_annot_assert_axiom_equals(CowlAnnotAssertAxiom *lhs, CowlAnnotAssertAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotAssertAxiom
 */
COWL_INLINE
ulib_uint cowl_annot_assert_axiom_hash(CowlAnnotAssertAxiom *axiom) {
    return cowl_hash_impl(axiom);
}

COWL_END_DECLS

#endif // COWL_ANNOT_ASSERT_AXIOM_H
