/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CONFIG_PRIVATE_H
#define COWL_CONFIG_PRIVATE_H

#include "cowl_config.h"

COWL_BEGIN_DECLS

COWL_PURE CowlErrorHandler cowl_get_error_handler(void);
COWL_PURE CowlImportLoader cowl_get_import_loader(void);
COWL_PURE CowlReader cowl_get_reader(void);
COWL_PURE CowlWriter cowl_get_writer(void);

COWL_END_DECLS

#endif // COWL_CONFIG_PRIVATE_H
