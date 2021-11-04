/**
 * Declares CowlSubClsAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
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
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
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
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
CowlSubClsAxiom* cowl_sub_cls_axiom_get(CowlClsExp *sub, CowlClsExp *super,
                                        CowlObjectVec *annot);

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
CowlObjectVec* cowl_sub_cls_axiom_get_annot(CowlSubClsAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
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
ulib_uint cowl_sub_cls_axiom_hash(CowlSubClsAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_PUBLIC
bool cowl_sub_cls_axiom_iterate_primitives(CowlSubClsAxiom *axiom, CowlPrimitiveFlags flags,
                                           CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_SUB_CLS_AXIOM_H
