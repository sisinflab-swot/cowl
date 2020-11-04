/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PRIMITIVE_FLAGS_H
#define COWL_PRIMITIVE_FLAGS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// These flags are used to control iteration over primitives.
typedef CowlFlags(8) CowlPrimitiveFlags;

/// Iterate over all primitives.
#define COWL_PF_NONE        cowl_flags_empty

/// Iterate over no primitives.
#define COWL_PF_ALL         ((CowlPrimitiveFlags)-1)

/// Iterate over classes.
#define COWL_PF_CLASS       cowl_flags_bit(0)

/// Iterate over object properties.
#define COWL_PF_OBJ_PROP    cowl_flags_bit(1)

/// Iterate over data properties.
#define COWL_PF_DATA_PROP   cowl_flags_bit(2)

/// Iterate over annotation properties.
#define COWL_PF_ANNOT_PROP  cowl_flags_bit(3)

/// Iterate over named individuals.
#define COWL_PF_NAMED_IND   cowl_flags_bit(4)

/// Iterate over anonymous individuals.
#define COWL_PF_ANON_IND    cowl_flags_bit(5)

/// Iterate over datatypes.
#define COWL_PF_DATATYPE    cowl_flags_bit(6)

/// Iterate over entities.
#define COWL_PF_ENTITY      (COWL_PF_CLASS | COWL_PF_OBJ_PROP | COWL_PF_DATA_PROP | \
                             COWL_PF_ANNOT_PROP | COWL_PF_NAMED_IND | COWL_PF_DATATYPE)

COWL_END_DECLS

#endif // COWL_PRIMITIVE_FLAGS_H
