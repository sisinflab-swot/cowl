/**
 * Declares CowlInvObjPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
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
COWL_INLINE
CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_get(CowlObjPropExp *first, CowlObjPropExp *second,
                                                 CowlVector *annot) {
    return (CowlInvObjPropAxiom *)cowl_get_impl_2_opt(COWL_OT_A_INV_OBJ_PROP, first, second, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_INLINE
CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_retain(CowlInvObjPropAxiom *axiom) {
    return (CowlInvObjPropAxiom *)cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_INLINE
void cowl_inv_obj_prop_axiom_release(CowlInvObjPropAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Gets the first of the two object property expressions.
 *
 * @param axiom The axiom.
 * @return The first object property expression.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_INLINE
CowlObjPropExp* cowl_inv_obj_prop_axiom_get_first_prop(CowlInvObjPropAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the second of the two object property expressions.
 *
 * @param axiom The axiom.
 * @return The second object property expression.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_INLINE
CowlObjPropExp* cowl_inv_obj_prop_axiom_get_second_prop(CowlInvObjPropAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_INLINE
CowlVector* cowl_inv_obj_prop_axiom_get_annot(CowlInvObjPropAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

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
COWL_INLINE
CowlString* cowl_inv_obj_prop_axiom_to_string(CowlInvObjPropAxiom *axiom) {
    return cowl_to_string_impl(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_INLINE
bool cowl_inv_obj_prop_axiom_equals(CowlInvObjPropAxiom *lhs, CowlInvObjPropAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_INLINE
ulib_uint cowl_inv_obj_prop_axiom_hash(CowlInvObjPropAxiom *axiom) {
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
 * @public @memberof CowlInvObjPropAxiom
 */
COWL_INLINE
bool cowl_inv_obj_prop_axiom_iterate_primitives(CowlInvObjPropAxiom *axiom,
                                                CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_INV_OBJ_PROP_AXIOM_H
