/**
 * Defines CowlAnnotValue and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_VALUE_H
#define COWL_ANNOT_VALUE_H

#include "cowl_annot_value_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotValue);
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlString);
/// @endcond

/**
 * Represents annotation values, which can be either anonymous individuals, IRIs, or literals.
 *
 * @see CowlAnnotation
 *
 * @struct CowlAnnotValue
 */

/**
 * Retains the annotation value.
 *
 * @param value The annotation value.
 * @return Retained annotation value.
 *
 * @public @memberof CowlAnnotValue
 */
COWL_PUBLIC
CowlAnnotValue* cowl_annot_value_retain(CowlAnnotValue *value);

/**
 * Releases the annotation value.
 *
 * @param value The annotation value.
 *
 * @public @memberof CowlAnnotValue
 */
COWL_PUBLIC
void cowl_annot_value_release(CowlAnnotValue *value);

/**
 * Gets the type of the specified annotation value.
 *
 * @param value The annotation value.
 * @return The type.
 *
 * @public @memberof CowlAnnotValue
 */
COWL_PUBLIC
CowlAnnotValueType cowl_annot_value_get_type(CowlAnnotValue *value);

/**
 * Returns the string representation of the specified annotation value.
 *
 * @param value The annotation value.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlAnnotValue
 */
COWL_PUBLIC
CowlString* cowl_annot_value_to_string(CowlAnnotValue *value);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotValue
 */
COWL_PUBLIC
bool cowl_annot_value_equals(CowlAnnotValue *lhs, CowlAnnotValue *rhs);

/**
 * Hash function.
 *
 * @param value The annotation value.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotValue
 */
COWL_PUBLIC
ulib_uint cowl_annot_value_hash(CowlAnnotValue *value);

/**
 * Iterates over the primitives referenced by the specified annotation value.
 *
 * @param value The annotation value.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAnnotValue
 */
COWL_PUBLIC
bool cowl_annot_value_iterate_primitives(CowlAnnotValue *value, CowlPrimitiveFlags flags,
                                         CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_ANNOT_VALUE_H
