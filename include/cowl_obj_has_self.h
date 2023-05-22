/**
 * Declares CowlObjHasSelf and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_HAS_SELF_H
#define COWL_OBJ_HAS_SELF_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlObjHasSelf);
/// @endcond

/**
 * Represents [ObjectHasSelf] in the OWL 2 specification.
 *
 * [ObjectHasSelf]: https://www.w3.org/TR/owl2-syntax/#Self-Restriction
 *
 * @struct CowlObjHasSelf
 * @extends CowlClsExp
 */

/**
 * Returns a retained self-restriction.
 *
 * @param prop The property expression.
 * @return Retained restriction, or NULL on error.
 *
 * @public @memberof CowlObjHasSelf
 */
COWL_INLINE
CowlObjHasSelf *cowl_obj_has_self(CowlAnyObjPropExp *prop) {
    return (CowlObjHasSelf *)cowl_get_impl_1(COWL_OT_CE_OBJ_HAS_SELF, prop);
}

/**
 * Gets the object property expression of the specified self-restriction.
 *
 * @param exp The restriction.
 * @return The object property expression.
 *
 * @public @memberof CowlObjHasSelf
 */
COWL_INLINE
CowlObjPropExp *cowl_obj_has_self_get_prop(CowlObjHasSelf *exp) {
    return (CowlObjPropExp *)cowl_get_field(exp, 0);
}

/**
 * Returns the string representation of the specified self-restriction.
 *
 * @param exp The restriction.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjHasSelf
 */
COWL_INLINE
CowlString *cowl_obj_has_self_to_string(CowlObjHasSelf *exp) {
    return cowl_to_string(exp);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjHasSelf
 */
COWL_INLINE
bool cowl_obj_has_self_equals(CowlObjHasSelf *lhs, CowlObjHasSelf *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param exp The restriction.
 * @return The hash value.
 *
 * @public @memberof CowlObjHasSelf
 */
COWL_INLINE
ulib_uint cowl_obj_has_self_hash(CowlObjHasSelf *exp) {
    return cowl_hash_impl(exp);
}

COWL_END_DECLS

#endif // COWL_OBJ_HAS_SELF_H
