/**
 * Defines CowlPrimitiveFlags and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PRIMITIVE_FLAGS_H
#define COWL_PRIMITIVE_FLAGS_H

#include "cowl_primitive_type.h"

COWL_BEGIN_DECLS

/// Size of the @type{#CowlPrimitiveFlags} type in bits.
#define COWL_PF 8

/**
 * @defgroup CowlPrimitiveFlags_type CowlPrimitiveFlags type and values
 * @{
 */

/**
 * Flags to control iteration over primitives
 *
 * @alias typedef UBit(N) CowlPrimitiveFlags;
 */
typedef UBit(COWL_PF) CowlPrimitiveFlags;

/// Iterate over no primitives.
#define COWL_PF_NONE ubit_none(COWL_PF)

/// Iterate over all primitives.
#define COWL_PF_ALL ubit(COWL_PF, ubit_bit(COWL_PF, COWL_PT_COUNT) - 1)

/// Iterate over classes.
#define COWL_PF_CLASS ubit_bit(COWL_PF, 0)

/// Iterate over object properties.
#define COWL_PF_OBJ_PROP ubit_bit(COWL_PF, 1)

/// Iterate over data properties.
#define COWL_PF_DATA_PROP ubit_bit(COWL_PF, 2)

/// Iterate over annotation properties.
#define COWL_PF_ANNOT_PROP ubit_bit(COWL_PF, 3)

/// Iterate over named individuals.
#define COWL_PF_NAMED_IND ubit_bit(COWL_PF, 4)

/// Iterate over anonymous individuals.
#define COWL_PF_ANON_IND ubit_bit(COWL_PF, 5)

/// Iterate over datatypes.
#define COWL_PF_DATATYPE ubit_bit(COWL_PF, 6)

/// Iterate over IRIs.
#define COWL_PF_IRI ubit_bit(COWL_PF, 7)

/// Iterate over entities.
#define COWL_PF_ENTITY                                                                             \
    (COWL_PF_CLASS | COWL_PF_OBJ_PROP | COWL_PF_DATA_PROP | COWL_PF_ANNOT_PROP |                   \
     COWL_PF_NAMED_IND | COWL_PF_DATATYPE)

/// @}

/**
 * @defgroup CowlPrimitiveFlags_api CowlPrimitiveFlags API
 * @{
 */

/**
 * Returns a bitmask with a bit set for the specified primitive type.
 *
 * @param type Primitive type.
 * @return Flags.
 */
COWL_CONST
COWL_INLINE
CowlPrimitiveFlags cowl_primitive_flags_from_type(CowlPrimitiveType type) {
    return ubit_bit(COWL_PF, type);
}

/**
 * Checks whether the specified type is included in the flags.
 *
 * @param flags Primitive flags.
 * @param type Primitive type.
 * @return True if the type is included in the flags, false otherwise.
 */
COWL_CONST
COWL_INLINE
bool cowl_primitive_flags_has_type(CowlPrimitiveFlags flags, CowlPrimitiveType type) {
    return ubit_is_set(COWL_PF, flags, ubit_bit(COWL_PF, type));
}

/// @}

COWL_END_DECLS

#endif // COWL_PRIMITIVE_FLAGS_H
