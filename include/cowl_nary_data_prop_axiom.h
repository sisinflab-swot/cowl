/**
 * Declares CowlNAryDataPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_DATA_PROP_AXIOM_H
#define COWL_NARY_DATA_PROP_AXIOM_H

#include "cowl_nary_axiom_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlNAryDataPropAxiom);
/// @endcond

/**
 * Represents an [EquivalentDataProperties] or [DisjointDataProperties] axiom
 * in the OWL 2 specification.
 *
 * [EquivalentDataProperties]: https://www.w3.org/TR/owl2-syntax/#Equivalent_Data_Properties
 * [DisjointDataProperties]: https://www.w3.org/TR/owl2-syntax/#Disjoint_Data_Properties
 *
 * @struct CowlNAryDataPropAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained N-ary data property axiom.
 *
 * @param type The type.
 * @param props The data properties.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_INLINE
CowlNAryDataPropAxiom *
cowl_nary_data_prop_axiom(CowlNAryAxiomType type, CowlVector *props, CowlVector *annot) {
    if (!cowl_enum_value_is_valid(NAT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_A_EQUIV_DATA_PROP + (CowlObjectType)type);
    return (CowlNAryDataPropAxiom *)cowl_get_impl_1_annot(t, props, annot);
}

/**
 * Gets the type of the specified N-ary data property axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_INLINE
CowlNAryAxiomType cowl_nary_data_prop_axiom_get_type(CowlNAryDataPropAxiom *axiom) {
    return (CowlNAryAxiomType)(cowl_get_type(axiom) - COWL_OT_A_EQUIV_DATA_PROP);
}

/**
 * Gets the data properties of the specified N-ary data property axiom.
 *
 * @param axiom The axiom.
 * @return The data properties.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_INLINE
CowlVector *cowl_nary_data_prop_axiom_get_props(CowlNAryDataPropAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 0);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_INLINE
CowlVector *cowl_nary_data_prop_axiom_get_annot(CowlNAryDataPropAxiom *axiom) {
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
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_INLINE
CowlString *cowl_nary_data_prop_axiom_to_string(CowlNAryDataPropAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_INLINE
bool cowl_nary_data_prop_axiom_equals(CowlNAryDataPropAxiom *lhs, CowlNAryDataPropAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_INLINE
ulib_uint cowl_nary_data_prop_axiom_hash(CowlNAryDataPropAxiom *axiom) {
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
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_INLINE
bool cowl_nary_data_prop_axiom_iterate_primitives(CowlNAryDataPropAxiom *axiom,
                                                  CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_NARY_DATA_PROP_AXIOM_H
