/**
 * Declares CowlObjCard and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_CARD_H
#define COWL_OBJ_CARD_H

#include "cowl_std.h"
#include "cowl_card_type.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlObjCard);
/// @endcond

/**
 * Represents [ObjectMinCardinality], [ObjectMaxCardinality] and [ObjectExactCardinality]
 * in the OWL 2 specification.
 *
 * [ObjectMinCardinality]: https://www.w3.org/TR/owl2-syntax/#Minimum_Cardinality
 * [ObjectMaxCardinality]: https://www.w3.org/TR/owl2-syntax/#Maximum_Cardinality
 * [ObjectExactCardinality]: https://www.w3.org/TR/owl2-syntax/#Exact_Cardinality
 *
 * @struct CowlObjCard
 * @extends CowlClsExp
 */

/**
 * Returns a retained object property cardinality restriction.
 *
 * @param type The type.
 * @param prop The object property.
 * @param filler [optional] Filler of the restriction.
 * @param cardinality Cardinality of the restriction.
 * @return Retained restriction, or NULL on error.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
CowlObjCard* cowl_obj_card_get(CowlCardType type, CowlObjPropExp *prop,
                               CowlClsExp *filler, ulib_uint cardinality);

/**
 * Retains the specified object property cardinality restriction.
 *
 * @param restr The restriction.
 * @return Retained restriction.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
CowlObjCard* cowl_obj_card_retain(CowlObjCard *restr);

/**
 * Releases the specified object property cardinality restriction.
 *
 * @param restr The restriction.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
void cowl_obj_card_release(CowlObjCard *restr);

/**
 * Gets the type of the specified object property cardinality restriction.
 *
 * @param restr The restriction.
 * @return The type.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
CowlCardType cowl_obj_card_get_type(CowlObjCard *restr);

/**
 * Gets the property of the restriction.
 *
 * @param restr The restriction.
 * @return The property.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
CowlObjPropExp* cowl_obj_card_get_prop(CowlObjCard *restr);

/**
 * Gets the filler of the restriction.
 *
 * @param restr The restriction.
 * @return The filler.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
CowlClsExp* cowl_obj_card_get_filler(CowlObjCard *restr);

/**
 * Gets the cardinality of the restriction.
 *
 * @param restr The restriction.
 * @return The cardinality.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
ulib_uint cowl_obj_card_get_cardinality(CowlObjCard *restr);

/**
 * Returns the string representation of the specified restriction.
 *
 * @param restr The restriction.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
CowlString* cowl_obj_card_to_string(CowlObjCard *restr);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
bool cowl_obj_card_equals(CowlObjCard *lhs, CowlObjCard *rhs);

/**
 * Hash function.
 *
 * @param restr The restriction.
 * @return The hash value.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
ulib_uint cowl_obj_card_hash(CowlObjCard *restr);

/**
 * Iterates over the primitives referenced by
 * the specified object property cardinality restriction.
 *
 * @param restr The restriction.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
bool cowl_obj_card_iterate_primitives(CowlObjCard *restr, CowlPrimitiveFlags flags,
                                      CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_CARD_H
