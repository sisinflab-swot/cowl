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

#include "cowl_iterator.h"
#include "cowl_std.h"

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
 */

/**
 * Retains the specified data property expression.
 *
 * @param exp The data property expression.
 * @return Retained data property expression.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_PUBLIC
CowlDataPropExp* cowl_data_prop_exp_retain(CowlDataPropExp *exp);

/**
 * Releases the specified data property expression.
 *
 * @param exp The data property expression.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_PUBLIC
void cowl_data_prop_exp_release(CowlDataPropExp *exp);

/**
 * Gets the underlying data property.
 *
 * @param exp The data property expression.
 * @return The data property.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_PUBLIC
CowlDataProp* cowl_data_prop_exp_get_prop(CowlDataPropExp *exp);

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
COWL_PUBLIC
CowlString* cowl_data_prop_exp_to_string(CowlDataPropExp *exp);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_PUBLIC
bool cowl_data_prop_exp_equals(CowlDataPropExp *lhs, CowlDataPropExp *rhs);

/**
 * Hash function.
 *
 * @param exp The data property expression.
 * @return The hash value.
 *
 * @public @memberof CowlDataPropExp
 */
COWL_PUBLIC
ulib_uint cowl_data_prop_exp_hash(CowlDataPropExp *exp);

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
COWL_PUBLIC
bool cowl_data_prop_exp_iterate_primitives(CowlDataPropExp *exp, CowlPrimitiveFlags flags,
                                           CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_DATA_PROP_EXP_H
