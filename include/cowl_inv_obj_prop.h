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
/// @endcond

/**
 * Represents an [InverseObjectProperty] in the OWL 2 specification.
 *
 * [InverseObjectProperty]: https://www.w3.org/TR/owl2-syntax/#Inverse_Object_Properties
 *
 * @superstruct{CowlObjPropExp}
 * @struct CowlInvObjProp
 */
cowl_struct_decl(CowlInvObjProp);

/**
 * @defgroup CowlInvObjProp CowlInvObjProp API
 * @{
 */

/**
 * Returns an inverse object property.
 *
 * @param prop The object property of which the expression is the inverse of.
 * @return Inverse object property, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlInvObjProp *cowl_inv_obj_prop(CowlObjProp *prop) {
    return (CowlInvObjProp *)cowl_get_impl_1(COWL_OT_OPE_INV_OBJ_PROP, prop);
}

/**
 * Gets the property of which the expression is the inverse of.
 *
 * @param inv The inverse object property.
 * @return The property.
 */
COWL_PURE
COWL_INLINE
CowlObjProp *cowl_inv_obj_prop_get_prop(CowlInvObjProp *inv) {
    return (CowlObjProp *)cowl_get_field(inv, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_INV_OBJ_PROP_H
