/**
 * Declares CowlObjPropRangeAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_RANGE_AXIOM_H
#define COWL_OBJ_PROP_RANGE_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlObjPropExp);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlObjPropRangeAxiom);
/// @endcond

/**
 * Represents an [ObjectPropertyRange] axiom in the OWL 2 specification.
 *
 * [ObjectPropertyRange]: https://www.w3.org/TR/owl2-syntax/#Object_Property_Range
 *
 * @struct CowlObjPropRangeAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained object property range axiom.
 *
 * @param prop The object property.
 * @param range Range of the object property.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlObjPropRangeAxiom
 */
COWL_PUBLIC
CowlObjPropRangeAxiom* cowl_obj_prop_range_axiom_get(CowlObjPropExp *prop, CowlClsExp *range,
                                                     CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlObjPropRangeAxiom
 */
COWL_PUBLIC
CowlObjPropRangeAxiom* cowl_obj_prop_range_axiom_retain(CowlObjPropRangeAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlObjPropRangeAxiom
 */
COWL_PUBLIC
void cowl_obj_prop_range_axiom_release(CowlObjPropRangeAxiom *axiom);

/**
 * Gets the object property.
 *
 * @param axiom The axiom.
 * @return The object property.
 *
 * @public @memberof CowlObjPropRangeAxiom
 */
COWL_PUBLIC
CowlObjPropExp* cowl_obj_prop_range_axiom_get_prop(CowlObjPropRangeAxiom *axiom);

/**
 * Gets the range of the object property.
 *
 * @param axiom The axiom.
 * @return Range of the object property.
 *
 * @public @memberof CowlObjPropRangeAxiom
 */
COWL_PUBLIC
CowlClsExp* cowl_obj_prop_range_axiom_get_range(CowlObjPropRangeAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlObjPropRangeAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_obj_prop_range_axiom_get_annot(CowlObjPropRangeAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjPropRangeAxiom
 */
COWL_PUBLIC
CowlString* cowl_obj_prop_range_axiom_to_string(CowlObjPropRangeAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjPropRangeAxiom
 */
COWL_PUBLIC
bool cowl_obj_prop_range_axiom_equals(CowlObjPropRangeAxiom *lhs, CowlObjPropRangeAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlObjPropRangeAxiom
 */
COWL_PUBLIC
ulib_uint cowl_obj_prop_range_axiom_hash(CowlObjPropRangeAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjPropRangeAxiom
 */
COWL_PUBLIC
bool cowl_obj_prop_range_axiom_iterate_primitives(CowlObjPropRangeAxiom *axiom,
                                                  CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_RANGE_AXIOM_H
