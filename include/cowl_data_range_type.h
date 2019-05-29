/// @author Ivano Bilenchi

#ifndef COWL_DATA_RANGE_TYPE_H
#define COWL_DATA_RANGE_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the different types of OWL 2 data ranges.
typedef enum CowlDataRangeType {

    /// Represents datatypes.
    CDRT_DATATYPE,

    /// Represents datatype restrictions.
    CDRT_DATATYPE_RESTRICTION,

    /// Represents the intersection of data ranges.
    CDRT_DATA_INTERSECTION,

    /// Represents the union of data ranges.
    CDRT_DATA_UNION,

    /// Represents the complement of data ranges.
    CDRT_DATA_COMPLEMENT,

    /// Represents enumerations of literals.
    CDRT_DATA_ONE_OF

} CowlDataRangeType;

COWL_END_DECLS

#endif // COWL_DATA_RANGE_TYPE_H
