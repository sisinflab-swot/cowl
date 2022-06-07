/**
 * Declares CowlNAryData and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_DATA_H
#define COWL_NARY_DATA_H

#include "cowl_object_impl.h"
#include "cowl_nary_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlNAryData);
/// @endcond

/**
 * Represents [DataIntersectionOf] and [DataUnionOf] in the OWL 2 specification.
 *
 * [DataIntersectionOf]: https://www.w3.org/TR/owl2-syntax/#Intersection_of_Data_Ranges
 * [DataUnionOf]: https://www.w3.org/TR/owl2-syntax/#Union_of_Data_Ranges
 *
 * @struct CowlNAryData
 * @extends CowlDataRange
 */

/**
 * Returns a retained N-ary data range.
 *
 * @param type N-ary data range type.
 * @param operands The operands.
 * @return Retained N-ary data range, or NULL on error.
 *
 * @public @memberof CowlNAryData
 */
COWL_INLINE
CowlNAryData* cowl_nary_data_get(CowlNAryType type, CowlVector *operands) {
    if (!cowl_enum_value_is_valid(NT, type)) return NULL;
    return cowl_get_impl_1(COWL_OT_DR_DATA_INTERSECT + type, operands, NULL);
}

/**
 * Retains the specified N-ary data range.
 *
 * @param range The data range.
 * @return Retained N-ary data range.
 *
 * @public @memberof CowlNAryData
 */
COWL_INLINE
CowlNAryData* cowl_nary_data_retain(CowlNAryData *range) { return cowl_retain(range); }

/**
 * Releases the specified N-ary data range.
 *
 * @param range The data range.
 *
 * @public @memberof CowlNAryData
 */
COWL_INLINE
void cowl_nary_data_release(CowlNAryData *range) { cowl_release_impl(range); }

/**
 * Gets the type of the specified N-ary data range.
 * @param range The data range.
 * @return The type.
 *
 * @public @memberof CowlNAryData
 */
COWL_INLINE
CowlNAryType cowl_nary_data_get_type(CowlNAryData *range) {
    return (CowlNAryType)(cowl_get_type(range) - COWL_OT_DR_DATA_INTERSECT);
}

/**
 * Gets the operands of the specified N-ary data range.
 *
 * @param range The data range.
 * @return The operands.
 *
 * @public @memberof CowlNAryData
 */
COWL_INLINE
CowlVector* cowl_nary_data_get_operands(CowlNAryData *range) { return cowl_get_field(range, 0); }

/**
 * Returns the string representation of the specified N-ary data range.
 *
 * @param range The data range.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlNAryData
 */
COWL_INLINE
CowlString* cowl_nary_data_to_string(CowlNAryData *range) {
    return cowl_to_string_impl(range);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNAryData
 */
COWL_INLINE
bool cowl_nary_data_equals(CowlNAryData *lhs, CowlNAryData *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param range The data range.
 * @return The hash value.
 *
 * @public @memberof CowlNAryData
 */
COWL_INLINE
ulib_uint cowl_nary_data_hash(CowlNAryData *range) {
    return cowl_hash_impl(range);
}

/**
 * Iterates over the primitives referenced by the specified N-ary data range.
 *
 * @param range The data range.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlNAryData
 */
COWL_INLINE
bool cowl_nary_data_iterate_primitives(CowlNAryData *range, CowlPrimitiveFlags flags,
                                       CowlIterator *iter) {
    return cowl_iterate_primitives_impl(range, flags, iter);
}

COWL_END_DECLS

#endif // COWL_NARY_DATA_H
