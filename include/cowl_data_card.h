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

#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_card_type.h"
#include "cowl_impl.h"
#include "cowl_object.h"
#include "cowl_object_type.h"
#include "cowl_utils.h"
#include "ulib.h"
#include <stddef.h>

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDataPropExp);
/// @endcond

/**
 * Represents [DataMinCardinality], [DataMaxCardinality] and [DataExactCardinality]
 * in the OWL 2 specification.
 *
 * [DataMinCardinality]: https://www.w3.org/TR/owl2-syntax/#Minimum_Cardinality_2
 * [DataMaxCardinality]: https://www.w3.org/TR/owl2-syntax/#Maximum_Cardinality_2
 * [DataExactCardinality]: https://www.w3.org/TR/owl2-syntax/#Exact_Cardinality_2
 *
 * @superstruct{CowlClsExp}
 * @struct CowlDataCard
 */
cowl_struct_decl(CowlDataCard);

/**
 * @defgroup CowlDataCard CowlDataCard API
 * @{
 */

/**
 * Returns a data property cardinality restriction.
 *
 * @param type The type.
 * @param prop The data property.
 * @param range @ctype{optional} Range of the restriction.
 * @param cardinality Cardinality of the restriction.
 * @return Restriction, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDataCard *cowl_data_card(CowlCardType type, CowlAnyDataPropExp *prop, CowlAnyDataRange *range,
                             ulib_uint cardinality) {
    if (!cowl_enum_value_is_valid(CT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_CE_DATA_MIN_CARD + (CowlObjectType)type);
    return (CowlDataCard *)cowl_get_impl_1_uint_opt(t, prop, cardinality, range);
}

/**
 * Gets the type of the specified data property cardinality restriction.
 *
 * @param restr The restriction.
 * @return The type.
 */
COWL_PURE
COWL_INLINE
CowlCardType cowl_data_card_get_type(CowlDataCard *restr) {
    return (CowlCardType)(cowl_get_type(restr) - COWL_OT_CE_DATA_MIN_CARD);
}

/**
 * Checks if the specified data property cardinality restriction has a range.
 *
 * @param restr The restriction.
 * @return True if the restriction has a range, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_data_card_is_qualified(CowlDataCard *restr) {
    return cowl_has_opt_field(restr);
}

/**
 * Gets the property of the restriction.
 *
 * @param restr The restriction.
 * @return The property.
 */
COWL_PURE
COWL_INLINE
CowlDataPropExp *cowl_data_card_get_prop(CowlDataCard *restr) {
    return (CowlDataPropExp *)cowl_get_field(restr, 0);
}

/**
 * Gets the range of the restriction.
 *
 * @param restr The restriction.
 * @return The range.
 */
COWL_PURE
COWL_INLINE
CowlDataRange *cowl_data_card_get_range(CowlDataCard *restr) {
    return (CowlDataRange *)cowl_get_opt_field(restr);
}

/**
 * Gets the cardinality of the restriction.
 *
 * @param restr The restriction.
 * @return The cardinality.
 */
COWL_PURE
COWL_INLINE
ulib_uint cowl_data_card_get_cardinality(CowlDataCard *restr) {
    return cowl_get_uint_field(restr);
}

/// @}

COWL_END_DECLS

#endif // COWL_DATA_CARD_H
