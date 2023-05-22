/**
 * Declares CowlObjCard and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_CARD_H
#define COWL_OBJ_CARD_H

#include "cowl_card_type.h"
#include "cowl_object.h"

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
CowlObjCard *cowl_obj_card(CowlCardType type, CowlAnyObjPropExp *prop, CowlAnyClsExp *filler,
                           ulib_uint cardinality);

/**
 * Gets the type of the specified object property cardinality restriction.
 *
 * @param restr The restriction.
 * @return The type.
 *
 * @public @memberof CowlObjCard
 */
COWL_INLINE
CowlCardType cowl_obj_card_get_type(CowlObjCard *restr) {
    return (CowlCardType)(cowl_get_type(restr) - COWL_OT_CE_OBJ_MIN_CARD);
}

/**
 * Gets the property of the restriction.
 *
 * @param restr The restriction.
 * @return The property.
 *
 * @public @memberof CowlObjCard
 */
COWL_INLINE
CowlObjPropExp *cowl_obj_card_get_prop(CowlObjCard *restr) {
    return (CowlObjPropExp *)cowl_get_field(restr, 0);
}

/**
 * Gets the filler of the restriction.
 *
 * @param restr The restriction.
 * @return The filler.
 *
 * @public @memberof CowlObjCard
 */
COWL_PUBLIC
CowlClsExp *cowl_obj_card_get_filler(CowlObjCard *restr);

/**
 * Gets the cardinality of the restriction.
 *
 * @param restr The restriction.
 * @return The cardinality.
 *
 * @public @memberof CowlObjCard
 */
COWL_INLINE
ulib_uint cowl_obj_card_get_cardinality(CowlObjCard *restr) {
    return cowl_get_uint_field(restr);
}

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
COWL_INLINE
CowlString *cowl_obj_card_to_string(CowlObjCard *restr) {
    return cowl_to_string(restr);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjCard
 */
COWL_INLINE
bool cowl_obj_card_equals(CowlObjCard *lhs, CowlObjCard *rhs) {
    return cowl_uint_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param restr The restriction.
 * @return The hash value.
 *
 * @public @memberof CowlObjCard
 */
COWL_INLINE
ulib_uint cowl_obj_card_hash(CowlObjCard *restr) {
    return cowl_uint_hash_impl(restr);
}

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
COWL_INLINE
bool cowl_obj_card_iterate_primitives(CowlObjCard *restr, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    return cowl_iterate_primitives_impl(restr, flags, iter);
}

COWL_END_DECLS

#endif // COWL_OBJ_CARD_H
