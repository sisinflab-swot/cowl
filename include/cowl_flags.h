/**
 * Defines bitmask manipulation API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_FLAGS_H
#define COWL_FLAGS_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/**
 * Bitmask manipulation API.
 *
 * @note This is not a real data structure, though it is declared as such
 *       for better grouping in the generated documentation.
 *
 * @struct CowlFlags
 */

/// Concatenates the 'a' and 'b' tokens, allowing 'a' and 'b' to be macro-expanded.
#define __COWL_MACRO_CONCAT(a, b) __COWL_MACRO_CONCAT_INNER(a, b)
#define __COWL_MACRO_CONCAT_INNER(a, b) a##b

/**
 * Bitmask type.
 *
 * @param N Number of bits. Allowed values: 8, 16, 32 and 64.
 *
 * @public @related CowlFlags
 */
#define CowlFlags(N) __COWL_MACRO_CONCAT(__COWL_MACRO_CONCAT(uint, N), _t)

/**
 * Empty bitmask.
 *
 * @public @related CowlFlags
 */
#define cowl_flags_empty (0u)

/**
 * Bitmask with all bits set to one.
 *
 * @public @related CowlFlags
 */
#define cowl_flags_all(N) ((CowlFlags(N))-1)

/**
 * Returns a bitmask with the specified bit set.
 *
 * @param N Bit to set.
 * @return Bitmask with the specified bit set.
 *
 * @public @related CowlFlags
 */
#define cowl_flags_bit(N) (1u << __COWL_MACRO_CONCAT(N, u))

/**
 * Use this directive to check whether a bitmask has specific bits set.
 *
 * @param OPTIONS Bitmask.
 * @param OPTION Bits to check.
 *
 * @return True if the bits are set, false otherwise.
 *
 * @public @related CowlFlags
 */
#define cowl_flags_is_set(OPTIONS, OPTION) (((OPTIONS) & (OPTION)) == (OPTION))

/**
 * Use this directive to check whether a bitmask has any of the specified bits set.
 *
 * @param OPTIONS Bitmask.
 * @param OPTION Bits to check.
 *
 * @return True if at least one of the specified bits is set, false otherwise.
 *
 * @public @related CowlFlags
 */
#define cowl_flags_is_any_set(OPTIONS, OPTION) (((OPTIONS) & (OPTION)) != 0)

/**
 * Use this directive to set bits in a bitmask.
 *
 * @param OPTIONS Bitmask.
 * @param OPTION Bits to set.
 *
 * @public @related CowlFlags
 */
#define cowl_flags_set(OPTIONS, OPTION) ((OPTIONS) |= (OPTION))

/**
 * Use this directive to unset bits in a bitmask.
 *
 * @param OPTIONS Bitmask.
 * @param OPTION Bits to unset.
 *
 * @public @related CowlFlags
 */
#define cowl_flags_unset(OPTIONS, OPTION) ((OPTIONS) &= ~(OPTION))

/**
 * Use this directive to toggle bits in a bitmask.
 *
 * @param OPTIONS Bitmask.
 * @param OPTION Bits to toggle.
 *
 * @public @related CowlFlags
 */
#define cowl_flags_toggle(OPTIONS, OPTION) ((OPTIONS) ^= (OPTION))

COWL_END_DECLS

#endif // COWL_FLAGS_H
