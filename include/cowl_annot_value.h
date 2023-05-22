/**
 * Defines CowlAnnotValue and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_VALUE_H
#define COWL_ANNOT_VALUE_H

#include "cowl_annot_value_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotValue);
/// @endcond

/**
 * Represents annotation values, which can be either anonymous individuals, IRIs, or literals.
 *
 * @see CowlAnnotation
 *
 * @struct CowlAnnotValue
 * @extends CowlObject
 */

/**
 * Gets the type of the specified annotation value.
 *
 * @param value The annotation value.
 * @return The type.
 *
 * @public @memberof CowlAnnotValue
 */
COWL_PUBLIC
CowlAnnotValueType cowl_annot_value_get_type(CowlAnyAnnotValue *value);

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
COWL_INLINE
CowlString *cowl_annot_value_to_string(CowlAnyAnnotValue *value) {
    return cowl_to_string(value);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotValue
 */
COWL_INLINE
bool cowl_annot_value_equals(CowlAnyAnnotValue *lhs, CowlAnyAnnotValue *rhs) {
    return cowl_equals(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param value The annotation value.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotValue
 */
COWL_INLINE
ulib_uint cowl_annot_value_hash(CowlAnyAnnotValue *value) {
    return cowl_hash(value);
}

COWL_END_DECLS

#endif // COWL_ANNOT_VALUE_H
