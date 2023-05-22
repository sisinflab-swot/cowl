/**
 * Declares CowlClsAssertAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLS_ASSERT_AXIOM_H
#define COWL_CLS_ASSERT_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlClsAssertAxiom);
/// @endcond

/**
 * Represents a [ClassAssertion] axiom in the OWL 2 specification.
 *
 * [ClassAssertion]: https://www.w3.org/TR/owl2-syntax/#Class_Assertions
 *
 * @struct CowlClsAssertAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained class assertion axiom.
 *
 * @param exp The asserted class expression.
 * @param ind The assertion individual.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_INLINE
CowlClsAssertAxiom *
cowl_cls_assert_axiom(CowlAnyClsExp *exp, CowlAnyIndividual *ind, CowlVector *annot) {
    return (CowlClsAssertAxiom *)cowl_get_impl_2_annot(COWL_OT_A_CLASS_ASSERT, exp, ind, annot);
}

/**
 * Gets the class expression that is asserted to be a type for an individual by this axiom.
 *
 * @param axiom The axiom.
 * @return The class expression.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_INLINE
CowlClsExp *cowl_cls_assert_axiom_get_cls_exp(CowlClsAssertAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the individual that is asserted to be an instance of a class expression by this axiom.
 *
 * @param axiom The axiom.
 * @return The individual.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_INLINE
CowlIndividual *cowl_cls_assert_axiom_get_ind(CowlClsAssertAxiom *axiom) {
    return (CowlIndividual *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_INLINE
CowlVector *cowl_cls_assert_axiom_get_annot(CowlClsAssertAxiom *axiom) {
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
 * @public @memberof CowlClsAssertAxiom
 */
COWL_INLINE
CowlString *cowl_cls_assert_axiom_to_string(CowlClsAssertAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_INLINE
bool cowl_cls_assert_axiom_equals(CowlClsAssertAxiom *lhs, CowlClsAssertAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_INLINE
ulib_uint cowl_cls_assert_axiom_hash(CowlClsAssertAxiom *axiom) {
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
 * @public @memberof CowlClsAssertAxiom
 */
COWL_INLINE
bool cowl_cls_assert_axiom_iterate_primitives(CowlClsAssertAxiom *axiom, CowlPrimitiveFlags flags,
                                              CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_CLS_ASSERT_AXIOM_H
