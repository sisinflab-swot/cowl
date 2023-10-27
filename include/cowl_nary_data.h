/**
 * Declares CowlNAryData and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_DATA_H
#define COWL_NARY_DATA_H

#include "cowl_nary_type.h"
#include "cowl_object.h"

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
 * Returns a N-ary data range.
 *
 * @param type N-ary data range type.
 * @param operands The operands.
 * @return N-ary data range, or NULL on error.
 *
 * @public @memberof CowlNAryData
 */
COWL_RETAINED
COWL_INLINE
CowlNAryData *cowl_nary_data(CowlNAryType type, CowlVector *operands) {
    if (!cowl_enum_value_is_valid(NT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_DR_DATA_INTERSECT + (CowlObjectType)type);
    return (CowlNAryData *)cowl_get_impl_1(t, operands);
}

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
CowlVector *cowl_nary_data_get_operands(CowlNAryData *range) {
    return (CowlVector *)cowl_get_field(range, 0);
}

COWL_END_DECLS

#endif // COWL_NARY_DATA_H
