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

COWL_END_DECLS

#endif // COWL_OBJ_CARD_H
