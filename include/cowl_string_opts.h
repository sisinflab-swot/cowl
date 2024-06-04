/**
 * Defines CowlStringOpts.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STRING_OPTS_H
#define COWL_STRING_OPTS_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

/// Size of the @type{#CowlStringOpts} type in bits.
#define COWL_SO 8

/**
 * @defgroup CowlStringOpts CowlStringOpts API
 * @{
 */

/**
 * String creation options.
 *
 * @see @func{#cowl_string_opt()}
 * @alias typedef UBit(N) CowlStringOpts;
 */
typedef UBit(COWL_SO) CowlStringOpts;

/// Empty options.
#define COWL_SO_NONE ubit_none(COWL_SO)

/// Copy the underlying raw string.
#define COWL_SO_COPY ubit_bit(COWL_SO, 0)

/// Intern the resulting string.
#define COWL_SO_INTERN ubit_bit(COWL_SO, 1)

/// @}

COWL_END_DECLS

#endif // COWL_STRING_OPTS_H
