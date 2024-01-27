/**
 * Declares CowlSubObjPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_OBJ_PROP_AXIOM_H
#define COWL_SUB_OBJ_PROP_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [SubObjectPropertyOf] axiom in the OWL 2 specification.
 *
 * [SubObjectPropertyOf]: https://www.w3.org/TR/owl2-syntax/#Object_Subproperties
 *
 * @superstruct{CowlAxiom}
 * @struct CowlSubObjPropAxiom
 */
cowl_struct_decl(CowlSubObjPropAxiom);

/**
 * @defgroup CowlSubObjPropAxiom CowlSubObjPropAxiom API
 * @{
 */

/**
 * Returns an object subproperty axiom.
 *
 * @param sub The subproperty.
 * @param super The superproperty.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlSubObjPropAxiom *
cowl_sub_obj_prop_axiom(CowlAnyObjPropExp *sub, CowlAnyObjPropExp *super, CowlVector *annot) {
    return (CowlSubObjPropAxiom *)cowl_get_impl_2_annot(COWL_OT_A_SUB_OBJ_PROP, sub, super, annot);
}

/**
 * Returns an object subproperty axiom where the subproperty is a chain of properties.
 *
 * @param sub The chain of properties.
 * @param super The superproperty.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlSubObjPropAxiom *
cowl_sub_obj_prop_chain_axiom(CowlVector *sub, CowlAnyObjPropExp *super, CowlVector *annot);

/**
 * Gets the subproperty.
 *
 * @param axiom The axiom.
 * @return The subproperty.
 *
 * @note The subproperty can be either an object property expression or a property expression chain.
 */
COWL_PURE
COWL_INLINE
CowlAny *cowl_sub_obj_prop_axiom_get_sub(CowlSubObjPropAxiom *axiom) {
    return cowl_get_field(axiom, 0);
}

/**
 * Gets the superproperty.
 *
 * @param axiom The axiom.
 * @return The superproperty.
 */
COWL_PURE
COWL_INLINE
CowlObjPropExp *cowl_sub_obj_prop_axiom_get_super(CowlSubObjPropAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_SUB_OBJ_PROP_AXIOM_H
