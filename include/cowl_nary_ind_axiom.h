/**
 * Declares CowlNAryIndAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_IND_AXIOM_H
#define COWL_NARY_IND_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_hash_decl(CowlIndividualSet);
cowl_struct_decl(CowlIndividual);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);
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
 * @param annot The annotations.
 * @return Retained axiom.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_PUBLIC
CowlNAryIndAxiom* cowl_nary_ind_axiom_get(CowlNAryAxiomType type, CowlIndividualSet *individuals,
                                          CowlAnnotationVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_PUBLIC
CowlNAryIndAxiom* cowl_nary_ind_axiom_retain(CowlNAryIndAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_PUBLIC
void cowl_nary_ind_axiom_release(CowlNAryIndAxiom *axiom);

/**
 * Gets the type of the specified N-ary individual axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_PUBLIC
CowlNAryAxiomType cowl_nary_ind_axiom_get_type(CowlNAryIndAxiom *axiom);

/**
 * Gets the individuals of the specified N-ary individual axiom.
 *
 * @param axiom The axiom.
 * @return The individuals.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_PUBLIC
CowlIndividualSet* cowl_nary_ind_axiom_get_individuals(CowlNAryIndAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_PUBLIC
CowlAnnotationVec* cowl_nary_ind_axiom_get_annot(CowlNAryIndAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_PUBLIC
CowlString* cowl_nary_ind_axiom_to_string(CowlNAryIndAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_PUBLIC
bool cowl_nary_ind_axiom_equals(CowlNAryIndAxiom *lhs, CowlNAryIndAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_PUBLIC
cowl_uint_t cowl_nary_ind_axiom_hash(CowlNAryIndAxiom *axiom);

/**
 * Iterates over the signature of the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_PUBLIC
bool cowl_nary_ind_axiom_iterate_signature(CowlNAryIndAxiom *axiom, CowlEntityIterator *iter);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter The primitive iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlNAryIndAxiom
 */
COWL_PUBLIC
bool cowl_nary_ind_axiom_iterate_primitives(CowlNAryIndAxiom *axiom, CowlPrimitiveIterator *iter);

COWL_END_DECLS

#endif // COWL_NARY_IND_AXIOM_H
