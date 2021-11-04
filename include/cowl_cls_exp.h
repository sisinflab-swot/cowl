/**
 * Declares CowlClsExp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLS_EXP_H
#define COWL_CLS_EXP_H

#include "cowl_cls_exp_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
/// @endcond

/**
 * Represents a [ClassExpression] in the OWL 2 specification.
 *
 * [ClassExpression]: https://www.w3.org/TR/owl2-syntax/#Class_Expressions
 *
 * @struct CowlClsExp
 */

/**
 * Retains the specified class expression.
 *
 * @param exp The class expression.
 * @return Retained class expression.
 *
 * @public @memberof CowlClsExp
 */
COWL_PUBLIC
CowlClsExp* cowl_cls_exp_retain(CowlClsExp *exp);

/**
 * Releases the specified class expression.
 *
 * @param exp The class expression.
 *
 * @public @memberof CowlClsExp
 */
COWL_PUBLIC
void cowl_cls_exp_release(CowlClsExp *exp);

/**
 * Gets the type of the specified class expression.
 *
 * @param exp The class expression.
 * @return The type.
 *
 * @public @memberof CowlClsExp
 */
COWL_PUBLIC
CowlClsExpType cowl_cls_exp_get_type(CowlClsExp *exp);

/**
 * Returns the string representation of the specified class expression.
 *
 * @param exp The class expression.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlClsExp
 */
COWL_PUBLIC
CowlString* cowl_cls_exp_to_string(CowlClsExp *exp);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlClsExp
 */
COWL_PUBLIC
bool cowl_cls_exp_equals(CowlClsExp *lhs, CowlClsExp *rhs);

/**
 * Hash function.
 *
 * @param exp The class expression.
 * @return The hash value.
 *
 * @public @memberof CowlClsExp
 */
COWL_PUBLIC
ulib_uint cowl_cls_exp_hash(CowlClsExp *exp);

/**
 * Iterates over the primitives referenced by the specified class expression.
 *
 * @param exp The class expression.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlClsExp
 */
COWL_PUBLIC
bool cowl_cls_exp_iterate_primitives(CowlClsExp *exp, CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_CLS_EXP_H
