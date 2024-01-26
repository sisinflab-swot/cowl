/**
 * Declares CowlObjPropExp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_EXP_H
#define COWL_OBJ_PROP_EXP_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjProp);
/// @endcond

/**
 * Represents an [ObjectPropertyExpression] in the OWL 2 specification.
 *
 * [ObjectPropertyExpression]: https://www.w3.org/TR/owl2-syntax/#Object_Property_Expressions
 *
 * @superstruct{CowlObject}
 * @struct CowlObjPropExp
 */
cowl_struct_decl(CowlObjPropExp);

/**
 * @defgroup CowlObjPropExp CowlObjPropExp API
 * @{
 */

/**
 * Returns true if the object property expression is inverse.
 *
 * @param exp The object property expression.
 * @return True if the expression is inverse, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_obj_prop_exp_is_inverse(CowlAnyObjPropExp *exp) {
    return cowl_get_type(exp) == COWL_OT_OPE_INV_OBJ_PROP;
}

/**
 * Gets the underlying object property.
 *
 * @param exp The object property expression.
 * @return The object property.
 */
COWL_API
COWL_PURE
CowlObjProp *cowl_obj_prop_exp_get_prop(CowlAnyObjPropExp *exp);

/// @}

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_H
