/**
 * Declares CowlNAryClsAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_CLS_AXIOM_H
#define COWL_NARY_CLS_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_hash_decl(CowlObjectTable);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlNAryClsAxiom);
/// @endcond

/**
 * Represents an [EquivalentClasses] or [DisjointClasses] axiom in the OWL 2 specification.
 *
 * [EquivalentClasses]: https://www.w3.org/TR/owl2-syntax/#Equivalent_Classes
 * [DisjointClasses]: https://www.w3.org/TR/owl2-syntax/#Disjoint_Classes
 *
 * @struct CowlNAryClsAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained N-ary class expression axiom.
 *
 * @param type N-ary class expression axiom type.
 * @param classes The classes.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlNAryClsAxiom
 */
COWL_PUBLIC
CowlNAryClsAxiom* cowl_nary_cls_axiom_get(CowlNAryAxiomType type, CowlObjectTable *classes,
                                          CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlNAryClsAxiom
 */
COWL_PUBLIC
CowlNAryClsAxiom* cowl_nary_cls_axiom_retain(CowlNAryClsAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlNAryClsAxiom
 */
COWL_PUBLIC
void cowl_nary_cls_axiom_release(CowlNAryClsAxiom *axiom);

/**
 * Gets the type of the specified N-ary class expression axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 *
 * @public @memberof CowlNAryClsAxiom
 */
COWL_PUBLIC
CowlNAryAxiomType cowl_nary_cls_axiom_get_type(CowlNAryClsAxiom *axiom);

/**
 * Gets the classes of the specified N-ary class expression axiom.
 *
 * @param axiom The axiom.
 * @return The classes.
 *
 * @public @memberof CowlNAryClsAxiom
 */
COWL_PUBLIC
CowlObjectTable* cowl_nary_cls_axiom_get_classes(CowlNAryClsAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlNAryClsAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_nary_cls_axiom_get_annot(CowlNAryClsAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlNAryClsAxiom
 */
COWL_PUBLIC
CowlString* cowl_nary_cls_axiom_to_string(CowlNAryClsAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNAryClsAxiom
 */
COWL_PUBLIC
bool cowl_nary_cls_axiom_equals(CowlNAryClsAxiom *lhs, CowlNAryClsAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlNAryClsAxiom
 */
COWL_PUBLIC
ulib_uint cowl_nary_cls_axiom_hash(CowlNAryClsAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlNAryClsAxiom
 */
COWL_PUBLIC
bool cowl_nary_cls_axiom_iterate_primitives(CowlNAryClsAxiom *axiom, CowlPrimitiveFlags flags,
                                            CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_NARY_CLS_AXIOM_H
