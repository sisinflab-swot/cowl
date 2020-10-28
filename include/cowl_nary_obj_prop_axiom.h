/**
 * Declares CowlNAryObjPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_OBJ_PROP_AXIOM_H
#define COWL_NARY_OBJ_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_hash_decl(CowlObjPropExpSet);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);
cowl_struct_decl(CowlNAryObjPropAxiom);
/// @endcond

/**
 * Represents an [EquivalentObjectProperties] or [DisjointObjectProperties] axiom
 * in the OWL 2 specification.
 *
 * [EquivalentObjectProperties]: https://www.w3.org/TR/owl2-syntax/#Equivalent_Object_Properties
 * [DisjointObjectProperties]: https://www.w3.org/TR/owl2-syntax/#Disjoint_Object_Properties
 *
 * @struct CowlNAryObjPropAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained N-ary object property axiom.
 *
 * @param type The type.
 * @param props The object properties.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_PUBLIC
CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_get(CowlNAryAxiomType type,
                                                   CowlObjPropExpSet *props,
                                                   CowlAnnotationVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_PUBLIC
CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_retain(CowlNAryObjPropAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_PUBLIC
void cowl_nary_obj_prop_axiom_release(CowlNAryObjPropAxiom *axiom);

/**
 * Gets the type of the specified N-ary object property axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_PUBLIC
CowlNAryAxiomType cowl_nary_obj_prop_axiom_get_type(CowlNAryObjPropAxiom *axiom);

/**
 * Gets the object properties of the specified N-ary object property axiom.
 *
 * @param axiom The axiom.
 * @return The object properties.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_PUBLIC
CowlObjPropExpSet* cowl_nary_obj_prop_axiom_get_props(CowlNAryObjPropAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_PUBLIC
CowlAnnotationVec* cowl_nary_obj_prop_axiom_get_annot(CowlNAryObjPropAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_PUBLIC
CowlString* cowl_nary_obj_prop_axiom_to_string(CowlNAryObjPropAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_PUBLIC
bool cowl_nary_obj_prop_axiom_equals(CowlNAryObjPropAxiom *lhs, CowlNAryObjPropAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_PUBLIC
cowl_uint_t cowl_nary_obj_prop_axiom_hash(CowlNAryObjPropAxiom *axiom);

/**
 * Iterates over the objects referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlNAryObjPropAxiom
 */
COWL_PUBLIC
bool cowl_nary_obj_prop_axiom_iterate(CowlNAryObjPropAxiom *axiom, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_NARY_OBJ_PROP_AXIOM_H
