/**
 * Declares CowlDataHasValue and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_HAS_VALUE_H
#define COWL_DATA_HAS_VALUE_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlDataHasValue);
/// @endcond

/**
 * Represents [DataHasValue] in the OWL 2 specification.
 *
 * [DataHasValue]: https://www.w3.org/TR/owl2-syntax/#Literal_Value_Restriction
 *
 * @struct CowlDataHasValue
 * @extends CowlClsExp
 */

/**
 * Returns a retained literal value restriction.
 *
 * @param prop The data property expression.
 * @param value The restriction value.
 * @return Retained restriction, or NULL on error.
 *
 * @public @memberof CowlDataHasValue
 */
COWL_PUBLIC
CowlDataHasValue* cowl_data_has_value_get(CowlDataPropExp *prop, CowlLiteral *value);

/**
 * Retains the specified literal value restriction.
 *
 * @param restr The restriction.
 * @return Retained restriction.
 *
 * @public @memberof CowlDataHasValue
 */
COWL_PUBLIC
CowlDataHasValue* cowl_data_has_value_retain(CowlDataHasValue *restr);

/**
 * Releases the specified literal value restriction.
 *
 * @param restr The restriction.
 *
 * @public @memberof CowlDataHasValue
 */
COWL_PUBLIC
void cowl_data_has_value_release(CowlDataHasValue *restr);

/**
 * Gets the property of the restriction.
 *
 * @param restr The restriction.
 * @return The property.
 *
 * @public @memberof CowlDataHasValue
 */
COWL_PUBLIC
CowlDataPropExp* cowl_data_has_value_get_prop(CowlDataHasValue *restr);

/**
 * Gets the value of the restriction.
 *
 * @param restr The restriction.
 * @return The value.
 *
 * @public @memberof CowlDataHasValue
 */
COWL_PUBLIC
CowlLiteral* cowl_data_has_value_get_value(CowlDataHasValue *restr);

/**
 * Returns the string representation of the specified restriction.
 *
 * @param restr The restriction.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDataHasValue
 */
COWL_PUBLIC
CowlString* cowl_data_has_value_to_string(CowlDataHasValue *restr);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataHasValue
 */
COWL_PUBLIC
bool cowl_data_has_value_equals(CowlDataHasValue *lhs, CowlDataHasValue *rhs);

/**
 * Hash function.
 *
 * @param restr The restriction.
 * @return The hash value.
 *
 * @public @memberof CowlDataHasValue
 */
COWL_PUBLIC
ulib_uint cowl_data_has_value_hash(CowlDataHasValue *restr);

/**
 * Iterates over the primitives referenced by the specified literal value restriction.
 *
 * @param restr The restriction.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataHasValue
 */
COWL_PUBLIC
bool cowl_data_has_value_iterate_primitives(CowlDataHasValue *restr, CowlPrimitiveFlags flags,
                                            CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_DATA_HAS_VALUE_H
