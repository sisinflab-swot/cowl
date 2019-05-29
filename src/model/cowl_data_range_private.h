/// @author Ivano Bilenchi

#ifndef COWL_DATA_RANGE_PRIVATE_H
#define COWL_DATA_RANGE_PRIVATE_H

#include "cowl_data_range.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDataRange) {
    CowlObject super;
    CowlDataRangeType type;
};

#define COWL_DATA_RANGE_INIT(T, H) { .super = COWL_OBJECT_INIT(H), .type = (T) }

#define cowl_data_range_ref_get(c) cowl_object_ref_get(c)
#define cowl_data_range_ref_incr(c) cowl_object_retain(c)
#define cowl_data_range_ref_decr(c) cowl_object_release(c)

#define cowl_data_range_hash_get(c) cowl_object_hash_get(c)
#define cowl_data_range_hash_set(c, h) cowl_object_hash_set(c, h)

COWL_END_DECLS

#endif // COWL_DATA_RANGE_PRIVATE_H
