/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_EDITOR_PRIVATE_H
#define COWL_EDITOR_PRIVATE_H

#include "cowl_editor.h"
#include "cowl_sym_table_private.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlManager);

typedef struct CowlEditor {
    CowlSymTable st;
    CowlOntology *ontology;
    void *state;
} CowlEditor;

CowlEditor* cowl_editor_alloc(void);
void cowl_editor_free(CowlEditor *editor);
void cowl_editor_set_ontology(CowlEditor *editor, CowlOntology *ontology);

COWL_END_DECLS

#endif // COWL_EDITOR_PRIVATE_H
