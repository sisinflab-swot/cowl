/**
 * Declares CowlDataQuant and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_QUANT_H
#define COWL_DATA_QUANT_H

#include "cowl_object.h"
#include "cowl_quant_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDataPropExp);
/// @endcond

/**
 * Represents [DataSomeValuesFrom] and [DataAllValuesFrom] in the OWL 2 specification.
 *
 * [DataSomeValuesFrom]: https://www.w3.org/TR/owl2-syntax/#Existential_Quantification_2
 * [DataAllValuesFrom]: https://www.w3.org/TR/owl2-syntax/#Universal_Quantification_2
 *
 * @superstruct{CowlClsExp}
 * @struct CowlDataQuant
 */
cowl_struct_decl(CowlDataQuant);

/**
 * @defgroup CowlDataQuant CowlDataQuant API
 * @{
 */

/**
 * Returns a data quantifier.
 *
 * @param type Data quantifier type.
 * @param prop The data property.
 * @param range Range of the quantifier.
 * @return Data quantifier, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlDataQuant *
cowl_data_quant(CowlQuantType type, CowlAnyDataPropExp *prop, CowlAnyDataRange *range);

/**
 * Gets the type of the specified data quantifier.
 *
 * @param restr The data quantifier.
 * @return The type of the data quantifier.
 */
COWL_PURE
COWL_INLINE
CowlQuantType cowl_data_quant_get_type(CowlDataQuant *restr) {
    return (CowlQuantType)(cowl_get_type(restr) - COWL_OT_CE_DATA_SOME);
}

/**
 * Gets the data property.
 *
 * @param restr The data quantifier.
 * @return The data property.
 */
COWL_PURE
COWL_INLINE
CowlDataPropExp *cowl_data_quant_get_prop(CowlDataQuant *restr) {
    return (CowlDataPropExp *)cowl_get_field(restr, 0);
}

/**
 * Gets the range of the specified data quantifier.
 *
 * @param restr The data quantifier.
 * @return Range of the data quantifier.
 */
COWL_API
COWL_PURE
CowlDataRange *cowl_data_quant_get_range(CowlDataQuant *restr);

/// @}

COWL_END_DECLS

#endif // COWL_DATA_QUANT_H
