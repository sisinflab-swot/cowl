/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ERROR_HANDLER_PRIVATE_H
#define COWL_ERROR_HANDLER_PRIVATE_H

#include "cowl_error_handler.h"

COWL_BEGIN_DECLS

#define cowl_error_handler_deinit(HANDLER) do {                                                     \
    if ((HANDLER).free) (HANDLER).free((HANDLER).ctx);                                              \
} while (0)

COWL_END_DECLS

#endif // COWL_ERROR_HANDLER_PRIVATE_H
