/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_PRIVATE_H
#define COWL_OBJECT_PRIVATE_H

#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_object.h" // IWYU pragma: export
#include "cowl_object_flags.h"
#include "ulib.h"

COWL_BEGIN_DECLS

struct CowlObject {
    CowlObjectFlags flags;
};

typedef struct CowlComposite {
    CowlObject super;
    union {
        CowlAny *obj;
        ulib_uint uint;
    } fields[];
} CowlComposite;

#define COWL_OBJECT_BIT_INIT(TYPE, HAS_BIT)                                                        \
    ((CowlObject){ .flags = cowl_object_flags(TYPE, HAS_BIT) })
#define COWL_OBJECT_INIT(TYPE) COWL_OBJECT_BIT_INIT(TYPE, 0)

ULIB_INLINE
ulib_uint cowl_object_get_ref(CowlAny *o) {
    return cowl_object_flags_get_ref(((CowlObject *)o)->flags);
}

ULIB_INLINE
void cowl_object_incr_ref(CowlAny *o) {
    cowl_object_flags_incr_ref(((CowlObject *)o)->flags);
}

ULIB_INLINE
ulib_uint cowl_object_decr_ref(CowlAny *o) {
    cowl_object_flags_decr_ref(((CowlObject *)o)->flags);
    return cowl_object_flags_get_ref(((CowlObject *)o)->flags);
}

ULIB_INLINE
bool cowl_object_bit_get(CowlAny *o) {
    return cowl_object_flags_has_bit(((CowlObject *)o)->flags);
}

ULIB_INLINE
void cowl_object_bit_set(CowlAny *o) {
    cowl_object_flags_set_bit(((CowlObject *)o)->flags);
}

ULIB_INLINE
void cowl_object_bit_unset(CowlAny *o) {
    cowl_object_flags_unset_bit(((CowlObject *)o)->flags);
}

COWL_END_DECLS

#endif // COWL_OBJECT_PRIVATE_H
