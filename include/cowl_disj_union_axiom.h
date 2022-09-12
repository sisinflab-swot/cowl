/**
 * Declares CowlDisjUnionAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DISJ_UNION_AXIOM_H
#define COWL_DISJ_UNION_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlDisjUnionAxiom);
/// @endcond

/**
 * Represents a [DisjointUnion] axiom in the OWL 2 specification.
 *
 * [DisjointUnion]: https://www.w3.org/TR/owl2-syntax/#Disjoint_Union_of_Class_Expressions
 *
 * @struct CowlDisjUnionAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained disjoint union axiom.
 *
 * @param cls The class which is equivalent to the disjoint union.
 * @param disjoints The class expressions which are operands of the disjoint union.
 * @param annot [optional] The annotations.
 * @return Retained disjoint union axiom, or NULL on error.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_INLINE
CowlDisjUnionAxiom* cowl_disj_union_axiom(CowlClass *cls, CowlVector *disjoints, CowlVector *annot) {
    return (CowlDisjUnionAxiom *)cowl_get_impl_2_opt(COWL_OT_A_DISJ_UNION, cls, disjoints, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_INLINE
CowlDisjUnionAxiom* cowl_disj_union_axiom_retain(CowlDisjUnionAxiom *axiom) {
    return (CowlDisjUnionAxiom *)cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_INLINE
void cowl_disj_union_axiom_release(CowlDisjUnionAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Gets the class which is equivalent to the disjoint union.
 *
 * @param axiom The axiom.
 * @return The class.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_INLINE
CowlClass* cowl_disj_union_axiom_get_class(CowlDisjUnionAxiom *axiom) {
    return (CowlClass *)cowl_get_field(axiom, 0);
}

/**
 * Gets the class expressions which are operands of the disjoint union.
 * @param axiom The axiom.
 * @return The class expressions.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_INLINE
CowlVector* cowl_disj_union_axiom_get_disjoints(CowlDisjUnionAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_INLINE
CowlVector* cowl_disj_union_axiom_get_annot(CowlDisjUnionAxiom *axiom) {
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
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_INLINE
CowlString* cowl_disj_union_axiom_to_string(CowlDisjUnionAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_INLINE
bool cowl_disj_union_axiom_equals(CowlDisjUnionAxiom *lhs, CowlDisjUnionAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_INLINE
ulib_uint cowl_disj_union_axiom_hash(CowlDisjUnionAxiom *axiom) {
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
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_INLINE
bool cowl_disj_union_axiom_iterate_primitives(CowlDisjUnionAxiom *axiom, CowlPrimitiveFlags flags,
                                              CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DISJ_UNION_AXIOM_H
