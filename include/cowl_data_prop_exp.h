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
cowl_struct_decl(CowlDataPropExp);
/// @endcond

/**
 * Represents a [DataPropertyExpression] in the OWL 2 specification.
 *
 * [DataPropertyExpression]: https://www.w3.org/TR/owl2-syntax/#Data_Property_Expressions
 *
 * @struct CowlDataPropExp
 * @extends CowlObject
 */

/**
 * Gets the underlying data property.
 *
 * @param exp The data property expression.
 * @return The data property.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_INLINE
CowlDataProp *cowl_data_prop_exp_get_prop(CowlAnyDataPropExp *exp) {
    return (CowlDataProp *)exp;
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_INLINE
bool cowl_data_prop_exp_equals(CowlAnyDataPropExp *lhs, CowlAnyDataPropExp *rhs) {
    return lhs == rhs;
}

/**
 * Hash function.
 *
 * @param exp The data property expression.
 * @return The hash value.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_INLINE
ulib_uint cowl_data_prop_exp_hash(CowlAnyDataPropExp *exp) {
    return uhash_ptr_hash(exp);
}

COWL_END_DECLS

#endif // COWL_DATA_PROP_EXP_H
