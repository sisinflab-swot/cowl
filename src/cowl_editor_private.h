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
#include "cowl_table.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlManager);

typedef struct CowlEditor {
    UString description;
    CowlManager *manager;
    CowlOntology *ontology;
    CowlTable *onto_import_map;
    CowlTable *import_onto_map;
    CowlTable *prefix_ns_map;
    CowlTable *ns_prefix_map;
    CowlTable *id_anon_map;
    CowlTable *anon_id_map;
    void *state;
} CowlEditor;

CowlEditor* cowl_editor_alloc(CowlManager *manager);
void cowl_editor_free(CowlEditor *editor);

void cowl_editor_set_ontology(CowlEditor *editor, CowlOntology *ontology);
void cowl_editor_handle_stream_error(CowlEditor *editor, ustream_ret code);

COWL_END_DECLS

#endif // COWL_EDITOR_PRIVATE_H
