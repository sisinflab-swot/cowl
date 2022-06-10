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

#include "cowl_object.h"
#include "cowl_object_flags.h"

COWL_BEGIN_DECLS

extern ulib_byte composite_fields[];

typedef struct CowlObject {
    CowlObjectFlags flags;
} CowlObject;

typedef struct CowlComposite {
    CowlObject super;
    void *data[];
} CowlComposite;

#define COWL_OBJECT_BIT_INIT(TYPE, HAS_BIT) \
    ((CowlObject){ .flags = cowl_object_flags_init(TYPE, HAS_BIT) })
#define COWL_OBJECT_INIT(TYPE) COWL_OBJECT_BIT_INIT(TYPE, 0)

#define cowl_object_get_ref(o) cowl_object_flags_get_ref(((CowlObject *)(o))->flags)
#define cowl_object_incr_ref(o) \
    (cowl_object_flags_incr_ref(((CowlObject *)(o))->flags), (o))
#define cowl_object_decr_ref(o) \
    (cowl_object_flags_decr_ref(((CowlObject *)(o))->flags), cowl_object_get_ref(o))

#define cowl_object_bit_get(o) cowl_object_flags_has_bit(((CowlObject *)(o))->flags)
#define cowl_object_bit_set(o) cowl_object_flags_set_bit(((CowlObject *)(o))->flags)

cowl_ret cowl_object_api_init(void);
void cowl_object_api_deinit(void);

COWL_END_DECLS

#endif // COWL_OBJECT_PRIVATE_H
