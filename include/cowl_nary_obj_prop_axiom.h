/**
 * Declares CowlNAryObjPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_OBJ_PROP_AXIOM_H
#define COWL_NARY_OBJ_PROP_AXIOM_H

#include "cowl_nary_axiom_type.h"
#include "cowl_object.h"

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
CowlNAryObjPropAxiom *
cowl_nary_obj_prop_axiom(CowlNAryAxiomType type, CowlVector *props, CowlVector *annot) {
    if (!cowl_enum_value_is_valid(NAT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_A_EQUIV_OBJ_PROP + (CowlObjectType)type);
    return (CowlNAryObjPropAxiom *)cowl_get_impl_1_annot(t, props, annot);
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
CowlVector *cowl_nary_obj_prop_axiom_get_props(CowlNAryObjPropAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 0);
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
CowlVector *cowl_nary_obj_prop_axiom_get_annot(CowlNAryObjPropAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
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

COWL_END_DECLS

#endif // COWL_NARY_OBJ_PROP_AXIOM_H
