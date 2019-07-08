/**
 * Declares CowlSubObjPropChainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
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
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);
cowl_vector_decl(CowlObjPropExpPtr, CowlObjPropExpVec);
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
 * @param annot The annotations.
 * @return Retained axiom.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_PUBLIC
CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_get(CowlObjPropExpVec *sub,
                                                            CowlObjPropExp *super,
                                                            CowlAnnotationVec *annot);

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
CowlObjPropExpVec* cowl_sub_obj_prop_chain_axiom_get_sub_props(CowlSubObjPropChainAxiom *axiom);

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
CowlAnnotationVec* cowl_sub_obj_prop_chain_axiom_get_annot(CowlSubObjPropChainAxiom *axiom);

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
cowl_uint_t cowl_sub_obj_prop_chain_axiom_hash(CowlSubObjPropChainAxiom *axiom);

/**
 * Iterates over the signature of the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlSubObjPropChainAxiom
 */
COWL_PUBLIC
bool cowl_sub_obj_prop_chain_axiom_iterate_signature(CowlSubObjPropChainAxiom *axiom,
                                                     CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_SUB_OBJ_PROP_CHAIN_AXIOM_H
