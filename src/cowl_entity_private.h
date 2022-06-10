/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ENTITY_PRIVATE_H
#define COWL_ENTITY_PRIVATE_H

#include "cowl_entity.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

struct CowlEntity {
    CowlObject super;
    CowlIRI *iri;
};

cowl_ret cowl_entity_api_init(void);
void cowl_entity_api_deinit(void);

COWL_END_DECLS

#endif // COWL_ENTITY_PRIVATE_H
