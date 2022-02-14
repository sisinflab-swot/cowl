/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_RANGE_PRIVATE_H
#define COWL_DATA_RANGE_PRIVATE_H

#include "cowl_data_range.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

struct CowlDataRange {
    CowlHashObject super;
};

#define COWL_DATA_RANGE_INIT(T, H) {                                                                \
    .super = COWL_HASH_OBJECT_INIT((CowlObjectType)(T) + COWL_OT_DR_DATATYPE, H)                    \
}

COWL_END_DECLS

#endif // COWL_DATA_RANGE_PRIVATE_H
