/**
 * Declares CowlDataRange and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_RANGE_H
#define COWL_DATA_RANGE_H

#include "cowl_data_range_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlDataRange);
/// @endcond

/**
 * Represents a [DataRange] in the OWL 2 specification.
 *
 * [DataRange]: https://www.w3.org/TR/owl2-syntax/#Data_Ranges
 *
 * @struct CowlDataRange
 * @extends CowlObject
 */

/**
 * Gets the type of the specified data range.
 *
 * @param range The data range.
 * @return The type.
 *
 * @public @memberof CowlDataRange
 */
COWL_INLINE
CowlDataRangeType cowl_data_range_get_type(CowlAnyDataRange *range) {
    return (CowlDataRangeType)(cowl_get_type(range) - COWL_OT_DR_DATATYPE);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataRange
 */
COWL_INLINE
bool cowl_data_range_equals(CowlAnyDataRange *lhs, CowlAnyDataRange *rhs) {
    return cowl_equals(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param range The data range.
 * @return The hash value.
 *
 * @public @memberof CowlDataRange
 */
COWL_INLINE
ulib_uint cowl_data_range_hash(CowlAnyDataRange *range) {
    return cowl_hash(range);
}

COWL_END_DECLS

#endif // COWL_DATA_RANGE_H
