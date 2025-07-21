/**
 * Declares API configuration functions.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CONFIG_H
#define COWL_CONFIG_H

#include "cowl_attrs.h"
#include "cowl_ret.h"

COWL_BEGIN_DECLS

/**
 * @defgroup init Library initialization
 * @{
 */

/**
 * Initializes the library.
 *
 * @return Return code.
 *
 * @note It's mandatory to call this function before making any other function call.
 */
COWL_API
cowl_ret cowl_init(void);

/**
 * Deinitializes the library.
 *
 * @note Calling this function releases any resource loaded when the library was initialized.
 *       You **must not** use objects retrieved before deinitializing the library, even
 *       if you later re-initialize it.
 */
COWL_API
void cowl_deinit(void);

/// @}

COWL_END_DECLS

#endif // COWL_CONFIG_H
