/**
 * Declares CowlDataOneOf and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_COWL_DATA_ONE_OF_H
#define COWL_COWL_DATA_ONE_OF_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents [DataOneOf] in the OWL 2 specification.
 *
 * [DataOneOf]: https://www.w3.org/TR/owl2-syntax/#Enumeration_of_Literals
 *
 * @superstruct{CowlDataRange}
 * @struct CowlDataOneOf
 */
cowl_struct_decl(CowlDataOneOf);

/**
 * @defgroup CowlDataOneOf CowlDataOneOf API
 * @{
 */

/**
 * Returns a literal enumeration.
 *
 * @param values The enumeration values.
 * @return Literal enumeration, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDataOneOf *cowl_data_one_of(CowlVector *values) {
    return (CowlDataOneOf *)cowl_get_impl_1(COWL_OT_DR_DATA_ONE_OF, values);
}

/**
 * Gets the values of the specified literal enumeration.
 *
 * @param range The literal enumeration.
 * @return The values.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_data_one_of_get_values(CowlDataOneOf *range) {
    return (CowlVector *)cowl_get_field(range, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_COWL_DATA_ONE_OF_H
