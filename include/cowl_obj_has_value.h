/**
 * Declares CowlObjHasValue and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_HAS_VALUE_H
#define COWL_OBJ_HAS_VALUE_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlObjHasValue);
/// @endcond

/**
 * Represents [ObjectHasValue] in the OWL 2 specification.
 *
 * [ObjectHasValue]: https://www.w3.org/TR/owl2-syntax/#Individual_Value_Restriction
 *
 * @struct CowlObjHasValue
 * @extends CowlClsExp
 */

/**
 * Returns a retained individual value restriction.
 *
 * @param prop The object property expression.
 * @param individual The individual.
 * @return Retained restriction, or NULL on error.
 *
 * @public @memberof CowlObjHasValue
 */
COWL_PUBLIC
CowlObjHasValue* cowl_obj_has_value_get(CowlObjPropExp *prop, CowlIndividual *individual);

/**
 * Retains the specified individual value restriction.
 *
 * @param exp The restriction.
 * @return Retained restriction.
 *
 * @public @memberof CowlObjHasValue
 */
COWL_PUBLIC
CowlObjHasValue* cowl_obj_has_value_retain(CowlObjHasValue *exp);

/**
 * Releases the specified individual value restriction.
 *
 * @param exp The restriction.
 *
 * @public @memberof CowlObjHasValue
 */
COWL_PUBLIC
void cowl_obj_has_value_release(CowlObjHasValue *exp);

/**
 * Gets the object property expression of the specified individual value restriction.
 *
 * @param exp The restriction.
 * @return The object property expression.
 *
 * @public @memberof CowlObjHasValue
 */
COWL_PUBLIC
CowlObjPropExp* cowl_obj_has_value_get_prop(CowlObjHasValue *exp);

/**
 * Gets the individual of the specified individual value restriction.
 *
 * @param exp The restriction.
 * @return The individual.
 *
 * @public @memberof CowlObjHasValue
 */
COWL_PUBLIC
CowlIndividual* cowl_obj_has_value_get_ind(CowlObjHasValue *exp);

/**
 * Returns the string representation of the specified value restriction.
 *
 * @param exp The restriction.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjHasValue
 */
COWL_PUBLIC
CowlString* cowl_obj_has_value_to_string(CowlObjHasValue *exp);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjHasValue
 */
COWL_PUBLIC
bool cowl_obj_has_value_equals(CowlObjHasValue *lhs, CowlObjHasValue *rhs);

/**
 * Hash function.
 *
 * @param exp The restriction.
 * @return The hash value.
 *
 * @public @memberof CowlObjHasValue
 */
COWL_PUBLIC
ulib_uint cowl_obj_has_value_hash(CowlObjHasValue *exp);

/**
 * Iterates over the primitives referenced by
 * the specified individual value restriction.
 *
 * @param exp The restriction.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjHasValue
 */
COWL_PUBLIC
bool cowl_obj_has_value_iterate_primitives(CowlObjHasValue *exp, CowlPrimitiveFlags flags,
                                           CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_HAS_VALUE_H
