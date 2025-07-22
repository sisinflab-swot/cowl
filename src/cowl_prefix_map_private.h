/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PREFIX_MAP_PRIVATE_H
#define COWL_PREFIX_MAP_PRIVATE_H

#include "cowl_attrs.h"
#include "cowl_object_private.h"
#include "cowl_prefix_map.h" // IWYU pragma: export
#include "cowl_utils.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlTable);

struct CowlPrefixMap {
    CowlObject super;
    CowlTable *prefix_ns;
    CowlTable *ns_prefix;
};

CowlPrefixMap *cowl_prefix_map(void);
void cowl_prefix_map_free(CowlPrefixMap *map);

COWL_END_DECLS

#endif // COWL_PREFIX_MAP_PRIVATE_H
