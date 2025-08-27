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
#include "cowl_utils.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlReader);
cowl_struct_decl(CowlWriter);
cowl_struct_decl(CowlPrefixMap);
/// @endcond

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

/**
 * @defgroup defaults Library defaults
 * @{
 */

/**
 * Returns the default reader.
 *
 * @return Default reader.
 */
COWL_API
COWL_PURE
CowlReader *cowl_get_reader(void);

/**
 * Sets the default reader.
 *
 * @param reader Reader.
 */
COWL_API
void cowl_set_reader(CowlReader *reader);

/**
 * Returns the default writer.
 *
 * @return Default writer.
 */
COWL_API
COWL_PURE
CowlWriter *cowl_get_writer(void);

/**
 * Sets the default writer.
 *
 * @param writer Writer.
 */
COWL_API
void cowl_set_writer(CowlWriter *writer);

/**
 * Returns the default prefix map.
 *
 * @return Default prefix map.
 */
COWL_API
COWL_PURE
CowlPrefixMap *cowl_get_prefix_map(void);

/// @}

COWL_END_DECLS

#endif // COWL_CONFIG_H
