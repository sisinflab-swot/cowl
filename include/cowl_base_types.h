/**
 * Defines base types used throughout the API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_BASE_TYPES_H
#define COWL_BASE_TYPES_H

#include "cowl_compat.h"
#include "cowl_flags.h"
#include "uhash.h"
#include "vector.h"

COWL_BEGIN_DECLS

/// Unsigned integer type.
typedef uhash_uint_t cowl_uint_t;

COWL_END_DECLS

#endif // COWL_BASE_TYPES_H
