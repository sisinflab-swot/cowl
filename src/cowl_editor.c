/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_editor_private.h"
#include "cowl_config_private.h"
#include "cowl_iri.h"
#include "cowl_manager_private.h"
#include "cowl_ontology_private.h"
#include "cowl_table_private.h"

CowlEditor* cowl_editor_alloc(void) {
    CowlEditor *editor = ulib_alloc(editor);
    if (!editor) return NULL;
    *editor = (CowlEditor) { .st = cowl_sym_table_init() };
    return editor;
}

void cowl_editor_free(CowlEditor *editor) {
    if (!editor) return;
    cowl_sym_table_deinit(&editor->st);
    cowl_ontology_release(editor->ontology);
    ulib_free(editor);
}

CowlOntology* cowl_editor_get_ontology(CowlEditor *editor) {
    return editor->ontology;
}

CowlSymTable* cowl_editor_get_sym_table(CowlEditor *editor) {
    return &editor->st;
}

void cowl_editor_set_ontology(CowlEditor *editor, CowlOntology *ontology) {
    if (editor->ontology) cowl_ontology_release(editor->ontology);
    editor->ontology = cowl_ontology_retain(ontology);
}

void cowl_editor_set_iri(CowlEditor *editor, CowlIRI *iri) {
    cowl_ontology_set_iri(editor->ontology, iri);
}

void cowl_editor_set_version(CowlEditor *editor, CowlIRI *version) {
    cowl_ontology_set_version(editor->ontology, version);
}

cowl_ret cowl_editor_add_annot(CowlEditor *editor, CowlAnnotation *annot) {
    cowl_ret ret = cowl_ontology_add_annot(editor->ontology, annot);
    if (ret) cowl_handle_error_code(ret, editor->ontology);
    return ret;
}

cowl_ret cowl_editor_remove_annot(CowlEditor *editor, CowlAnnotation *annot) {
    cowl_ontology_remove_annot(editor->ontology, annot);
    return COWL_OK;
}

cowl_ret cowl_editor_add_import(CowlEditor *editor, CowlIRI *iri) {
    cowl_ret ret = COWL_OK;

    if (!iri) {
        ret = COWL_ERR_MEM;
        goto end;
    }

    CowlOntology *import = NULL;
    CowlImportLoader loader = editor->ontology->manager->loader;
    if (!loader.load_ontology) loader = cowl_get_import_loader();

    if (loader.load_ontology) {
        if ((import = loader.load_ontology(loader.ctx, iri))) {
            ret = cowl_ontology_add_import(editor->ontology, import);
            cowl_ontology_release(import);
        } else {
            ret = COWL_ERR_IMPORT;
        }
    }

    if (!import) goto end;

    CowlTable *table = cowl_sym_table_get_onto_iri_map(&editor->st, false);
    if (!table) {
        ret = COWL_ERR_MEM;
        goto end;
    }

    uhash_ret lret = uhmap_add(CowlObjectTable, &table->data, import, iri, NULL);
    if (lret == UHASH_ERR) {
        ret = COWL_ERR_MEM;
    } else if (lret == UHASH_INSERTED) {
        cowl_ontology_retain(import);
        cowl_iri_retain(iri);
    }

end:
    if (ret) cowl_handle_error_code(ret, editor->ontology);
    return ret;
}

cowl_ret cowl_editor_remove_import(CowlEditor *editor, CowlIRI *iri) {
    CowlOntology *import = NULL;
    cowl_ret ret = cowl_sym_table_pop_import(&editor->st, iri, &import);
    if (ret) return ret;

    cowl_ontology_remove_import(editor->ontology, import);
    cowl_ontology_release(import);

    return COWL_OK;
}

cowl_ret cowl_editor_add_axiom(CowlEditor *editor, CowlAxiom *axiom) {
    if (!axiom) {
        cowl_handle_error_code(COWL_ERR_MEM, editor->ontology);
        return COWL_ERR_MEM;
    }

    cowl_ret ret = cowl_ontology_add_axiom(editor->ontology, axiom);

    if (ret) {
        cowl_handle_error_code(ret, editor->ontology);
        return ret;
    }

    return COWL_OK;
}

cowl_ret cowl_editor_remove_axiom(CowlEditor *editor, CowlAxiom *axiom) {
    cowl_ontology_remove_axiom(editor->ontology, axiom);
    return COWL_OK;
}
