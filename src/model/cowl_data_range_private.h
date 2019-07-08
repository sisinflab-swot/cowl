/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_RANGE_PRIVATE_H
#define COWL_DATA_RANGE_PRIVATE_H

#include "cowl_data_range.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDataRange) {
    CowlHashObject super;
    CowlDataRangeType type;
};

#define COWL_DATA_RANGE_INIT(T, H) { .super = COWL_HASH_OBJECT_INIT(H), .type = (T) }

COWL_END_DECLS

#endif // COWL_DATA_RANGE_PRIVATE_H
