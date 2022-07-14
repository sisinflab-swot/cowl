/**
 * Declares CowlDataPropRangeAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_RANGE_AXIOM_H
#define COWL_DATA_PROP_RANGE_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlDataPropRangeAxiom);
/// @endcond

/**
 * Represents a [DataPropertyRange] axiom in the OWL 2 specification.
 *
 * [DataPropertyRange]: https://www.w3.org/TR/owl2-syntax/#Data_Property_Range
 *
 * @struct CowlDataPropRangeAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained data property range axiom.
 *
 * @param prop The data property.
 * @param range Range of the data property.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlDataPropRangeAxiom
 */
COWL_INLINE
CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_get(CowlDataPropExp *prop, CowlDataRange *range,
                                                       CowlVector *annot) {
    return (CowlDataPropRangeAxiom *)cowl_get_impl_2_opt(COWL_OT_A_DATA_PROP_RANGE,
                                                         prop, range, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlDataPropRangeAxiom
 */
COWL_INLINE
CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_retain(CowlDataPropRangeAxiom *axiom) {
    return (CowlDataPropRangeAxiom *)cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlDataPropRangeAxiom
 */
COWL_INLINE
void cowl_data_prop_range_axiom_release(CowlDataPropRangeAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Gets the data property.
 *
 * @param axiom The axiom.
 * @return The data property.
 *
 * @public @memberof CowlDataPropRangeAxiom
 */
COWL_INLINE
CowlDataPropExp* cowl_data_prop_range_axiom_get_prop(CowlDataPropRangeAxiom *axiom) {
    return (CowlDataPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the range of the data property.
 *
 * @param axiom The axiom.
 * @return Range of the data property.
 *
 * @public @memberof CowlDataPropRangeAxiom
 */
COWL_INLINE
CowlDataRange* cowl_data_prop_range_axiom_get_range(CowlDataPropRangeAxiom *axiom) {
    return (CowlDataRange *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlDataPropRangeAxiom
 */
COWL_INLINE
CowlVector* cowl_data_prop_range_axiom_get_annot(CowlDataPropRangeAxiom *axiom) {
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
 * @public @memberof CowlDataPropRangeAxiom
 */
COWL_INLINE
CowlString* cowl_data_prop_range_axiom_to_string(CowlDataPropRangeAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataPropRangeAxiom
 */
COWL_INLINE
bool cowl_data_prop_range_axiom_equals(CowlDataPropRangeAxiom *lhs, CowlDataPropRangeAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlDataPropRangeAxiom
 */
COWL_INLINE
ulib_uint cowl_data_prop_range_axiom_hash(CowlDataPropRangeAxiom *axiom) {
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
 * @public @memberof CowlDataPropRangeAxiom
 */
COWL_INLINE
bool cowl_data_prop_range_axiom_iterate_primitives(CowlDataPropRangeAxiom *axiom,
                                                   CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DATA_PROP_RANGE_AXIOM_H
