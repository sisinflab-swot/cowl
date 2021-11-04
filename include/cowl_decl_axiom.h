/**
 * Declares CowlDeclAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DECL_AXIOM_H
#define COWL_DECL_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlEntity);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlDeclAxiom);
/// @endcond

/**
 * Represents a [Declaration] in the OWL 2 specification.
 *
 * [Declaration]: https://www.w3.org/TR/owl2-syntax/#Entity_Declarations_and_Typing
 *
 * @struct CowlDeclAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained declaration axiom.
 *
 * @param entity The declared entity.
 * @param annot [optional] The annotations.
 * @return Retained declaration.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_PUBLIC
CowlDeclAxiom* cowl_decl_axiom_get(CowlEntity *entity, CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_PUBLIC
CowlDeclAxiom* cowl_decl_axiom_retain(CowlDeclAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_PUBLIC
void cowl_decl_axiom_release(CowlDeclAxiom *axiom);

/**
 * Gets the declared entity.
 *
 * @param axiom The axiom.
 * @return The entity.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_PUBLIC
CowlEntity* cowl_decl_axiom_get_entity(CowlDeclAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_decl_axiom_get_annot(CowlDeclAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_PUBLIC
CowlString* cowl_decl_axiom_to_string(CowlDeclAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_PUBLIC
bool cowl_decl_axiom_equals(CowlDeclAxiom *lhs, CowlDeclAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_PUBLIC
ulib_uint cowl_decl_axiom_hash(CowlDeclAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_PUBLIC
bool cowl_decl_axiom_iterate_primitives(CowlDeclAxiom *axiom, CowlPrimitiveFlags flags,
                                        CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_DECL_AXIOM_H
