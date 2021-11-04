/**
 * Declares CowlNAryBool and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_BOOL_H
#define COWL_NARY_BOOL_H

#include "cowl_iterator.h"
#include "cowl_nary_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_hash_decl(CowlObjectTable);
cowl_struct_decl(CowlString);
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
COWL_PUBLIC
CowlNAryBool* cowl_nary_bool_get(CowlNAryType type, CowlObjectTable *operands);

/**
 * Retains the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 * @return Retained expression.
 *
 * @public @memberof CowlNAryBool
 */
COWL_PUBLIC
CowlNAryBool* cowl_nary_bool_retain(CowlNAryBool *exp);

/**
 * Releases the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 *
 * @public @memberof CowlNAryBool
 */
COWL_PUBLIC
void cowl_nary_bool_release(CowlNAryBool *exp);

/**
 * Gets the type of the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 * @return The type.
 *
 * @public @memberof CowlNAryBool
 */
COWL_PUBLIC
CowlNAryType cowl_nary_bool_get_type(CowlNAryBool *exp);

/**
 * Gets the operands of the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 * @return The operands.
 *
 * @public @memberof CowlNAryBool
 */
COWL_PUBLIC
CowlObjectTable* cowl_nary_bool_get_operands(CowlNAryBool *exp);

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
COWL_PUBLIC
CowlString* cowl_nary_bool_to_string(CowlNAryBool *exp);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNAryBool
 */
COWL_PUBLIC
bool cowl_nary_bool_equals(CowlNAryBool *lhs, CowlNAryBool *rhs);

/**
 * Hash function.
 *
 * @param exp The expression.
 * @return The hash value.
 *
 * @public @memberof CowlNAryBool
 */
COWL_PUBLIC
ulib_uint cowl_nary_bool_hash(CowlNAryBool *exp);

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
COWL_PUBLIC
bool cowl_nary_bool_iterate_primitives(CowlNAryBool *exp, CowlPrimitiveFlags flags,
                                       CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_NARY_BOOL_H
