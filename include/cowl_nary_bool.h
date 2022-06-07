/**
 * Declares CowlNAryBool and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_BOOL_H
#define COWL_NARY_BOOL_H

#include "cowl_object_impl.h"
#include "cowl_nary_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlNAryBool);
/// @endcond

/**
 * Represents [ObjectIntersectionOf] and [ObjectUnionOf] in the OWL 2 specification.
 *
 * [ObjectIntersectionOf]: https://www.w3.org/TR/owl2-syntax/#Intersection_of_Class_Expressions
 * [ObjectUnionOf]: https://www.w3.org/TR/owl2-syntax/#Union_of_Class_Expressions
 *
 * @struct CowlNAryBool
 * @extends CowlClsExp
 */

/**
 * Returns a retained N-ary boolean class expression.
 *
 * @param type N-ary class expression type.
 * @param operands The operands.
 * @return Retained expression, or NULL on error.
 *
 * @public @memberof CowlNAryBool
 */
COWL_INLINE
CowlNAryBool* cowl_nary_bool_get(CowlNAryType type, CowlVector *operands) {
    if (!cowl_enum_value_is_valid(NT, type)) return NULL;
    return cowl_get_impl_1(COWL_OT_CE_OBJ_INTERSECT + type, operands, NULL);
}

/**
 * Retains the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 * @return Retained expression.
 *
 * @public @memberof CowlNAryBool
 */
COWL_INLINE
CowlNAryBool* cowl_nary_bool_retain(CowlNAryBool *exp) { return cowl_retain(exp); }

/**
 * Releases the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 *
 * @public @memberof CowlNAryBool
 */
COWL_INLINE
void cowl_nary_bool_release(CowlNAryBool *exp) { cowl_release_impl(exp); }

/**
 * Gets the type of the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 * @return The type.
 *
 * @public @memberof CowlNAryBool
 */
COWL_INLINE
CowlNAryType cowl_nary_bool_get_type(CowlNAryBool *exp) {
    return (CowlNAryType)(cowl_get_type(exp) - COWL_OT_CE_OBJ_INTERSECT);
}

/**
 * Gets the operands of the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 * @return The operands.
 *
 * @public @memberof CowlNAryBool
 */
COWL_INLINE
CowlVector* cowl_nary_bool_get_operands(CowlNAryBool *exp) { return cowl_get_field(exp, 0); }

/**
 * Returns the string representation of the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlNAryBool
 */
COWL_INLINE
CowlString* cowl_nary_bool_to_string(CowlNAryBool *exp) {
    return cowl_to_string_impl(exp);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNAryBool
 */
COWL_INLINE
bool cowl_nary_bool_equals(CowlNAryBool *lhs, CowlNAryBool *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param exp The expression.
 * @return The hash value.
 *
 * @public @memberof CowlNAryBool
 */
COWL_INLINE
ulib_uint cowl_nary_bool_hash(CowlNAryBool *exp) {
    return cowl_hash_impl(exp);
}

/**
 * Iterates over the primitives referenced by
 * the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlNAryBool
 */
COWL_INLINE
bool cowl_nary_bool_iterate_primitives(CowlNAryBool *exp, CowlPrimitiveFlags flags,
                                       CowlIterator *iter) {
    return cowl_iterate_primitives_impl(exp, flags, iter);
}

COWL_END_DECLS

#endif // COWL_NARY_BOOL_H
