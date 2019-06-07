/// @author Ivano Bilenchi

#ifndef COWL_OBJECT_H
#define COWL_OBJECT_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef cowl_struct(CowlObject) {
    cowl_uint_t ref_count;
} CowlObject;

typedef cowl_struct(CowlHashObject) {
    CowlObject super;
    cowl_uint_t hash;
} CowlHashObject;

#define COWL_OBJECT_INIT { .ref_count = 1 }
#define COWL_HASH_OBJECT_INIT(H) { .super = COWL_OBJECT_INIT, .hash = (H) }

#define cowl_object_ref_get(o) (((CowlObject *)(o))->ref_count)
#define cowl_object_retain(o) (++cowl_object_ref_get(o), (o))
#define cowl_object_release(o) (--cowl_object_ref_get(o))

#define cowl_object_hash_get(c) (((CowlHashObject *)(c))->hash)
#define cowl_object_hash_set(c, h) (((CowlHashObject *)(c))->hash = (h))

COWL_END_DECLS

#endif // COWL_OBJECT_H
