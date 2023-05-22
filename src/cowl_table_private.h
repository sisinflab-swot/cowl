/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_TABLE_PRIVATE_H
#define COWL_TABLE_PRIVATE_H

#include "cowl_object_private.h"
#include "cowl_table.h"

COWL_BEGIN_DECLS

struct CowlTable {
    CowlObject super;
    UHash(CowlObjectTable) data;
};

UHash(CowlObjectTable) cowl_primitive_map(void);
UHash(CowlObjectTable) cowl_string_map(void);

void cowl_table_free(CowlTable *table);
void cowl_table_release_ex(CowlTable *table, bool release_elements);
bool cowl_table_iterate_primitives(CowlTable *table, CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_TABLE_PRIVATE_H
