/**
 * Declares CowlDataPropExp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_EXP_H
#define COWL_DATA_PROP_EXP_H

#include "cowl_data_prop.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataProp);
/// @endcond

/**
 * Represents a [DataPropertyExpression] in the OWL 2 specification.
 *
 * [DataPropertyExpression]: https://www.w3.org/TR/owl2-syntax/#Data_Property_Expressions
 *
 * @superstruct{CowlObject}
 * @struct CowlDataPropExp
 */
cowl_struct_decl(CowlDataPropExp);

/**
 * @defgroup CowlDataPropExp CowlDataPropExp API
 * @{
 */

/**
 * Gets the underlying data property.
 *
 * @param exp The data property expression.
 * @return The data property.
 */
COWL_PURE
COWL_INLINE
CowlDataProp *cowl_data_prop_exp_get_prop(CowlAnyDataPropExp *exp) {
    return (CowlDataProp *)exp;
}

/// @}

COWL_END_DECLS

#endif // COWL_DATA_PROP_EXP_H
