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
cowl_struct_decl(CowlSubObjPropAxiom);
/// @endcond

/**
 * Represents a [SubObjectPropertyOf] axiom in the OWL 2 specification.
 *
 * [SubObjectPropertyOf]: https://www.w3.org/TR/owl2-syntax/#Object_Subproperties
 *
 * @struct CowlSubObjPropAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained object subproperty axiom.
 *
 * @param sub The subproperty.
 * @param super The superproperty.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_INLINE
CowlSubObjPropAxiom *
cowl_sub_obj_prop_axiom(CowlAnyObjPropExp *sub, CowlAnyObjPropExp *super, CowlVector *annot) {
    return (CowlSubObjPropAxiom *)cowl_get_impl_2_annot(COWL_OT_A_SUB_OBJ_PROP, sub, super, annot);
}

/**
 * Returns a retained object subproperty axiom where the subproperty is a chain of properties.
 *
 * @param sub The chain of properties.
 * @param super The superproperty.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_PUBLIC
CowlSubObjPropAxiom *
cowl_sub_obj_prop_chain_axiom(CowlVector *sub, CowlAnyObjPropExp *super, CowlVector *annot);

/**
 * Gets the subproperty.
 *
 * @param axiom The axiom.
 * @return The subproperty.
 *
 * @note The subproperty can be either an object property expression or a property expression chain.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_INLINE
CowlAny *cowl_sub_obj_prop_axiom_get_sub(CowlSubObjPropAxiom *axiom) {
    return cowl_get_field(axiom, 0);
}

/**
 * Gets the superproperty.
 *
 * @param axiom The axiom.
 * @return The superproperty.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_INLINE
CowlObjPropExp *cowl_sub_obj_prop_axiom_get_super(CowlSubObjPropAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_INLINE
CowlVector *cowl_sub_obj_prop_axiom_get_annot(CowlSubObjPropAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

COWL_END_DECLS

#endif // COWL_SUB_OBJ_PROP_AXIOM_H
