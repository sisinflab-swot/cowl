/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_manager_private.h"
#include "cowl_config_private.h"
#include "cowl_editor_private.h"
#include "cowl_error_handler_private.h"
#include "cowl_import_loader_private.h"
#include "cowl_ontology_private.h"

CowlManager* cowl_manager_get(void) {
    CowlManager *manager = ulib_alloc(manager);
    if (!manager) return NULL;
    *manager = (CowlManager){
        .super = COWL_OBJECT_INIT(COWL_OT_MANAGER),
        .parser = {0},
        .editors = uvec_init(ulib_ptr)
    };
    return manager;
}

void cowl_manager_release(CowlManager *manager) {
    if (manager && !cowl_object_decr_ref(manager)) {
        cowl_import_loader_deinit(manager->loader);
        cowl_error_handler_deinit(manager->handler);
        uvec_foreach(ulib_ptr, &manager->editors, editor) {
            cowl_editor_free(*editor.item);
        }
        ulib_free(manager);
    }
}

static CowlEditor* cowl_ensure_editor(CowlManager *manager, CowlOntologyId const *id) {
    CowlEditor *ret = NULL;

    if (id) {
        uvec_foreach(ulib_ptr, &manager->editors, editor) {
            CowlOntology *onto = ((CowlEditor *)*editor.item)->ontology;
            if (cowl_ontology_id_equals(*id, cowl_ontology_get_id(onto))) {
                return *editor.item;
            }
        }
    }

    ret = cowl_editor_alloc(manager);
    if (!ret) goto err;

    CowlOntology *ontology = cowl_ontology_get();
    if (!ontology) goto err;

    cowl_editor_set_ontology(ret, ontology);
    cowl_ontology_release(ontology);

    if (id) {
        if (id->ontology_iri) cowl_editor_set_iri(ret, id->ontology_iri);
        if (id->version_iri) cowl_editor_set_version(ret, id->version_iri);
    }

    if (uvec_push(ulib_ptr, &manager->editors, ret) != UVEC_OK) goto err;
    return ret;

err:
    {
        CowlEditor temp_editor = {.manager = manager};
        cowl_editor_handle_error_type(&temp_editor, COWL_ERR_MEM);
        cowl_editor_free(ret);
        return NULL;
    }
}

CowlParser cowl_manager_get_parser(CowlManager *manager) {
    return manager->parser.name ? manager->parser : cowl_api_get_parser();
}

static CowlEditor* cowl_read_stream(CowlManager *manager, UIStream *stream, UString desc) {
    if (!(manager && stream)) return NULL;

    CowlEditor *editor = cowl_ensure_editor(manager, NULL);
    if (!editor) return NULL;
    editor->description = desc;

    CowlParser parser = cowl_manager_get_parser(editor->manager);

    if (parser.alloc && !(editor->state = parser.alloc())) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
        return NULL;
    }

    if (parser.parse(editor->state, stream, editor)) {
        goto err;
    }

    if (cowl_ontology_finalize(editor->ontology)) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
        goto err;
    }

    if (parser.free) parser.free(editor->state);
    editor->state = NULL;

    return editor;

err:
    if (parser.free) parser.free(editor->state);
    editor->state = NULL;
    return NULL;
}

static CowlOntology* cowl_read_stream_deinit(CowlManager *manager, UIStream *stream, UString desc) {
    if (stream->state) {
        CowlEditor temp = { .manager = manager, .description = desc };
        cowl_editor_handle_stream_error(&temp, stream->state);
        uistream_deinit(stream);
        return NULL;
    }

    CowlEditor *editor = cowl_read_stream(manager, stream, desc);
    ustream_ret ret = uistream_deinit(stream);
    if (!editor) return NULL;

    if (ret) cowl_editor_handle_stream_error(editor, ret);
    return cowl_editor_get_ontology(editor);
}

CowlOntology* cowl_manager_read_stream(CowlManager *manager, UIStream *stream) {
    CowlEditor *editor = cowl_read_stream(manager, stream, ustring_empty);
    return editor ? cowl_editor_get_ontology(editor) : NULL;
}

CowlOntology* cowl_manager_read_path(CowlManager *manager, UString path) {
    UIStream stream;
    uistream_from_path(&stream, ustring_data(path));
    return cowl_read_stream_deinit(manager, &stream, path);
}

CowlOntology* cowl_manager_read_file(CowlManager *manager, FILE *file) {
    UIStream stream;
    uistream_from_file(&stream, file);
    return cowl_read_stream_deinit(manager, &stream, ustring_empty);
}

CowlOntology* cowl_manager_read_string(CowlManager *manager, UString const *string) {
    UIStream stream;
    uistream_from_ustring(&stream, string);
    return cowl_read_stream_deinit(manager, &stream, ustring_empty);
}

void cowl_manager_set_parser(CowlManager *manager, CowlParser parser) {
    manager->parser = parser;
}

void cowl_manager_set_import_loader(CowlManager *manager, CowlImportLoader loader) {
    manager->loader = loader;
}

void cowl_manager_set_error_handler(CowlManager *manager, CowlErrorHandler handler) {
    manager->handler = handler;
}

CowlEditor* cowl_manager_get_editor(CowlManager *manager, CowlOntology *ontology) {
    uvec_foreach(ulib_ptr, &manager->editors, editor) {
        if (cowl_ontology_equals(ontology, ((CowlEditor *)*editor.item)->ontology)) {
            return *editor.item;
        }
    }
    return NULL;
}

CowlOntology* cowl_manager_get_ontology(CowlManager *manager, CowlOntologyId const *id) {
    CowlEditor *editor = cowl_ensure_editor(manager, id);
    return editor ? cowl_editor_get_ontology(editor) : NULL;
}
