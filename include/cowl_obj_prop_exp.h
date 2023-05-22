/**
 * Declares CowlObjPropExp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_EXP_H
#define COWL_OBJ_PROP_EXP_H

#include "cowl_object.h"

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
 * @extends CowlObject
 */

/**
 * Returns true if the object property expression is inverse.
 *
 * @param exp The object property expression.
 * @return True if the expression is inverse, false otherwise.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_INLINE
bool cowl_obj_prop_exp_is_inverse(CowlAnyObjPropExp *exp) {
    return cowl_get_type(exp) == COWL_OT_OPE_INV_OBJ_PROP;
}

/**
 * Gets the underlying object property.
 *
 * @param exp The object property expression.
 * @return The object property.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_PUBLIC
CowlObjProp *cowl_obj_prop_exp_get_prop(CowlAnyObjPropExp *exp);

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
COWL_INLINE
CowlString *cowl_obj_prop_exp_to_string(CowlAnyObjPropExp *exp) {
    return cowl_to_string(exp);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_INLINE
bool cowl_obj_prop_exp_equals(CowlAnyObjPropExp *lhs, CowlAnyObjPropExp *rhs) {
    return cowl_equals(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param exp The object property expression.
 * @return The hash value.
 *
 * @public @memberof CowlObjPropExp
 */
COWL_INLINE
ulib_uint cowl_obj_prop_exp_hash(CowlAnyObjPropExp *exp) {
    return cowl_hash(exp);
}

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_H
