/**
 * Declares CowlDataPropExp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
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
 * Retains the specified data property expression.
 *
 * @param exp The data property expression.
 * @return Retained data property expression.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_INLINE
CowlAnyDataPropExp* cowl_data_prop_exp_retain(CowlAnyDataPropExp *exp) {
    return (CowlAnyDataPropExp *)cowl_data_prop_retain((CowlDataProp *)exp);
}

/**
 * Releases the specified data property expression.
 *
 * @param exp The data property expression.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_INLINE
void cowl_data_prop_exp_release(CowlAnyDataPropExp *exp) {
    cowl_data_prop_release((CowlDataProp *)exp);
}

/**
 * Gets the underlying data property.
 *
 * @param exp The data property expression.
 * @return The data property.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_INLINE
CowlDataProp* cowl_data_prop_exp_get_prop(CowlAnyDataPropExp *exp) {
    return (CowlDataProp *)exp;
}

/**
 * Returns the string representation of the specified data property expression.
 *
 * @param exp The data property expression.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_INLINE
CowlString* cowl_data_prop_exp_to_string(CowlAnyDataPropExp *exp) {
    return cowl_data_prop_to_string((CowlDataProp *)exp);
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

/**
 * Iterates over the primitives referenced by the specified data property expression.
 *
 * @param exp The data property expression.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_INLINE
bool cowl_data_prop_exp_iterate_primitives(CowlAnyDataPropExp *exp, CowlPrimitiveFlags flags,
                                           CowlIterator *iter) {
    return cowl_data_prop_iterate_primitives((CowlDataProp *)exp, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DATA_PROP_EXP_H
