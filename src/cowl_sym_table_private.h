/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SYM_TABLE_PRIVATE_H
#define COWL_SYM_TABLE_PRIVATE_H

#include "cowl_sym_table.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlTable);

struct CowlSymTable {
    CowlTable *prefix_ns_map;
    CowlTable *ns_prefix_map;
};

CowlSymTable cowl_sym_table_init(void);
void cowl_sym_table_deinit(CowlSymTable *st);

COWL_END_DECLS

#endif // COWL_SYM_TABLE_PRIVATE_H
