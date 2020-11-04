/**
 * Declares CowlAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_H
#define COWL_AXIOM_H

#include "cowl_axiom_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAxiom);
/// @endcond

/**
 * Represents an [Axiom] in the OWL 2 specification.
 *
 * [Axiom]: https://www.w3.org/TR/owl2-syntax/#Axioms
 *
 * @struct CowlAxiom
 */

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlAxiom
 */
COWL_PUBLIC
CowlAxiom* cowl_axiom_retain(CowlAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlAxiom
 */
COWL_PUBLIC
void cowl_axiom_release(CowlAxiom *axiom);

/**
 * Gets the type of the specified axiom.
 *
 * @param axiom The axiom.
 * @return Axiom type.
 *
 * @public @memberof CowlAxiom
 */
COWL_PUBLIC
CowlAxiomType cowl_axiom_get_type(CowlAxiom *axiom);

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
COWL_PUBLIC
CowlString* cowl_axiom_to_string(CowlAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAxiom
 */
COWL_PUBLIC
bool cowl_axiom_equals(CowlAxiom *lhs, CowlAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlAxiom
 */
COWL_PUBLIC
cowl_uint_t cowl_axiom_hash(CowlAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter The iterator.
 * @param flags Iteration flags.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAxiom
 */
COWL_PUBLIC
bool cowl_axiom_iterate_primitives(CowlAxiom *axiom, CowlIterator *iter, CowlPrimitiveFlags flags);

COWL_END_DECLS

#endif // COWL_AXIOM_H
