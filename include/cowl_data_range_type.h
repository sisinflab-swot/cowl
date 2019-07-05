/// @author Ivano Bilenchi

#ifndef COWL_DATA_RANGE_TYPE_H
#define COWL_DATA_RANGE_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the different types of OWL 2 data ranges.
typedef enum CowlDataRangeType {

    /// Represents datatypes.
    COWL_DRT_DATATYPE,

    /// Represents datatype restrictions.
    COWL_DRT_DATATYPE_RESTR,

    /// Represents the intersection of data ranges.
    COWL_DRT_DATA_INTERSECT,

    /// Represents the union of data ranges.
    COWL_DRT_DATA_UNION,

    /// Represents the complement of data ranges.
    COWL_DRT_DATA_COMPL,

    /// Represents enumerations of literals.
    COWL_DRT_DATA_ONE_OF,

    COWL_DRT_COUNT,
    COWL_DRT_FIRST = COWL_DRT_DATATYPE

} CowlDataRangeType;

COWL_END_DECLS

#endif // COWL_DATA_RANGE_TYPE_H
