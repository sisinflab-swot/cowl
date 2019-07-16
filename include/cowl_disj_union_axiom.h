/**
 * Declares CowlDisjUnionAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DISJ_UNION_AXIOM_H
#define COWL_DISJ_UNION_AXIOM_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

/// @cond
cowl_hash_decl(CowlClsExpSet);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);
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
 * @param annot The annotations.
 * @return Retained disjoint union axiom.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_PUBLIC
CowlDisjUnionAxiom* cowl_disj_union_axiom_get(CowlClass *cls, CowlClsExpSet *disjoints,
                                              CowlAnnotationVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_PUBLIC
CowlDisjUnionAxiom* cowl_disj_union_axiom_retain(CowlDisjUnionAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_PUBLIC
void cowl_disj_union_axiom_release(CowlDisjUnionAxiom *axiom);

/**
 * Gets the class which is equivalent to the disjoint union.
 *
 * @param axiom The axiom.
 * @return The class.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_PUBLIC
CowlClass* cowl_disj_union_axiom_get_class(CowlDisjUnionAxiom *axiom);

/**
 * Gets the class expressions which are operands of the disjoint union.
 * @param axiom The axiom.
 * @return The class expressions.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_PUBLIC
CowlClsExpSet* cowl_disj_union_axiom_get_disjoints(CowlDisjUnionAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_PUBLIC
CowlAnnotationVec* cowl_disj_union_axiom_get_annot(CowlDisjUnionAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_PUBLIC
CowlString* cowl_disj_union_axiom_to_string(CowlDisjUnionAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_PUBLIC
bool cowl_disj_union_axiom_equals(CowlDisjUnionAxiom *lhs, CowlDisjUnionAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_PUBLIC
cowl_uint_t cowl_disj_union_axiom_hash(CowlDisjUnionAxiom *axiom);

/**
 * Iterates over the signature of the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDisjUnionAxiom
 */
COWL_PUBLIC
bool cowl_disj_union_axiom_iterate_signature(CowlDisjUnionAxiom *axiom, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_DISJ_UNION_AXIOM_H
