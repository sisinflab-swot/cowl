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
        .reader = {0},
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
        uvec_deinit(ulib_ptr, &manager->editors);
        ulib_free(manager);
    }
}

static CowlEditor* cowl_ensure_editor(CowlManager *manager, CowlOntology *onto,
                                      CowlOntologyId const *id) {
    CowlEditor *editor = NULL;

    if (onto) {
        editor = cowl_manager_get_editor(manager, onto);
        if (editor) return editor;
    } else if (id) {
        uvec_foreach(ulib_ptr, &manager->editors, e) {
            CowlOntology *o = ((CowlEditor *)*e.item)->ontology;
            if (cowl_ontology_id_equals(*id, cowl_ontology_get_id(o))) {
                return *e.item;
            }
        }
    }

    editor = cowl_editor_alloc(manager);
    if (!editor) goto err;

    if (onto) {
        cowl_editor_set_ontology(editor, onto);
    } else {
        onto = cowl_ontology_get();
        if (!onto) goto err;

        if (id) {
            if (id->iri) cowl_editor_set_iri(editor, id->iri);
            if (id->version) cowl_editor_set_version(editor, id->version);
        }

        cowl_editor_set_ontology(editor, onto);
        cowl_ontology_release(onto);
    }

    if (uvec_push(ulib_ptr, &manager->editors, editor) != UVEC_OK) goto err;

    return editor;

err:
    {
        CowlEditor temp_editor = { .manager = manager };
        cowl_editor_handle_error_type(&temp_editor, COWL_ERR_MEM);
        cowl_editor_free(editor);
        return NULL;
    }
}

CowlReader cowl_manager_get_reader(CowlManager *manager) {
    return manager->reader.name ? manager->reader : cowl_api_get_reader();
}

CowlWriter cowl_manager_get_writer(CowlManager *manager) {
    return manager->writer.name ? manager->writer : cowl_api_get_writer();
}

static CowlEditor* cowl_read_stream(CowlManager *manager, UIStream *stream, UString desc) {
    if (!(manager && stream)) return NULL;

    CowlEditor *editor = cowl_ensure_editor(manager, NULL, NULL);
    if (!editor) return NULL;
    editor->description = desc;

    CowlReader reader = cowl_manager_get_reader(manager);

    if (reader.alloc && !(editor->state = reader.alloc())) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
        return NULL;
    }

    bool success = true;

    if (reader.read(editor->state, stream, editor)) {
        success = false;
        goto err;
    }

    if (cowl_ontology_finalize(editor->ontology)) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
        success = false;
        goto err;
    }

err:
    if (reader.free) reader.free(editor->state);
    editor->state = NULL;
    editor->description = ustring_empty;

    return success ? editor : NULL;
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
    return cowl_ontology_retain(editor->ontology);
}

static CowlEditor* cowl_write_stream(CowlManager *manager, CowlOntology *onto, UOStream *stream,
                                     UString desc) {
    if (!(manager && stream && onto)) return NULL;

    CowlEditor *editor = cowl_ensure_editor(manager, onto, NULL);
    if (!editor) return NULL;
    editor->description = desc;

    CowlWriter writer = cowl_manager_get_writer(manager);

    if (writer.alloc && !(editor->state = writer.alloc())) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
        return NULL;
    }

    cowl_ret ret = writer.write_ontology(editor->state, stream, editor);
    if (writer.free) writer.free(editor->state);
    editor->state = NULL;
    editor->description = ustring_empty;

    return ret ? NULL : editor;
}

static cowl_ret cowl_write_stream_deinit(CowlManager *manager, CowlOntology *onto, UOStream *stream,
                                         UString desc) {
    if (stream->state) {
        CowlEditor temp = { .manager = manager, .description = desc };
        cowl_editor_handle_stream_error(&temp, stream->state);
        uostream_deinit(stream);
        return cowl_ret_from_ustream(stream->state);
    }

    CowlEditor *editor = cowl_write_stream(manager, onto, stream, desc);
    ustream_ret sret = uostream_deinit(stream);
    if (sret) cowl_editor_handle_stream_error(editor, sret);
    return !editor || sret ? COWL_ERR : COWL_OK;
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

CowlOntology* cowl_manager_read_stream(CowlManager *manager, UIStream *stream) {
    CowlEditor *editor = cowl_read_stream(manager, stream, ustring_empty);
    return editor && editor->ontology ? cowl_ontology_retain(editor->ontology) : NULL;
}

cowl_ret cowl_manager_write_path(CowlManager *manager, CowlOntology *ontology, UString path) {
    UOStream stream;
    uostream_to_path(&stream, ustring_data(path));
    return cowl_write_stream_deinit(manager, ontology, &stream, path);
}

cowl_ret cowl_manager_write_file(CowlManager *manager, CowlOntology *ontology, FILE *file) {
    UOStream stream;
    uostream_to_file(&stream, file);
    return cowl_write_stream_deinit(manager, ontology, &stream, ustring_empty);
}

cowl_ret cowl_manager_write_strbuf(CowlManager *manager, CowlOntology *ontology, UStrBuf *buf) {
    UOStream stream;
    uostream_to_strbuf(&stream, buf);
    return cowl_write_stream_deinit(manager, ontology, &stream, ustring_empty);
}

cowl_ret cowl_manager_write_stream(CowlManager *manager, CowlOntology *ontology, UOStream *stream) {
    return cowl_write_stream(manager, ontology, stream, ustring_empty) ? COWL_OK : COWL_ERR;
}

void cowl_manager_set_reader(CowlManager *manager, CowlReader reader) {
    manager->reader = reader;
}

void cowl_manager_set_writer(CowlManager *manager, CowlWriter writer) {
    manager->writer = writer;
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
    CowlEditor *editor = cowl_ensure_editor(manager, NULL, id);
    return editor && editor->ontology ? cowl_ontology_retain(editor->ontology) : NULL;
}
