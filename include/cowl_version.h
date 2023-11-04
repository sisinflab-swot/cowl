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

#include "cowl_std.h"

COWL_BEGIN_DECLS

/**
 * Returns the version of the library.
 *
 * @return Library version.
 */
COWL_API
UVersion cowl_get_version(void);

/**
 * Returns the string representation of the library version.
 *
 * @return String representation.
 */
COWL_API
COWL_RETAINED
CowlString *cowl_get_version_string(void);

COWL_END_DECLS

#endif // COWL_VERSION_H
