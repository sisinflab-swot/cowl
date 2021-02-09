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
#include "uflags.h"
#include "uhash.h"
#include "uvec.h"

#include <inttypes.h>

COWL_BEGIN_DECLS

/**
 * Unsigned integer type.
 *
 * The size of this type can be controlled through the *COWL_TINY* and *COWL_HUGE*
 * preprocessor definitions:
 *
 * - **No definitions** (*default*): 4 bytes (*uint32_t*)
 *
 * - **COWL_TINY**: 2 bytes (*uint16_t*)
 *
 * - **COWL_HUGE**: 8 bytes (*uint64_t*)
 *
 * @typedef cowl_uint
 */

/**
 * Maximum value of a cowl_uint variable.
 *
 * @def COWL_UINT_MAX
 */

/**
 * Format string for cowl_uint variables.
 *
 * @def COWL_UINT_FMT
 */

#if defined COWL_TINY
    typedef uint16_t cowl_uint;
    #define COWL_UINT_MAX UINT16_MAX
    #define COWL_UINT_FMT PRIu16
#elif defined COWL_HUGE
    typedef uint64_t cowl_uint;
    #define COWL_UINT_MAX UINT64_MAX
    #define COWL_UINT_FMT PRIu64
#else
    typedef uint32_t cowl_uint;
    #define COWL_UINT_MAX UINT32_MAX
    #define COWL_UINT_FMT PRIu32
#endif

/// Byte type.
typedef uint8_t cowl_byte;

COWL_END_DECLS

#endif // COWL_BASE_TYPES_H
