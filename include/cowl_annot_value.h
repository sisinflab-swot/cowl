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
COWL_API
CowlAnnotValueType cowl_annot_value_get_type(CowlAnyAnnotValue *value);

COWL_END_DECLS

#endif // COWL_ANNOT_VALUE_H
