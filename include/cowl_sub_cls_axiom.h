/**
 * Declares CowlSubClsAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_CLS_AXIOM_H
#define COWL_SUB_CLS_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);
cowl_struct_decl(CowlSubClsAxiom);
/// @endcond

/**
 * Represents a [SubClassOf] axiom in the OWL 2 specification.
 *
 * [SubClassOf]: https://www.w3.org/TR/owl2-syntax/#Subclass_Axioms
 *
 * @struct CowlSubClsAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained subclass axiom.
 *
 * @param sub The subclass.
 * @param super The superclass.
 * @param annot The annotations.
 * @return Retained axiom.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
CowlSubClsAxiom* cowl_sub_cls_axiom_get(CowlClsExp *sub, CowlClsExp *super,
                                        CowlAnnotationVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
CowlSubClsAxiom* cowl_sub_cls_axiom_retain(CowlSubClsAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
void cowl_sub_cls_axiom_release(CowlSubClsAxiom *axiom);

/**
 * Gets the superclass.
 *
 * @param axiom The axiom.
 * @return The superclass.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
CowlClsExp* cowl_sub_cls_axiom_get_super(CowlSubClsAxiom *axiom);

/**
 * Gets the subclass.
 *
 * @param axiom The axiom.
 * @return The subclass.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
CowlClsExp* cowl_sub_cls_axiom_get_sub(CowlSubClsAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
CowlAnnotationVec* cowl_sub_cls_axiom_get_annot(CowlSubClsAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
CowlString* cowl_sub_cls_axiom_to_string(CowlSubClsAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
bool cowl_sub_cls_axiom_equals(CowlSubClsAxiom *lhs, CowlSubClsAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
cowl_uint_t cowl_sub_cls_axiom_hash(CowlSubClsAxiom *axiom);

/**
 * Iterates over the signature of the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
bool cowl_sub_cls_axiom_iterate_signature(CowlSubClsAxiom *axiom, CowlEntityIterator *iter);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter The primitive iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
bool cowl_sub_cls_axiom_iterate_primitives(CowlSubClsAxiom *axiom, CowlPrimitiveIterator *iter);

COWL_END_DECLS

#endif // COWL_SUB_CLS_AXIOM_H
