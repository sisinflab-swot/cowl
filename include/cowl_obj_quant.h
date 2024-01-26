/**
 * Declares CowlObjQuant and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_QUANT_H
#define COWL_OBJ_QUANT_H

#include "cowl_object.h"
#include "cowl_quant_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlString);
/// @endcond

/**
 * Represents [ObjectSomeValuesFrom] and [ObjectAllValuesFrom] in the OWL 2 specification.
 *
 * [ObjectSomeValuesFrom]: https://www.w3.org/TR/owl2-syntax/#Existential_Quantification
 * [ObjectAllValuesFrom]: https://www.w3.org/TR/owl2-syntax/#Universal_Quantification
 *
 * @superstruct{CowlClsExp}
 * @struct CowlObjQuant
 */
cowl_struct_decl(CowlObjQuant);

/**
 * @defgroup CowlObjQuant CowlObjQuant API
 * @{
 */

/**
 * Returns an object quantifier.
 *
 * @param type Object quantifier type.
 * @param prop The object property.
 * @param filler Filler of the quantifier.
 * @return Object quantifier, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlObjQuant *cowl_obj_quant(CowlQuantType type, CowlAnyObjPropExp *prop, CowlAnyClsExp *filler);

/**
 * Gets the type of the specified object quantifier.
 *
 * @param restr The object quantifier.
 * @return The type of the object quantifier.
 */
COWL_PURE
COWL_INLINE
CowlQuantType cowl_obj_quant_get_type(CowlObjQuant *restr) {
    return (CowlQuantType)(cowl_get_type(restr) - COWL_OT_CE_OBJ_SOME);
}

/**
 * Gets the object property.
 *
 * @param restr The object quantifier.
 * @return The object property.
 */
COWL_PURE
COWL_INLINE
CowlObjPropExp *cowl_obj_quant_get_prop(CowlObjQuant *restr) {
    return (CowlObjPropExp *)cowl_get_field(restr, 0);
}

/**
 * Gets the filler of the specified object quantifier.
 *
 * @param restr The object quantifier.
 * @return Range of the object quantifier.
 */
COWL_API
COWL_PURE
CowlClsExp *cowl_obj_quant_get_filler(CowlObjQuant *restr);

/// @}

COWL_END_DECLS

#endif // COWL_OBJ_QUANT_H
