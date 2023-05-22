/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
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
#if COWL_ENTITY_IDS
    ulib_uint id;
#endif
    CowlIRI *iri;
};

cowl_ret cowl_entity_api_init(void);
void cowl_entity_api_deinit(void);

void cowl_entity_free(CowlAnyEntity *entity);

COWL_END_DECLS

#endif // COWL_ENTITY_PRIVATE_H
