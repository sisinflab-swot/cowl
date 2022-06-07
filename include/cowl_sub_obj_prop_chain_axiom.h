/**
 * Declares CowlSubObjPropChainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_OBJ_PROP_CHAIN_AXIOM_H
#define COWL_SUB_OBJ_PROP_CHAIN_AXIOM_H

#include "cowl_object_impl.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlSubObjPropChainAxiom);
/// @endcond

/**
 * Represents a [SubObjectPropertyOf] axiom in the OWL 2 specification
 * where the subproperty is a chain of properties.
 *
 * [SubObjectPropertyOf]: https://www.w3.org/TR/owl2-syntax/#Object_Subproperties
 *
 * @struct CowlSubObjPropChainAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained object subproperty chain axiom.
 *
 * @param sub The chain of properties that represents the subproperty.
 * @param super The superproperty.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_INLINE
CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_get(CowlVector *sub,
                                                            CowlObjPropExp *super,
                                                            CowlVector *annot) {
    return cowl_get_impl_2(COWL_OT_A_SUB_OBJ_PROP_CHAIN, sub, super, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_INLINE
CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_retain(CowlSubObjPropChainAxiom *axiom) {
    return cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_INLINE
void cowl_sub_obj_prop_chain_axiom_release(CowlSubObjPropChainAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Gets the chain of properties that represents the subproperty.
 *
 * @param axiom The axiom.
 * @return The properties.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_INLINE
CowlVector* cowl_sub_obj_prop_chain_axiom_get_sub_props(CowlSubObjPropChainAxiom *axiom) {
    return cowl_get_field(axiom, 0);
}

/**
 * Gets the superproperty.
 *
 * @param axiom The axiom.
 * @return The superproperty.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_INLINE
CowlObjPropExp* cowl_sub_obj_prop_chain_axiom_get_super_prop(CowlSubObjPropChainAxiom *axiom) {
    return cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_INLINE
CowlVector* cowl_sub_obj_prop_chain_axiom_get_annot(CowlSubObjPropChainAxiom *axiom) {
    return cowl_get_opt_field(axiom);
}

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_INLINE
CowlString* cowl_sub_obj_prop_chain_axiom_to_string(CowlSubObjPropChainAxiom *axiom) {
    return cowl_to_string_impl(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_INLINE
bool cowl_sub_obj_prop_chain_axiom_equals(CowlSubObjPropChainAxiom *lhs,
                                          CowlSubObjPropChainAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_INLINE
ulib_uint cowl_sub_obj_prop_chain_axiom_hash(CowlSubObjPropChainAxiom *axiom) {
    return cowl_hash_impl(axiom);
}

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_INLINE
bool cowl_sub_obj_prop_chain_axiom_iterate_primitives(CowlSubObjPropChainAxiom *axiom,
                                                      CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_SUB_OBJ_PROP_CHAIN_AXIOM_H
