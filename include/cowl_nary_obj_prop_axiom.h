/**
 * Declares CowlNAryObjPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_OBJ_PROP_AXIOM_H
#define COWL_NARY_OBJ_PROP_AXIOM_H

#include "cowl_object_impl.h"
#include "cowl_nary_axiom_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlNAryObjPropAxiom);
/// @endcond

/**
 * Represents an [EquivalentObjectProperties] or [DisjointObjectProperties] axiom
 * in the OWL 2 specification.
 *
 * [EquivalentObjectProperties]: https://www.w3.org/TR/owl2-syntax/#Equivalent_Object_Properties
 * [DisjointObjectProperties]: https://www.w3.org/TR/owl2-syntax/#Disjoint_Object_Properties
 *
 * @struct CowlNAryObjPropAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained N-ary object property axiom.
 *
 * @param type The type.
 * @param props The object properties.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_INLINE
CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_get(CowlNAryAxiomType type,
                                                   CowlVector *props,
                                                   CowlVector *annot) {
    if (!cowl_enum_value_is_valid(NAT, type)) return NULL;
    return cowl_get_impl_1(COWL_OT_A_EQUIV_OBJ_PROP + type, props, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_INLINE
CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_retain(CowlNAryObjPropAxiom *axiom) {
    return cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_INLINE
void cowl_nary_obj_prop_axiom_release(CowlNAryObjPropAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Gets the type of the specified N-ary object property axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_INLINE
CowlNAryAxiomType cowl_nary_obj_prop_axiom_get_type(CowlNAryObjPropAxiom *axiom) {
    return (CowlNAryAxiomType)(cowl_get_type(axiom) - COWL_OT_A_EQUIV_OBJ_PROP);
}

/**
 * Gets the object properties of the specified N-ary object property axiom.
 *
 * @param axiom The axiom.
 * @return The object properties.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_INLINE
CowlVector* cowl_nary_obj_prop_axiom_get_props(CowlNAryObjPropAxiom *axiom) {
    return cowl_get_field(axiom, 0);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_INLINE
CowlVector* cowl_nary_obj_prop_axiom_get_annot(CowlNAryObjPropAxiom *axiom) {
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
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_INLINE
CowlString* cowl_nary_obj_prop_axiom_to_string(CowlNAryObjPropAxiom *axiom) {
    return cowl_to_string_impl(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_INLINE
bool cowl_nary_obj_prop_axiom_equals(CowlNAryObjPropAxiom *lhs, CowlNAryObjPropAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_INLINE
ulib_uint cowl_nary_obj_prop_axiom_hash(CowlNAryObjPropAxiom *axiom) {
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
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_INLINE
bool cowl_nary_obj_prop_axiom_iterate_primitives(CowlNAryObjPropAxiom *axiom,
                                                 CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_NARY_OBJ_PROP_AXIOM_H
