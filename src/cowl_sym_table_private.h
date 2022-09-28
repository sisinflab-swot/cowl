/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SYM_TABLE_PRIVATE_H
#define COWL_SYM_TABLE_PRIVATE_H

#include "cowl_sym_table.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlTable);

typedef struct CowlSymTable {
    CowlTable *onto_import_map;
    CowlTable *import_onto_map;
    CowlTable *prefix_ns_map;
    CowlTable *ns_prefix_map;
    CowlTable *id_anon_map;
    CowlTable *anon_id_map;
} CowlSymTable;

CowlSymTable cowl_sym_table_init(void);
void cowl_sym_table_deinit(CowlSymTable *st);

cowl_ret cowl_sym_table_pop_import(CowlSymTable *st, CowlIRI *iri, CowlOntology **import);

COWL_END_DECLS

#endif // COWL_SYM_TABLE_PRIVATE_H
