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
#include "cowl_set.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlManager);

typedef struct CowlEditor {
    CowlManager *manager;
    CowlOntology *ontology;
    void *state;
    UHash(CowlObjectTable) prefix_ns_map;
    UHash(CowlObjectTable) anon_ind_map;
    UString description;
} CowlEditor;

CowlEditor* cowl_editor_alloc(CowlManager *manager);
void cowl_editor_free(CowlEditor *editor);

CowlOntology* cowl_editor_get_ontology(CowlEditor *editor);
void cowl_editor_set_ontology(CowlEditor *editor, CowlOntology *ontology);

void cowl_editor_handle_stream_error(CowlEditor *editor, ustream_ret code);

COWL_END_DECLS

#endif // COWL_EDITOR_PRIVATE_H
