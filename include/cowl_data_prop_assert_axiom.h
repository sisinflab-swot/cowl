/**
 * Declares CowlDataPropAssertAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_ASSERT_AXIOM_H
#define COWL_DATA_PROP_ASSERT_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlVector);
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
COWL_INLINE
CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_get(CowlIndividual *subj,
                                                         CowlDataPropExp *prop,
                                                         CowlLiteral *obj,
                                                         CowlVector *annot) {
    return (CowlDataPropAssertAxiom *)cowl_get_impl_3_opt(COWL_OT_A_DATA_PROP_ASSERT,
                                                          subj, prop, obj, annot);
}

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
COWL_INLINE
CowlDataPropAssertAxiom* cowl_neg_data_prop_assert_axiom_get(CowlIndividual *subj,
                                                             CowlDataPropExp *prop,
                                                             CowlLiteral *obj,
                                                             CowlVector *annot) {
    return (CowlDataPropAssertAxiom *)cowl_get_impl_3_opt(COWL_OT_A_NEG_DATA_PROP_ASSERT,
                                                          subj, prop, obj, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_INLINE
CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_retain(CowlDataPropAssertAxiom *axiom) {
    return (CowlDataPropAssertAxiom *)cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_INLINE
void cowl_data_prop_assert_axiom_release(CowlDataPropAssertAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Returns true if the specified data property assertion axiom is negative.
 *
 * @param axiom The axiom.
 * @return True if the assertion is negative, false otherwise.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_INLINE
bool cowl_data_prop_assert_axiom_is_negative(CowlDataPropAssertAxiom *axiom) {
    return cowl_get_type(axiom) == COWL_OT_A_NEG_DATA_PROP_ASSERT;
}

/**
 * Gets the assertion subject.
 *
 * @param axiom The axiom.
 * @return The assertion subject.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_INLINE
CowlIndividual* cowl_data_prop_assert_axiom_get_subject(CowlDataPropAssertAxiom *axiom) {
    return (CowlIndividual *)cowl_get_field(axiom, 0);
}

/**
 * Gets the data property.
 *
 * @param axiom The axiom.
 * @return The data property.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_INLINE
CowlDataPropExp* cowl_data_prop_assert_axiom_get_prop(CowlDataPropAssertAxiom *axiom) {
    return (CowlDataPropExp *)cowl_get_field(axiom, 1);
}

/**
 * Gets the assertion object.
 *
 * @param axiom The axiom.
 * @return The assertion object.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_INLINE
CowlLiteral* cowl_data_prop_assert_axiom_get_object(CowlDataPropAssertAxiom *axiom) {
    return (CowlLiteral *)cowl_get_field(axiom, 2);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_INLINE
CowlVector* cowl_data_prop_assert_axiom_get_annot(CowlDataPropAssertAxiom *axiom) {
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
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_INLINE
CowlString* cowl_data_prop_assert_axiom_to_string(CowlDataPropAssertAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_INLINE
bool cowl_data_prop_assert_axiom_equals(CowlDataPropAssertAxiom *lhs, CowlDataPropAssertAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_INLINE
ulib_uint cowl_data_prop_assert_axiom_hash(CowlDataPropAssertAxiom *axiom) {
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
 * @public @memberof CowlDataPropAssertAxiom
 */
COWL_INLINE
bool cowl_data_prop_assert_axiom_iterate_primitives(CowlDataPropAssertAxiom *axiom,
                                                    CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DATA_PROP_ASSERT_AXIOM_H
