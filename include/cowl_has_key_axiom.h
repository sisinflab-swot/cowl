/**
 * Declares CowlHasKeyAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_HAS_KEY_AXIOM_H
#define COWL_HAS_KEY_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_hash_decl(CowlObjectTable);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlHasKeyAxiom);
/// @endcond

/**
 * Represents a [HasKey] axiom in the OWL 2 specification.
 *
 * [HasKey]: https://www.w3.org/TR/owl2-syntax/#Keys
 *
 * @struct CowlHasKeyAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained 'has key' axiom.
 *
 * @param cls_exp The class expression, instances of which this axiom acts as the key for.
 * @param obj_props Object property expressions that make up the key.
 * @param data_props Data property expressions that make up the key.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_PUBLIC
CowlHasKeyAxiom* cowl_has_key_axiom_get(CowlClsExp *cls_exp, CowlObjectTable *obj_props,
                                        CowlObjectTable *data_props, CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_PUBLIC
CowlHasKeyAxiom* cowl_has_key_axiom_retain(CowlHasKeyAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_PUBLIC
void cowl_has_key_axiom_release(CowlHasKeyAxiom *axiom);

/**
 * Gets the class expression, instances of which this axiom acts as the key for.
 *
 * @param axiom The axiom.
 * @return The class expression.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_PUBLIC
CowlClsExp* cowl_has_key_axiom_get_cls_exp(CowlHasKeyAxiom *axiom);

/**
 * Gets the set of object property expressions that make up the key.
 *
 * @param axiom The axiom.
 * @return The object property expressions.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_PUBLIC
CowlObjectTable* cowl_has_key_axiom_get_obj_props(CowlHasKeyAxiom *axiom);

/**
 * Gets the set of data property expressions that make up the key.
 *
 * @param axiom The axiom.
 * @return The data property expressions.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_PUBLIC
CowlObjectTable* cowl_has_key_axiom_get_data_props(CowlHasKeyAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_has_key_axiom_get_annot(CowlHasKeyAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_PUBLIC
CowlString* cowl_has_key_axiom_to_string(CowlHasKeyAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_PUBLIC
bool cowl_has_key_axiom_equals(CowlHasKeyAxiom *lhs, CowlHasKeyAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_PUBLIC
ulib_uint cowl_has_key_axiom_hash(CowlHasKeyAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_PUBLIC
bool cowl_has_key_axiom_iterate_primitives(CowlHasKeyAxiom *axiom, CowlPrimitiveFlags flags,
                                           CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_HAS_KEY_AXIOM_H
