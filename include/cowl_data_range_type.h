/**
 * Defines the #CowlDataRangeType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier - EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_RANGE_TYPE_H
#define COWL_DATA_RANGE_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS


/// Represents the type of CowlDataRange.
typedef enum CowlDataRangeType {

/// @name Types

    /// CowlDatatype - Datatype.
    COWL_DRT_DATATYPE,

    /// CowlDatatypeRestr - Datatype restriction.
    COWL_DRT_DATATYPE_RESTR,

    /// CowlNAryData - Intersection of data ranges.
    COWL_DRT_DATA_INTERSECT,

    /// CowlNAryData - Union of data ranges.
    COWL_DRT_DATA_UNION,

    /// CowlDataCompl - Complement of data ranges.
    COWL_DRT_DATA_COMPL,

    /// CowlDataOneOf - Enumeration of literals.
    COWL_DRT_DATA_ONE_OF,

/// @name Markers

    /// Number of enum values.
    COWL_DRT_COUNT,

    /// First enum value.
    COWL_DRT_FIRST = 0

} CowlDataRangeType;

COWL_END_DECLS

#endif // COWL_DATA_RANGE_TYPE_H
