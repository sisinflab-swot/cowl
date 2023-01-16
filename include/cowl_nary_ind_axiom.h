/**
 * Declares CowlNAryIndAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_IND_AXIOM_H
#define COWL_NARY_IND_AXIOM_H

#include "cowl_nary_axiom_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlNAryIndAxiom);
/// @endcond

/**
 * Represents a [SameIndividuals] or [DifferentIndividuals] axiom in the OWL 2 specification.
 *
 * [SameIndividuals]: https://www.w3.org/TR/owl2-syntax/#Individual_Equality
 * [DifferentIndividuals]: https://www.w3.org/TR/owl2-syntax/#Individual_Inequality
 *
 * @struct CowlNAryIndAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained N-ary individual axiom.
 *
 * @param type The type.
 * @param individuals The individuals.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_INLINE
CowlNAryIndAxiom *
cowl_nary_ind_axiom(CowlNAryAxiomType type, CowlVector *individuals, CowlVector *annot) {
    if (!cowl_enum_value_is_valid(NAT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_A_SAME_IND + (CowlObjectType)type);
    return (CowlNAryIndAxiom *)cowl_get_impl_1_annot(t, individuals, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_INLINE
CowlNAryIndAxiom *cowl_nary_ind_axiom_retain(CowlNAryIndAxiom *axiom) {
    return (CowlNAryIndAxiom *)cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_INLINE
void cowl_nary_ind_axiom_release(CowlNAryIndAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Gets the type of the specified N-ary individual axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_INLINE
CowlNAryAxiomType cowl_nary_ind_axiom_get_type(CowlNAryIndAxiom *axiom) {
    return (CowlNAryAxiomType)(cowl_get_type(axiom) - COWL_OT_A_SAME_IND);
}

/**
 * Gets the individuals of the specified N-ary individual axiom.
 *
 * @param axiom The axiom.
 * @return The individuals.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_INLINE
CowlVector *cowl_nary_ind_axiom_get_individuals(CowlNAryIndAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 0);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_INLINE
CowlVector *cowl_nary_ind_axiom_get_annot(CowlNAryIndAxiom *axiom) {
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
 * @public @memberof CowlNAryIndAxiom
 */
COWL_INLINE
CowlString *cowl_nary_ind_axiom_to_string(CowlNAryIndAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_INLINE
bool cowl_nary_ind_axiom_equals(CowlNAryIndAxiom *lhs, CowlNAryIndAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_INLINE
ulib_uint cowl_nary_ind_axiom_hash(CowlNAryIndAxiom *axiom) {
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
 * @public @memberof CowlNAryIndAxiom
 */
COWL_INLINE
bool cowl_nary_ind_axiom_iterate_primitives(CowlNAryIndAxiom *axiom, CowlPrimitiveFlags flags,
                                            CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_NARY_IND_AXIOM_H
