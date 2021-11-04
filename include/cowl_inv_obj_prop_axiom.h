/**
 * Declares CowlInvObjPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INV_OBJ_PROP_AXIOM_H
#define COWL_INV_OBJ_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlInvObjPropAxiom);
/// @endcond

/**
 * Represents an [InverseObjectProperties] axiom in the OWL 2 specification.
 *
 * [InverseObjectProperties]: https://www.w3.org/TR/owl2-syntax/#Inverse_Object_Properties_2
 *
 * @struct CowlInvObjPropAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained inverse object properties axiom.
 *
 * @param first The first object property expression.
 * @param second The second object property expression.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_PUBLIC
CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_get(CowlObjPropExp *first, CowlObjPropExp *second,
                                                 CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_PUBLIC
CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_retain(CowlInvObjPropAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_PUBLIC
void cowl_inv_obj_prop_axiom_release(CowlInvObjPropAxiom *axiom);

/**
 * Gets the first of the two object property expressions.
 *
 * @param axiom The axiom.
 * @return The first object property expression.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_PUBLIC
CowlObjPropExp* cowl_inv_obj_prop_axiom_get_first_prop(CowlInvObjPropAxiom *axiom);

/**
 * Gets the second of the two object property expressions.
 *
 * @param axiom The axiom.
 * @return The second object property expression.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_PUBLIC
CowlObjPropExp* cowl_inv_obj_prop_axiom_get_second_prop(CowlInvObjPropAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_inv_obj_prop_axiom_get_annot(CowlInvObjPropAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_PUBLIC
CowlString* cowl_inv_obj_prop_axiom_to_string(CowlInvObjPropAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_PUBLIC
bool cowl_inv_obj_prop_axiom_equals(CowlInvObjPropAxiom *lhs, CowlInvObjPropAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_PUBLIC
ulib_uint cowl_inv_obj_prop_axiom_hash(CowlInvObjPropAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_PUBLIC
bool cowl_inv_obj_prop_axiom_iterate_primitives(CowlInvObjPropAxiom *axiom,
                                                CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_INV_OBJ_PROP_AXIOM_H
