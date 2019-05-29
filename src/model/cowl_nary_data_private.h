/// @author Ivano Bilenchi

#ifndef COWL_NARY_DATA_PRIVATE_H
#define COWL_NARY_DATA_PRIVATE_H

#include "cowl_nary_data.h"
#include "cowl_data_range_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlNAryData) {
    CowlDataRange super;
    CowlDataRangeSet *operands;
};

COWL_END_DECLS

#endif // COWL_NARY_DATA_PRIVATE_H
