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

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// Size of the CowlPosition type in bits.
#define COWL_PS 8

/**
 * @defgroup CowlPosition Position of a component in an OWL construct.
 * @{
 */

/// Position of a component in an OWL construct.
typedef UBit(COWL_PS) CowlPosition;

/// No position.
#define COWL_PS_NONE ubit_none(COWL_PS)

/// Any position.
#define COWL_PS_ANY ubit_all(COWL_PS)

/// Left position.
#define COWL_PS_LEFT ubit_bit(COWL_PF, 0)

/// Right position.
#define COWL_PS_RIGHT ubit_bit(COWL_PF, 1)

/// Middle position.
#define COWL_PS_MIDDLE ubit_bit(COWL_PF, 2)

/// Subject position.
#define COWL_PS_SUBJECT COWL_PS_LEFT

/// Predicate position.
#define COWL_PS_PREDICATE COWL_PS_MIDDLE

/// Object position.
#define COWL_PS_OBJECT COWL_PS_RIGHT

/// @}

COWL_END_DECLS

#endif // COWL_POSITION_H
