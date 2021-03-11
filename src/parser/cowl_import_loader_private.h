/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_IMPORT_LOADER_PRIVATE_H
#define COWL_IMPORT_LOADER_PRIVATE_H

#include "cowl_import_loader.h"

COWL_BEGIN_DECLS

#define cowl_import_loader_deinit(LOADER) do {                                                      \
    if ((LOADER).free) (LOADER).free((LOADER).ctx);                                                 \
} while (0)

COWL_END_DECLS

#endif // COWL_IMPORT_LOADER_PRIVATE_H
