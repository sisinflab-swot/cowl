/**
 * Declares CowlInvObjPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INV_OBJ_PROP_AXIOM_H
#define COWL_INV_OBJ_PROP_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents an [InverseObjectProperties] axiom in the OWL 2 specification.
 *
 * [InverseObjectProperties]: https://www.w3.org/TR/owl2-syntax/#Inverse_Object_Properties_2
 *
 * @superstruct{CowlAxiom}
 * @struct CowlInvObjPropAxiom
 */
cowl_struct_decl(CowlInvObjPropAxiom);

/**
 * @defgroup CowlInvObjPropAxiom CowlInvObjPropAxiom API
 * @{
 */

/**
 * Returns an inverse object properties axiom.
 *
 * @param first The first object property expression.
 * @param second The second object property expression.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlInvObjPropAxiom *
cowl_inv_obj_prop_axiom(CowlAnyObjPropExp *first, CowlAnyObjPropExp *second, CowlVector *annot) {
    return (CowlInvObjPropAxiom *)cowl_get_impl_2_annot(COWL_OT_A_INV_OBJ_PROP, first, second,
                                                        annot);
}

/**
 * Gets the first of the two object property expressions.
 *
 * @param axiom The axiom.
 * @return The first object property expression.
 */
COWL_PURE
COWL_INLINE
CowlObjPropExp *cowl_inv_obj_prop_axiom_get_first_prop(CowlInvObjPropAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the second of the two object property expressions.
 *
 * @param axiom The axiom.
 * @return The second object property expression.
 */
COWL_PURE
COWL_INLINE
CowlObjPropExp *cowl_inv_obj_prop_axiom_get_second_prop(CowlInvObjPropAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_INV_OBJ_PROP_AXIOM_H
