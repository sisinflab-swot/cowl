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
/// @endcond

/**
 * Represents a [DataRange] in the OWL 2 specification.
 *
 * [DataRange]: https://www.w3.org/TR/owl2-syntax/#Data_Ranges
 *
 * @superstruct{CowlObject}
 * @struct CowlDataRange
 */
cowl_struct_decl(CowlDataRange);

/**
 * @defgroup CowlDataRange CowlDataRange API
 * @{
 */

/**
 * Gets the type of the specified data range.
 *
 * @param range The data range.
 * @return The type.
 */
COWL_PURE
COWL_INLINE
CowlDataRangeType cowl_data_range_get_type(CowlAnyDataRange *range) {
    return (CowlDataRangeType)(cowl_get_type(range) - COWL_OT_DR_DATATYPE);
}

/// @}

COWL_END_DECLS

#endif // COWL_DATA_RANGE_H
