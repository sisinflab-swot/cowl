/**
 * Declares CowlObjHasValue and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_HAS_VALUE_H
#define COWL_OBJ_HAS_VALUE_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlObjPropExp);
/// @endcond

/**
 * Represents [ObjectHasValue] in the OWL 2 specification.
 *
 * [ObjectHasValue]: https://www.w3.org/TR/owl2-syntax/#Individual_Value_Restriction
 *
 * @superstruct{CowlClsExp}
 * @struct CowlObjHasValue
 */
cowl_struct_decl(CowlObjHasValue);

/**
 * @defgroup CowlObjHasValue CowlObjHasValue
 * @{
 */

/**
 * Returns an individual value restriction.
 *
 * @param prop The object property expression.
 * @param individual The individual.
 * @return Restriction, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlObjHasValue *cowl_obj_has_value(CowlAnyObjPropExp *prop, CowlAnyIndividual *individual) {
    return (CowlObjHasValue *)cowl_get_impl_2(COWL_OT_CE_OBJ_HAS_VALUE, prop, individual);
}

/**
 * Gets the object property expression of the specified individual value restriction.
 *
 * @param exp The restriction.
 * @return The object property expression.
 */
COWL_PURE
COWL_INLINE
CowlObjPropExp *cowl_obj_has_value_get_prop(CowlObjHasValue *exp) {
    return (CowlObjPropExp *)cowl_get_field(exp, 0);
}

/**
 * Gets the individual of the specified individual value restriction.
 *
 * @param exp The restriction.
 * @return The individual.
 */
COWL_PURE
COWL_INLINE
CowlIndividual *cowl_obj_has_value_get_ind(CowlObjHasValue *exp) {
    return (CowlIndividual *)cowl_get_field(exp, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_OBJ_HAS_VALUE_H
