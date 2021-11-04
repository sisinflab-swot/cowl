/**
 * Declares CowlSubObjPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_OBJ_PROP_AXIOM_H
#define COWL_SUB_OBJ_PROP_AXIOM_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
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
COWL_PUBLIC
CowlSubObjPropAxiom* cowl_sub_obj_prop_axiom_get(CowlObjPropExp *sub, CowlObjPropExp *super,
                                                 CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_PUBLIC
CowlSubObjPropAxiom* cowl_sub_obj_prop_axiom_retain(CowlSubObjPropAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_PUBLIC
void cowl_sub_obj_prop_axiom_release(CowlSubObjPropAxiom *axiom);

/**
 * Gets the superproperty.
 *
 * @param axiom The axiom.
 * @return The superproperty.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_PUBLIC
CowlObjPropExp* cowl_sub_obj_prop_axiom_get_super(CowlSubObjPropAxiom *axiom);

/**
 * Gets the subproperty.
 *
 * @param axiom The axiom.
 * @return The subproperty.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_PUBLIC
CowlObjPropExp* cowl_sub_obj_prop_axiom_get_sub(CowlSubObjPropAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_sub_obj_prop_axiom_get_annot(CowlSubObjPropAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_PUBLIC
CowlString* cowl_sub_obj_prop_axiom_to_string(CowlSubObjPropAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_PUBLIC
bool cowl_sub_obj_prop_axiom_equals(CowlSubObjPropAxiom *lhs, CowlSubObjPropAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_PUBLIC
ulib_uint cowl_sub_obj_prop_axiom_hash(CowlSubObjPropAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlSubObjPropAxiom
 */
COWL_PUBLIC
bool cowl_sub_obj_prop_axiom_iterate_primitives(CowlSubObjPropAxiom *axiom,
                                                CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_SUB_OBJ_PROP_AXIOM_H
