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
#include "cowl_object.h"

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
COWL_INLINE
CowlClsExp* cowl_cls_exp_retain(CowlClsExp *exp) {
    return (CowlClsExp *)cowl_retain(exp);
}

/**
 * Releases the specified class expression.
 *
 * @param exp The class expression.
 *
 * @public @memberof CowlClsExp
 */
COWL_INLINE
void cowl_cls_exp_release(CowlClsExp *exp) {
    cowl_release(exp);
}

/**
 * Gets the type of the specified class expression.
 *
 * @param exp The class expression.
 * @return The type.
 *
 * @public @memberof CowlClsExp
 */
COWL_INLINE
CowlClsExpType cowl_cls_exp_get_type(CowlClsExp *exp) {
    return (CowlClsExpType)(cowl_get_type(exp) - COWL_OT_CE_CLASS);
}

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
COWL_INLINE
CowlString* cowl_cls_exp_to_string(CowlClsExp *exp) {
    return cowl_to_string(exp);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlClsExp
 */
COWL_INLINE
bool cowl_cls_exp_equals(CowlClsExp *lhs, CowlClsExp *rhs) {
    return cowl_equals(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param exp The class expression.
 * @return The hash value.
 *
 * @public @memberof CowlClsExp
 */
COWL_INLINE
ulib_uint cowl_cls_exp_hash(CowlClsExp *exp) {
    return cowl_hash(exp);
}

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
COWL_INLINE
bool cowl_cls_exp_iterate_primitives(CowlClsExp *exp, CowlPrimitiveFlags flags,
                                     CowlIterator *iter) {
    return cowl_iterate_primitives(exp, flags, iter);
}

COWL_END_DECLS

#endif // COWL_CLS_EXP_H
