/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_MANAGER_PRIVATE_H
#define COWL_MANAGER_PRIVATE_H

#include "cowl_manager.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

struct CowlManager {
    CowlObject super;
    CowlParser parser;
    CowlErrorHandler handler;
    CowlImportLoader loader;
};

COWL_END_DECLS

#endif // COWL_MANAGER_PRIVATE_H
