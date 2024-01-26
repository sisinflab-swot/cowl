/**
 * Declares CowlClsExp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLS_EXP_H
#define COWL_CLS_EXP_H

#include "cowl_cls_exp_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/**
 * Represents a [ClassExpression] in the OWL 2 specification.
 *
 * [ClassExpression]: https://www.w3.org/TR/owl2-syntax/#Class_Expressions
 *
 * @superstruct{CowlObject}
 * @struct CowlClsExp
 */
cowl_struct_decl(CowlClsExp);

/**
 * @defgroup CowlClsExp CowlClsExp API
 * @{
 */

/**
 * Gets the type of the specified class expression.
 *
 * @param exp The class expression.
 * @return The type.
 */
COWL_PURE
COWL_INLINE
CowlClsExpType cowl_cls_exp_get_type(CowlAnyClsExp *exp) {
    return (CowlClsExpType)(cowl_get_type(exp) - COWL_OT_CE_CLASS);
}

/// @}

COWL_END_DECLS

#endif // COWL_CLS_EXP_H
