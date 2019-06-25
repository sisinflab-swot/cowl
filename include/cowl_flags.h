/// @author Ivano Bilenchi

#ifndef COWL_FLAGS_H
#define COWL_FLAGS_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// 8-bit bitmask.
typedef uint8_t CowlFlags8;

/// 16-bit bitmask.
typedef uint16_t CowlFlags16;

/// 32-bit bitmask.
typedef uint32_t CowlFlags32;

/// 64-bit bitmask.
typedef uint64_t CowlFlags64;

/// Empty bitmask.
#define cowl_flags_empty (0u)

/**
 * Returns a bitmask with the specified bit set.
 *
 * @param N Bit to set.
 * @return Bitmask with the specified bit set.
 */
#define cowl_flags_bit(N) (1u << N##u)

/**
 * Use this directive to check whether a bitmask has specific bits set.
 *
 * @param OPTIONS Bitmask.
 * @param OPTION Bits to check.
 *
 * @return True if the bits are set, false otherwise.
 */
#define cowl_flags_is_set(OPTIONS, OPTION) (((OPTIONS) & (OPTION)) == (OPTION))

/**
 * Use this directive to check whether a bitmask has any of the specified bits set.
 *
 * @param OPTIONS Bitmask.
 * @param OPTION Bits to check.
 *
 * @return True if at least one of the specified bits is set, false otherwise.
 */
#define cowl_flags_is_any_set(OPTIONS, OPTION) (((OPTIONS) & (OPTION)) != 0)

/**
 * Use this directive to set bits in a bitmask.
 *
 * @param OPTIONS Bitmask.
 * @param OPTION Bits to set.
 */
#define cowl_flags_set(OPTIONS, OPTION) ((OPTIONS) |= (OPTION))

/**
 * Use this directive to unset bits in a bitmask.
 *
 * @param OPTIONS Bitmask.
 * @param OPTION Bits to unset.
 */
#define cowl_flags_unset(OPTIONS, OPTION) ((OPTIONS) &= ~(OPTION))

/**
 * Use this directive to toggle in a bitmask.
 *
 * @param OPTIONS Bitmask.
 * @param OPTION Bits to toggle.
 */
#define cowl_flags_toggle(OPTIONS, OPTION) ((OPTIONS) ^= (OPTION))

COWL_END_DECLS

#endif // COWL_FLAGS_H
