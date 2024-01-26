/**
 * Declares CowlDataHasValue and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_HAS_VALUE_H
#define COWL_DATA_HAS_VALUE_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlLiteral);
/// @endcond

/**
 * Represents [DataHasValue] in the OWL 2 specification.
 *
 * [DataHasValue]: https://www.w3.org/TR/owl2-syntax/#Literal_Value_Restriction
 *
 * @superstruct{CowlClsExp}
 * @struct CowlDataHasValue
 */
cowl_struct_decl(CowlDataHasValue);

/**
 * @defgroup CowlDataHasValue CowlDataHasValue API
 * @{
 */

/**
 * Returns a literal value restriction.
 *
 * @param prop The data property expression.
 * @param value The restriction value.
 * @return Restriction, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDataHasValue *cowl_data_has_value(CowlAnyDataPropExp *prop, CowlLiteral *value) {
    return (CowlDataHasValue *)cowl_get_impl_2(COWL_OT_CE_DATA_HAS_VALUE, prop, value);
}

/**
 * Gets the property of the restriction.
 *
 * @param restr The restriction.
 * @return The property.
 */
COWL_PURE
COWL_INLINE
CowlDataPropExp *cowl_data_has_value_get_prop(CowlDataHasValue *restr) {
    return (CowlDataPropExp *)cowl_get_field(restr, 0);
}

/**
 * Gets the value of the restriction.
 *
 * @param restr The restriction.
 * @return The value.
 */
COWL_PURE
COWL_INLINE
CowlLiteral *cowl_data_has_value_get_value(CowlDataHasValue *restr) {
    return (CowlLiteral *)cowl_get_field(restr, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_DATA_HAS_VALUE_H
