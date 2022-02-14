/**
 * Defines the #CowlNAryType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_TYPE_H
#define COWL_NARY_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the type of CowlNAryBool and CowlNAryData.
typedef enum CowlNAryType {

/// @name Types

    /// Intersection.
    COWL_NT_INTERSECT,

    /// Union.
    COWL_NT_UNION,

/// @name Markers

    /// Number of enum values.
    COWL_NT_COUNT,

    /// First enum value.
    COWL_NT_FIRST = 0

} CowlNAryType;

COWL_END_DECLS

#endif // COWL_NARY_TYPE_H
