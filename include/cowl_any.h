/**
 * Defines placeholder types for generic Cowl objects.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANY_H
#define COWL_ANY_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

/**
 * @defgroup cowl_any cowl_any
 * @{
 */

/// Placeholder for any @type{#CowlObject}.
typedef void CowlAny;

/// Placeholder for any @type{#CowlAnnotValue}.
typedef void CowlAnyAnnotValue;

/// Placeholder for any @type{#CowlAxiom}.
typedef void CowlAnyAxiom;

/// Placeholder for any @type{#CowlClsExp}.
typedef void CowlAnyClsExp;

/// Placeholder for any @type{#CowlDataPropExp}.
typedef void CowlAnyDataPropExp;

/// Placeholder for any @type{#CowlDataRange}.
typedef void CowlAnyDataRange;

/// Placeholder for any @type{#CowlEntity}.
typedef void CowlAnyEntity;

/// Placeholder for any @type{#CowlIndividual}.
typedef void CowlAnyIndividual;

/// Placeholder for any @type{#CowlPrimitive}.
typedef void CowlAnyPrimitive;

/// Placeholder for any @type{#CowlObjPropExp}.
typedef void CowlAnyObjPropExp;

/// @}

COWL_END_DECLS

#endif // COWL_ANY_H
