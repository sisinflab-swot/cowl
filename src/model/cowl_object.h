/// @author Ivano Bilenchi

#ifndef COWL_OBJECT_H
#define COWL_OBJECT_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef cowl_struct(CowlObject) {
    cowl_uint_t ref_count;
    cowl_uint_t hash;
} CowlObject;

#define COWL_OBJECT_INIT(H) { .ref_count = 1, .hash = (H) }

#define cowl_object_ref_get(o) (((CowlObject *)(o))->ref_count)
#define cowl_object_retain(o) (++cowl_object_ref_get(o), (o))
#define cowl_object_release(o) (--cowl_object_ref_get(o))

#define cowl_object_hash_get(c) (((CowlObject *)(c))->hash)
#define cowl_object_hash_set(c, h) (((CowlObject *)(c))->hash = (h))

COWL_END_DECLS

#endif // COWL_OBJECT_H
