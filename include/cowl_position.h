/**
 * Defines CowlPosition and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_POSITION_H
#define COWL_POSITION_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

/// Size of the @type{#CowlPosition} type in bits.
#define COWL_PS 8

/**
 * @defgroup CowlPosition Position of a component in an OWL construct.
 * @{
 */

/**
 * Position of a component in an OWL construct.
 *
 * @alias typedef UBit(N) CowlPosition;
 */
typedef UBit(COWL_PS) CowlPosition;

/// No position.
#define COWL_PS_NONE ubit_none(COWL_PS)

/// Left position.
#define COWL_PS_LEFT ubit_bit(COWL_PS, 0)

/// Right position.
#define COWL_PS_RIGHT ubit_bit(COWL_PS, 1)

/// Middle position.
#define COWL_PS_MIDDLE ubit_bit(COWL_PS, 2)

/// Any position.
#define COWL_PS_ANY ubit(COWL_PS, COWL_PS_LEFT | COWL_PS_MIDDLE | COWL_PS_RIGHT)

/// Subject position in assertion axioms.
#define COWL_PS_SUBJECT COWL_PS_MIDDLE

/// Predicate position in assertion axioms.
#define COWL_PS_PREDICATE COWL_PS_LEFT

/// Object position in assertion axioms.
#define COWL_PS_OBJECT COWL_PS_RIGHT

/// @}

COWL_END_DECLS

#endif // COWL_POSITION_H
