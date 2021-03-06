/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_PRIVATE_H
#define COWL_OBJECT_PRIVATE_H

#include "cowl_object.h"
#include "cowl_object_flags.h"

COWL_BEGIN_DECLS

typedef cowl_struct(CowlObject) {
    CowlObjectFlags flags;
} CowlObject;

typedef cowl_struct(CowlHashObject) {
    CowlObject super;
    cowl_uint hash;
} CowlHashObject;

#define COWL_OBJECT_BIT_INIT(TYPE, HAS_BIT) \
    ((CowlObject){ .flags = cowl_object_flags_init(TYPE, HAS_BIT) })
#define COWL_OBJECT_INIT(TYPE) COWL_OBJECT_BIT_INIT(TYPE, 0)

#define COWL_HASH_OBJECT_BIT_INIT(TYPE, HAS_BIT, HASH) \
    ((CowlHashObject){ .super = COWL_OBJECT_BIT_INIT(TYPE, HAS_BIT), .hash = (HASH) })
#define COWL_HASH_OBJECT_INIT(TYPE, HASH) COWL_HASH_OBJECT_BIT_INIT(TYPE, 0, HASH)

#define cowl_object_get_ref_count(o) cowl_object_flags_get_ref_count(((CowlObject *)(o))->flags)
#define cowl_object_retain(o) (cowl_object_flags_retain(((CowlObject *)(o))->flags), (o))
#define cowl_object_release(o) \
    (cowl_object_flags_release(((CowlObject *)(o))->flags), cowl_object_get_ref_count(o))

#define cowl_object_equals_impl(LHS, RHS) ( \
    (((CowlObject *)(LHS))->flags & COWL_OBJECT_FLAGS_BIT_TYPE_MASK) == \
    (((CowlObject *)(RHS))->flags & COWL_OBJECT_FLAGS_BIT_TYPE_MASK) \
)
#define cowl_hash_object_equals_impl(LHS, RHS) (                                                    \
    cowl_object_equals_impl(LHS, RHS) &&                                                            \
    ((CowlHashObject *)(LHS))->hash == ((CowlHashObject *)(RHS))->hash                              \
)

#define cowl_object_hash_get(o) (((CowlHashObject *)(o))->hash)
#define cowl_object_hash_set(o, h) (((CowlHashObject *)(o))->hash = (h))

#define cowl_get_type(object) cowl_object_get_type((CowlObject *)(object))

COWL_END_DECLS

#endif // COWL_OBJECT_PRIVATE_H
