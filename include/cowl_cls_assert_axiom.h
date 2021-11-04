/**
 * Declares CowlClsAssertAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLS_ASSERT_AXIOM_H
#define COWL_CLS_ASSERT_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlIndividual);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
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
 * @param ind The assertion individual.
 * @param exp The asserted class expression.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_PUBLIC
CowlClsAssertAxiom* cowl_cls_assert_axiom_get(CowlIndividual *ind, CowlClsExp *exp,
                                              CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_PUBLIC
CowlClsAssertAxiom* cowl_cls_assert_axiom_retain(CowlClsAssertAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_PUBLIC
void cowl_cls_assert_axiom_release(CowlClsAssertAxiom *axiom);

/**
 * Gets the individual that is asserted to be an instance of a class expression by this axiom.
 *
 * @param axiom The axiom.
 * @return The individual.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_PUBLIC
CowlIndividual* cowl_cls_assert_axiom_get_ind(CowlClsAssertAxiom *axiom);

/**
 * Gets the class expression that is asserted to be a type for an individual by this axiom.
 *
 * @param axiom The axiom.
 * @return The class expression.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_PUBLIC
CowlClsExp* cowl_cls_assert_axiom_get_cls_exp(CowlClsAssertAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_cls_assert_axiom_get_annot(CowlClsAssertAxiom *axiom);

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
COWL_PUBLIC
CowlString* cowl_cls_assert_axiom_to_string(CowlClsAssertAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_PUBLIC
bool cowl_cls_assert_axiom_equals(CowlClsAssertAxiom *lhs, CowlClsAssertAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_PUBLIC
ulib_uint cowl_cls_assert_axiom_hash(CowlClsAssertAxiom *axiom);

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
COWL_PUBLIC
bool cowl_cls_assert_axiom_iterate_primitives(CowlClsAssertAxiom *axiom, CowlPrimitiveFlags flags,
                                              CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_CLS_ASSERT_AXIOM_H
