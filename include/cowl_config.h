/**
 * Declares API configuration functions.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CONFIG_H
#define COWL_CONFIG_H

#include "cowl_std.h"
#include "cowl_error_handler.h"
#include "cowl_import_loader.h"
#include "cowl_parser.h"

COWL_BEGIN_DECLS

/**
 * Initializes the API.
 *
 * @return Return code.
 *
 * @note It's mandatory to call this function before making any other Cowl API call.
 */
COWL_PUBLIC
cowl_ret cowl_api_init(void);

/**
 * Deinitializes the API.
 *
 * @note Calling this function releases any resource loaded when the API was initialized.
 *       You **must not** make API calls on objects retrieved before deinitializing the API, even
 *       if you later re-initialize it.
 */
COWL_PUBLIC
void cowl_api_deinit(void);

/**
 * Sets the global error handler.
 *
 * @param handler The error handler.
 *
 * @note This function must be called again if you reinitialize the API after deinitializing it.
 */
COWL_PUBLIC
void cowl_api_set_error_handler(CowlErrorHandler handler);

/**
 * Sets the global import loader.
 *
 * @param loader The import loader.
 *
 * @note This function must be called again if you reinitialize the API after deinitializing it.
 */
COWL_PUBLIC
void cowl_api_set_import_loader(CowlImportLoader loader);

/**
 * Sets the default parser.
 *
 * @param parser The parser.
 *
 * @note This function must be called again if you reinitialize the API after deinitializing it.
 */
COWL_PUBLIC
void cowl_api_set_parser(CowlParser parser);

COWL_END_DECLS

#endif // COWL_CONFIG_H
