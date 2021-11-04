/**
 * Declares CowlObjOneOf and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_ONE_OF_H
#define COWL_OBJ_ONE_OF_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

/// @cond
cowl_hash_decl(CowlObjectTable);
cowl_struct_decl(CowlObjOneOf);
/// @endcond

/**
 * Represents [ObjectOneOf] in the OWL 2 specification.
 *
 * [ObjectOneOf]: https://www.w3.org/TR/owl2-syntax/#Enumeration_of_Individuals
 *
 * @struct CowlObjOneOf
 * @extends CowlClsExp
 */

/**
 * Returns a retained individual enumeration.
 *
 * @param inds The individuals.
 * @return Retained individual enumeration, or NULL on error.
 *
 * @public @memberof CowlObjOneOf
 */
COWL_PUBLIC
CowlObjOneOf* cowl_obj_one_of_get(CowlObjectTable *inds);

/**
 * Retains the specified individual enumeration.
 *
 * @param exp The individual enumeration.
 * @return Retained individual enumeration.
 *
 * @public @memberof CowlObjOneOf
 */
COWL_PUBLIC
CowlObjOneOf* cowl_obj_one_of_retain(CowlObjOneOf *exp);

/**
 * Releases the specified individual enumeration.
 *
 * @param exp The individual enumeration.
 *
 * @public @memberof CowlObjOneOf
 */
COWL_PUBLIC
void cowl_obj_one_of_release(CowlObjOneOf *exp);

/**
 * Gets the individuals of the specified enumeration.
 *
 * @param exp The individual enumeration.
 * @return The individuals.
 *
 * @public @memberof CowlObjOneOf
 */
COWL_PUBLIC
CowlObjectTable* cowl_obj_one_of_get_inds(CowlObjOneOf *exp);

/**
 * Returns the string representation of the specified individual enumeration.
 *
 * @param exp The individual enumeration.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjOneOf
 */
COWL_PUBLIC
CowlString* cowl_obj_one_of_to_string(CowlObjOneOf *exp);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjOneOf
 */
COWL_PUBLIC
bool cowl_obj_one_of_equals(CowlObjOneOf *lhs, CowlObjOneOf *rhs);

/**
 * Hash function.
 *
 * @param exp The individual enumeration.
 * @return The hash value.
 *
 * @public @memberof CowlObjOneOf
 */
COWL_PUBLIC
ulib_uint cowl_obj_one_of_hash(CowlObjOneOf *exp);

/**
 * Iterates over the primitives referenced by the specified individual enumeration.
 *
 * @param exp The individual enumeration.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjOneOf
 */
COWL_PUBLIC
bool cowl_obj_one_of_iterate_primitives(CowlObjOneOf *exp, CowlPrimitiveFlags flags,
                                        CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_ONE_OF_H
