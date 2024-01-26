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
/// @endcond

/**
 * Represents [ObjectMinCardinality], [ObjectMaxCardinality] and [ObjectExactCardinality]
 * in the OWL 2 specification.
 *
 * [ObjectMinCardinality]: https://www.w3.org/TR/owl2-syntax/#Minimum_Cardinality
 * [ObjectMaxCardinality]: https://www.w3.org/TR/owl2-syntax/#Maximum_Cardinality
 * [ObjectExactCardinality]: https://www.w3.org/TR/owl2-syntax/#Exact_Cardinality
 *
 * @superstruct{CowlClsExp}
 * @struct CowlObjCard
 */
cowl_struct_decl(CowlObjCard);

/**
 * @defgroup CowlObjCard CowlObjCard API
 * @{
 */

/**
 * Returns an object property cardinality restriction.
 *
 * @param type The type.
 * @param prop The object property.
 * @param filler @type{optional} Filler of the restriction.
 * @param cardinality Cardinality of the restriction.
 * @return Restriction, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlObjCard *cowl_obj_card(CowlCardType type, CowlAnyObjPropExp *prop, CowlAnyClsExp *filler,
                           ulib_uint cardinality);

/**
 * Gets the type of the specified object property cardinality restriction.
 *
 * @param restr The restriction.
 * @return The type.
 */
COWL_PURE
COWL_INLINE
CowlCardType cowl_obj_card_get_type(CowlObjCard *restr) {
    return (CowlCardType)(cowl_get_type(restr) - COWL_OT_CE_OBJ_MIN_CARD);
}

/**
 * Gets the property of the restriction.
 *
 * @param restr The restriction.
 * @return The property.
 */
COWL_PURE
COWL_INLINE
CowlObjPropExp *cowl_obj_card_get_prop(CowlObjCard *restr) {
    return (CowlObjPropExp *)cowl_get_field(restr, 0);
}

/**
 * Gets the filler of the restriction.
 *
 * @param restr The restriction.
 * @return The filler.
 */
COWL_API
COWL_PURE
CowlClsExp *cowl_obj_card_get_filler(CowlObjCard *restr);

/**
 * Gets the cardinality of the restriction.
 *
 * @param restr The restriction.
 * @return The cardinality.
 */
COWL_PURE
COWL_INLINE
ulib_uint cowl_obj_card_get_cardinality(CowlObjCard *restr) {
    return cowl_get_uint_field(restr);
}

/// @}

COWL_END_DECLS

#endif // COWL_OBJ_CARD_H
