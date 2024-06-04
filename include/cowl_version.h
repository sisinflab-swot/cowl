/**
 * Allows retrieving the version of the library.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_VERSION_H
#define COWL_VERSION_H

#include "cowl_attrs.h"
#include "cowl_macros.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
/// @endcond

/**
 * @defgroup version Library version metadata
 * @{
 */

/**
 * Returns the version of the library.
 *
 * @return Library version.
 */
COWL_API
COWL_CONST
UVersion cowl_get_version(void);

/**
 * Returns the string representation of the library version.
 *
 * @return String representation.
 */
COWL_API
COWL_RETAINED
CowlString *cowl_get_version_string(void);

/// @}

COWL_END_DECLS

#endif // COWL_VERSION_H
