/**
 * Declares CowlObjPropExp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_EXP_H
#define COWL_OBJ_PROP_EXP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjProp);
cowl_struct_decl(CowlObjPropExp);
/// @endcond

/**
 * Represents an [ObjectPropertyExpression] in the OWL 2 specification.
 *
 * [ObjectPropertyExpression]: https://www.w3.org/TR/owl2-syntax/#Object_Property_Expressions
 *
 * @struct CowlObjPropExp
 */

/**
 * Retains the specified object property expression.
 *
 * @param prop The object property expression.
 * @return Retained object property expression.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_PUBLIC
CowlObjPropExp* cowl_obj_prop_exp_retain(CowlObjPropExp *prop);

/**
 * Releases the specified object property expression.
 *
 * @param prop The object property expression.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_PUBLIC
void cowl_obj_prop_exp_release(CowlObjPropExp *prop);

/**
 * Returns true if the object property expression is inverse.
 *
 * @param exp The object property expression.
 * @return True if the expression is inverse, false otherwise.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_PUBLIC
bool cowl_obj_prop_exp_is_inverse(CowlObjPropExp *exp);

/**
 * Gets the underlying object property.
 *
 * @param exp The object property expression.
 * @return The object property.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_PUBLIC
CowlObjProp* cowl_obj_prop_exp_get_prop(CowlObjPropExp *exp);

/**
 * Returns the string representation of the specified object property expression.
 *
 * @param exp The object property expression.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_PUBLIC
CowlString* cowl_obj_prop_exp_to_string(CowlObjPropExp *exp);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_PUBLIC
bool cowl_obj_prop_exp_equals(CowlObjPropExp *lhs, CowlObjPropExp *rhs);

/**
 * Hash function.
 *
 * @param exp The object property expression.
 * @return The hash value.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_PUBLIC
cowl_uint cowl_obj_prop_exp_hash(CowlObjPropExp *exp);

/**
 * Iterates over the primitives referenced by the specified object property expression.
 *
 * @param exp The object property expression.
 * @param iter The iterator.
 * @param flags Iteration flags.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_PUBLIC
bool cowl_obj_prop_exp_iterate_primitives(CowlObjPropExp *exp, CowlIterator *iter,
                                          CowlPrimitiveFlags flags);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_H
