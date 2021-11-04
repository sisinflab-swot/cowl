/**
 * Declares CowlSubObjPropChainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_OBJ_PROP_CHAIN_AXIOM_H
#define COWL_SUB_OBJ_PROP_CHAIN_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
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
COWL_PUBLIC
CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_get(CowlObjectVec *sub,
                                                            CowlObjPropExp *super,
                                                            CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_PUBLIC
CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_retain(CowlSubObjPropChainAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_PUBLIC
void cowl_sub_obj_prop_chain_axiom_release(CowlSubObjPropChainAxiom *axiom);

/**
 * Gets the chain of properties that represents the subproperty.
 *
 * @param axiom The axiom.
 * @return The properties.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_sub_obj_prop_chain_axiom_get_sub_props(CowlSubObjPropChainAxiom *axiom);

/**
 * Gets the superproperty.
 *
 * @param axiom The axiom.
 * @return The superproperty.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_PUBLIC
CowlObjPropExp* cowl_sub_obj_prop_chain_axiom_get_super_prop(CowlSubObjPropChainAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_sub_obj_prop_chain_axiom_get_annot(CowlSubObjPropChainAxiom *axiom);

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
COWL_PUBLIC
CowlString* cowl_sub_obj_prop_chain_axiom_to_string(CowlSubObjPropChainAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_PUBLIC
bool cowl_sub_obj_prop_chain_axiom_equals(CowlSubObjPropChainAxiom *lhs,
                                          CowlSubObjPropChainAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_PUBLIC
ulib_uint cowl_sub_obj_prop_chain_axiom_hash(CowlSubObjPropChainAxiom *axiom);

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
COWL_PUBLIC
bool cowl_sub_obj_prop_chain_axiom_iterate_primitives(CowlSubObjPropChainAxiom *axiom,
                                                      CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_SUB_OBJ_PROP_CHAIN_AXIOM_H
