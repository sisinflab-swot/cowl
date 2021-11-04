/**
 * Declares CowlObjPropCharAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_CHAR_AXIOM_H
#define COWL_OBJ_PROP_CHAR_AXIOM_H

#include "cowl_char_axiom_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlObjPropCharAxiom);
/// @endcond

/**
 * Represents a [FunctionalObjectProperty], [InverseFunctionalObjectProperty],
 * [SymmetricObjectProperty], [AsymmetricObjectProperty], [TransitiveObjectProperty],
 * [ReflexiveObjectProperty] or [IrreflexiveObjectProperty] axiom in the OWL 2 specification.
 *
 * [FunctionalObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Functional_Object_Properties
 *
 * [InverseFunctionalObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Inverse-Functional_Object_Properties
 *
 * [SymmetricObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Symmetric_Object_Properties
 *
 * [AsymmetricObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Asymmetric_Object_Properties
 *
 * [TransitiveObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Transitive_Object_Properties
 *
 * [ReflexiveObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Reflexive_Object_Properties
 *
 * [IrreflexiveObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Irreflexive_Object_Properties
 *
 * @struct CowlObjPropCharAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained object property characteristic axiom.
 *
 * @param type The type.
 * @param prop The object property expression.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PUBLIC
CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_get(CowlCharAxiomType type,
                                                   CowlObjPropExp *prop,
                                                   CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PUBLIC
CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_retain(CowlObjPropCharAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PUBLIC
void cowl_obj_prop_char_axiom_release(CowlObjPropCharAxiom *axiom);

/**
 * Gets the type of the specified object property characteristic axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PUBLIC
CowlCharAxiomType cowl_obj_prop_char_axiom_get_type(CowlObjPropCharAxiom *axiom);

/**
 * Gets the object property expression of the specified characteristic axiom.
 *
 * @param axiom The axiom.
 * @return The object property expression.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PUBLIC
CowlObjPropExp* cowl_obj_prop_char_axiom_get_prop(CowlObjPropCharAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_obj_prop_char_axiom_get_annot(CowlObjPropCharAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PUBLIC
CowlString* cowl_obj_prop_char_axiom_to_string(CowlObjPropCharAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PUBLIC
bool cowl_obj_prop_char_axiom_equals(CowlObjPropCharAxiom *lhs, CowlObjPropCharAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PUBLIC
ulib_uint cowl_obj_prop_char_axiom_hash(CowlObjPropCharAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PUBLIC
bool cowl_obj_prop_char_axiom_iterate_primitives(CowlObjPropCharAxiom *axiom,
                                                 CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_CHAR_AXIOM_H
