/**
 * Declares CowlInvObjProp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INV_OBJ_PROP_H
#define COWL_INV_OBJ_PROP_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjProp);
cowl_struct_decl(CowlInvObjProp);
/// @endcond

/**
 * Represents an [InverseObjectProperty] in the OWL 2 specification.
 *
 * [InverseObjectProperty]: https://www.w3.org/TR/owl2-syntax/#Inverse_Object_Properties
 *
 * @struct CowlInvObjProp
 * @extends CowlObjPropExp
 */

/**
 * Returns a retained inverse object property.
 *
 * @param prop The object property of which the expression is the inverse of.
 * @return Retained inverse object property, or NULL on error.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_INLINE
CowlInvObjProp *cowl_inv_obj_prop(CowlObjProp *prop) {
    return (CowlInvObjProp *)cowl_get_impl_1(COWL_OT_OPE_INV_OBJ_PROP, prop);
}

/**
 * Gets the property of which the expression is the inverse of.
 *
 * @param inv The inverse object property.
 * @return The property.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_INLINE
CowlObjProp *cowl_inv_obj_prop_get_prop(CowlInvObjProp *inv) {
    return (CowlObjProp *)cowl_get_field(inv, 0);
}

/**
 * Returns the string representation of the specified inverse object property.
 *
 * @param inv The inverse object property.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_INLINE
CowlString *cowl_inv_obj_prop_to_string(CowlInvObjProp *inv) {
    return cowl_to_string(inv);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_INLINE
bool cowl_inv_obj_prop_equals(CowlInvObjProp *lhs, CowlInvObjProp *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param inv The inverse object property.
 * @return The hash value.
 *
 * @public @memberof CowlInvObjProp
 */
COWL_INLINE
ulib_uint cowl_inv_obj_prop_hash(CowlInvObjProp *inv) {
    return cowl_hash_impl(inv);
}

COWL_END_DECLS

#endif // COWL_INV_OBJ_PROP_H
