/**
 * Declares CowlAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_H
#define COWL_AXIOM_H

#include "cowl_axiom_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlAxiom);
/// @endcond

/**
 * Represents an [Axiom] in the OWL 2 specification.
 *
 * [Axiom]: https://www.w3.org/TR/owl2-syntax/#Axioms
 *
 * @struct CowlAxiom
 * @extends CowlObject
 */

/**
 * Gets the type of the specified axiom.
 *
 * @param axiom The axiom.
 * @return Axiom type.
 *
 * @public @memberof CowlAxiom
 */
COWL_INLINE
CowlAxiomType cowl_axiom_get_type(CowlAnyAxiom *axiom) {
    return (CowlAxiomType)(cowl_get_type(axiom) - COWL_OT_A_DECL);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlAxiom
 */
COWL_INLINE
CowlVector *cowl_axiom_get_annot(CowlAnyAxiom *axiom) {
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
 * @public @memberof CowlAxiom
 */
COWL_INLINE
CowlString *cowl_axiom_to_string(CowlAnyAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAxiom
 */
COWL_INLINE
bool cowl_axiom_equals(CowlAnyAxiom *lhs, CowlAnyAxiom *rhs) {
    return cowl_equals(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlAxiom
 */
COWL_INLINE
ulib_uint cowl_axiom_hash(CowlAnyAxiom *axiom) {
    return cowl_hash(axiom);
}

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAxiom
 */
COWL_INLINE
bool cowl_axiom_iterate_primitives(CowlAnyAxiom *axiom, CowlPrimitiveFlags flags,
                                   CowlIterator *iter) {
    return cowl_iterate_primitives(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_AXIOM_H
