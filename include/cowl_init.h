/**
 * Declares API init/deinit functions.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INIT_H
#define COWL_INIT_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/**
 * Initializes the API.
 *
 * @return Return code.
 *
 * @note It's mandatory to call this function before making any other Cowl API call.
 */
COWL_PUBLIC
cowl_ret_t cowl_api_init(void);

/**
 * Deinitializes the API.
 *
 * @note Calling this function releases any resource loaded when the API was initialized.
 *       You **must not** make API calls on objects retrieved before deinitializing the API, even
 *       if you later re-initialize it.
 */
COWL_PUBLIC
void cowl_api_deinit(void);

COWL_END_DECLS

#endif // COWL_INIT_H
