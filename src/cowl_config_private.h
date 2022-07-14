/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CONFIG_PRIVATE_H
#define COWL_CONFIG_PRIVATE_H

#include "cowl_config.h"

COWL_BEGIN_DECLS

CowlErrorHandler cowl_api_get_error_handler(void);
CowlImportLoader cowl_api_get_import_loader(void);
CowlParser cowl_api_get_parser(void);
CowlWriter cowl_api_get_writer(void);

COWL_END_DECLS

#endif // COWL_CONFIG_PRIVATE_H
