/**
 * Declares CowlDataPropAssertAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_ASSERT_AXIOM_H
#define COWL_DATA_PROP_ASSERT_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlLiteral);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlDataPropAssertAxiom);
/// @endcond

/**
 * Represents a [DataPropertyAssertion] or [NegativeDataPropertyAssertion] axiom
 * in the OWL 2 specification.
 *
 * [DataPropertyAssertion]:
 * https://www.w3.org/TR/owl2-syntax/#Positive_Data_Property_Assertions
 *
 * [NegativeDataPropertyAssertion]:
 * https://www.w3.org/TR/owl2-syntax/#Negative_Data_Property_Assertions
 *
 * @struct CowlDataPropAssertAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained data property assertion axiom.
 *
 * @param subj The assertion subject.
 * @param prop The data property.
 * @param obj The assertion object.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_get(CowlIndividual *subj,
                                                         CowlDataPropExp *prop,
                                                         CowlLiteral *obj,
                                                         CowlObjectVec *annot);

/**
 * Returns a retained negative data property assertion axiom.
 *
 * @param subj The assertion subject.
 * @param prop The data property.
 * @param obj The assertion object.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
CowlDataPropAssertAxiom* cowl_neg_data_prop_assert_axiom_get(CowlIndividual *subj,
                                                             CowlDataPropExp *prop,
                                                             CowlLiteral *obj,
                                                             CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_retain(CowlDataPropAssertAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
void cowl_data_prop_assert_axiom_release(CowlDataPropAssertAxiom *axiom);

/**
 * Returns true if the specified data property assertion axiom is negative.
 *
 * @param axiom The axiom.
 * @return True if the assertion is negative, false otherwise.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
bool cowl_data_prop_assert_axiom_is_negative(CowlDataPropAssertAxiom *axiom);

/**
 * Gets the assertion subject.
 *
 * @param axiom The axiom.
 * @return The assertion subject.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
CowlIndividual* cowl_data_prop_assert_axiom_get_subject(CowlDataPropAssertAxiom *axiom);

/**
 * Gets the assertion object.
 *
 * @param axiom The axiom.
 * @return The assertion object.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
CowlLiteral* cowl_data_prop_assert_axiom_get_object(CowlDataPropAssertAxiom *axiom);

/**
 * Gets the data property.
 *
 * @param axiom The axiom.
 * @return The data property.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
CowlDataPropExp* cowl_data_prop_assert_axiom_get_prop(CowlDataPropAssertAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_data_prop_assert_axiom_get_annot(CowlDataPropAssertAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
CowlString* cowl_data_prop_assert_axiom_to_string(CowlDataPropAssertAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
bool cowl_data_prop_assert_axiom_equals(CowlDataPropAssertAxiom *lhs, CowlDataPropAssertAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
ulib_uint cowl_data_prop_assert_axiom_hash(CowlDataPropAssertAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_PUBLIC
bool cowl_data_prop_assert_axiom_iterate_primitives(CowlDataPropAssertAxiom *axiom,
                                                    CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_DATA_PROP_ASSERT_AXIOM_H
