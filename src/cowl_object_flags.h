/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_FLAGS_H
#define COWL_OBJECT_FLAGS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

// CowlObjectFlags holds information about reference count and object type, while carrying
// an additional boolean flag which can be used by concrete pseudo-classes. Its layout is like this:
//
// |_OTYPE_|B|_______REF_COUNT________|
//
// The reference count field is variably sized, depending on certain preprocessor definitions:
//
// - No definitions (default): 3 bytes
// - COWL_HUGE: 7 bytes
//
// This of course limits the maximum number of references that can be held for any object.
// As of this writing, Cowl does not make any checks about this limit, so one must take
// care not to over-retain objects. Anyway, this is usually not a problem, as the maximum number
// of references is (2^24 - 1), being as big as (2^56 - 1) if COWL_HUGE is defined.

#if defined COWL_HUGE
#define COWL_OBJECT_FLAGS_SIZE 64
#else
#define COWL_OBJECT_FLAGS_SIZE 32
#endif

#define COWL_OBJECT_FLAGS_TYPE_SIZE 7
#define COWL_OBJECT_FLAGS_REF_SIZE (COWL_OBJECT_FLAGS_SIZE - COWL_OBJECT_FLAGS_TYPE_SIZE - 1)

#define COWL_OF COWL_OBJECT_FLAGS_SIZE
typedef UBit(COWL_OF) CowlObjectFlags;

#define COWL_OBJECT_FLAGS_BIT_OFFSET COWL_OBJECT_FLAGS_REF_SIZE
#define COWL_OBJECT_FLAGS_TYPE_OFFSET (COWL_OBJECT_FLAGS_BIT_OFFSET + 1)

#define COWL_OBJECT_FLAGS_BIT_MASK ubit_bit(COWL_OF, COWL_OBJECT_FLAGS_BIT_OFFSET)
#define COWL_OBJECT_FLAGS_REF_MASK (COWL_OBJECT_FLAGS_BIT_MASK - 1)
#define COWL_OBJECT_FLAGS_BIT_TYPE_MASK (ubit_all(COWL_OF) & ~COWL_OBJECT_FLAGS_REF_MASK)
#define COWL_OBJECT_FLAGS_TYPE_MASK (COWL_OBJECT_FLAGS_BIT_TYPE_MASK & ~COWL_OBJECT_FLAGS_BIT_MASK)

#define cowl_object_flags(TYPE, HAS_BIT)                                                           \
    (ubit_lshift(COWL_OF, TYPE, COWL_OBJECT_FLAGS_TYPE_OFFSET) |                                   \
     ((HAS_BIT) ? COWL_OBJECT_FLAGS_BIT_MASK : ubit_none(COWL_OF)) | 1)

#define cowl_object_flags_has_bit(FLAGS) ubit_is_set(COWL_OF, FLAGS, COWL_OBJECT_FLAGS_BIT_MASK)
#define cowl_object_flags_set_bit(FLAGS)                                                           \
    ((FLAGS) = ubit_set(COWL_OF, FLAGS, COWL_OBJECT_FLAGS_BIT_MASK))

#define cowl_object_flags_get_type(FLAGS)                                                          \
    ((CowlObjectType)(((FLAGS)&COWL_OBJECT_FLAGS_TYPE_MASK) >> COWL_OBJECT_FLAGS_TYPE_OFFSET))

#define cowl_object_flags_get_ref(FLAGS) ((ulib_uint)((FLAGS)&COWL_OBJECT_FLAGS_REF_MASK))

#define cowl_object_flags_incr_ref(FLAGS) (++(FLAGS))
#define cowl_object_flags_decr_ref(FLAGS) (--(FLAGS))

COWL_END_DECLS

#endif // COWL_OBJECT_FLAGS_H
