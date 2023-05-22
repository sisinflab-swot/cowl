/**
 * Declares CowlDataCard and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_CARD_H
#define COWL_DATA_CARD_H

#include "cowl_card_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlDataCard);
/// @endcond

/**
 * Represents [DataMinCardinality], [DataMaxCardinality] and [DataExactCardinality]
 * in the OWL 2 specification.
 *
 * [DataMinCardinality]: https://www.w3.org/TR/owl2-syntax/#Minimum_Cardinality_2
 * [DataMaxCardinality]: https://www.w3.org/TR/owl2-syntax/#Maximum_Cardinality_2
 * [DataExactCardinality]: https://www.w3.org/TR/owl2-syntax/#Exact_Cardinality_2
 *
 * @struct CowlDataCard
 * @extends CowlClsExp
 */

/**
 * Returns a retained data property cardinality restriction.
 *
 * @param type The type.
 * @param prop The data property.
 * @param range [optional] Range of the restriction.
 * @param cardinality Cardinality of the restriction.
 * @return Retained restriction, or NULL on error.
 *
 * @public @memberof CowlDataCard
 */
COWL_PUBLIC
CowlDataCard *cowl_data_card(CowlCardType type, CowlAnyDataPropExp *prop, CowlAnyDataRange *range,
                             ulib_uint cardinality);

/**
 * Gets the type of the specified data property cardinality restriction.
 *
 * @param restr The restriction.
 * @return The type.
 *
 * @public @memberof CowlDataCard
 */
COWL_INLINE
CowlCardType cowl_data_card_get_type(CowlDataCard *restr) {
    return (CowlCardType)(cowl_get_type(restr) - COWL_OT_CE_DATA_MIN_CARD);
}

/**
 * Gets the property of the restriction.
 *
 * @param restr The restriction.
 * @return The property.
 *
 * @public @memberof CowlDataCard
 */
COWL_INLINE
CowlDataPropExp *cowl_data_card_get_prop(CowlDataCard *restr) {
    return (CowlDataPropExp *)cowl_get_field(restr, 0);
}

/**
 * Gets the range of the restriction.
 *
 * @param restr The restriction.
 * @return The range.
 *
 * @public @memberof CowlDataCard
 */
COWL_PUBLIC
CowlDataRange *cowl_data_card_get_range(CowlDataCard *restr);

/**
 * Gets the cardinality of the restriction.
 *
 * @param restr The restriction.
 * @return The cardinality.
 *
 * @public @memberof CowlDataCard
 */
COWL_INLINE
ulib_uint cowl_data_card_get_cardinality(CowlDataCard *restr) {
    return cowl_get_uint_field(restr);
}

/**
 * Returns the string representation of the specified restriction.
 *
 * @param restr The restriction.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDataCard
 */
COWL_INLINE
CowlString *cowl_data_card_to_string(CowlDataCard *restr) {
    return cowl_to_string(restr);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataCard
 */
COWL_INLINE
bool cowl_data_card_equals(CowlDataCard *lhs, CowlDataCard *rhs) {
    return cowl_uint_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param restr The restriction.
 * @return The hash value.
 *
 * @public @memberof CowlDataCard
 */
COWL_INLINE
ulib_uint cowl_data_card_hash(CowlDataCard *restr) {
    return cowl_uint_hash_impl(restr);
}

/**
 * Iterates over the primitives referenced by the specified data property cardinality restriction.
 *
 * @param restr The restriction.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataCard
 */
COWL_INLINE
bool cowl_data_card_iterate_primitives(CowlDataCard *restr, CowlPrimitiveFlags flags,
                                       CowlIterator *iter) {
    return cowl_iterate_primitives_impl(restr, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DATA_CARD_H
