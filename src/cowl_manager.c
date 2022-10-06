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
#include "cowl_error_handler_private.h"
#include "cowl_import_loader_private.h"
#include "cowl_ontology_private.h"

CowlManager* cowl_manager(void) {
    CowlManager *manager = ulib_alloc(manager);
    if (!manager) return NULL;
    *manager = (CowlManager){
        .super = COWL_OBJECT_INIT(COWL_OT_MANAGER),
        .reader = {0},
        .ontos = uvec(ulib_ptr)
    };
    return manager;
}

void cowl_manager_release(CowlManager *manager) {
    if (!manager || cowl_object_decr_ref(manager)) return;
    cowl_import_loader_deinit(manager->loader);
    cowl_error_handler_deinit(manager->handler);
    uvec_deinit(ulib_ptr, &manager->ontos);
    ulib_free(manager);
}

CowlReader cowl_manager_get_reader(CowlManager *manager) {
    return manager->reader.name ? manager->reader : cowl_get_reader();
}

CowlWriter cowl_manager_get_writer(CowlManager *manager) {
    return manager->writer.name ? manager->writer : cowl_get_writer();
}

static CowlOntology* cowl_read_stream_deinit(CowlManager *manager, UIStream *stream) {
    if (stream->state) {
        cowl_handle_stream_error(stream->state, manager);
        uistream_deinit(stream);
        return NULL;
    }

    CowlOntology *onto = cowl_manager_read_stream(manager, stream);
    ustream_ret ret = uistream_deinit(stream);
    if (!onto) return NULL;

    if (ret) cowl_handle_stream_error(ret, manager);
    return onto;
}

static cowl_ret cowl_write_stream_deinit(CowlManager *manager, CowlOntology *onto,
                                         UOStream *stream) {
    if (stream->state) {
        cowl_ret ret = cowl_ret_from_ustream(stream->state);
        cowl_handle_error_code(ret, manager);
        uostream_deinit(stream);
        return ret;
    }

    cowl_ret ret = cowl_manager_write_stream(manager, onto, stream);
    ustream_ret sret = uostream_deinit(stream);

    if (ret) cowl_handle_error_code(ret, manager);
    if (sret) cowl_handle_stream_error(sret, manager);

    return ret || sret ? COWL_ERR : COWL_OK;
}

CowlOntology* cowl_manager_read_path(CowlManager *manager, UString path) {
    UIStream stream;
    uistream_from_path(&stream, ustring_data(path));

    CowlOntology *onto = cowl_read_stream_deinit(manager, &stream);

    if (!onto) {
        UString comp[] = { ustring_literal("failed to load ontology "), path };
        UString desc = ustring_concat(comp, ulib_array_count(comp));
        cowl_handle_error(COWL_ERR, desc, manager);
        ustring_deinit(&desc);
    }

    return onto;
}

CowlOntology* cowl_manager_read_file(CowlManager *manager, FILE *file) {
    UIStream stream;
    uistream_from_file(&stream, file);
    return cowl_read_stream_deinit(manager, &stream);
}

CowlOntology* cowl_manager_read_string(CowlManager *manager, UString const *string) {
    UIStream stream;
    uistream_from_ustring(&stream, string);
    return cowl_read_stream_deinit(manager, &stream);
}

CowlOntology* cowl_manager_read_stream(CowlManager *manager, UIStream *stream) {
    if (!(manager && stream)) return NULL;

    CowlReader reader = cowl_manager_get_reader(manager);

    void *state = NULL;

    if (reader.alloc && !(state = reader.alloc())) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        return NULL;
    }

    bool success = false;
    CowlOntology *onto = cowl_ontology(manager);

    if (!onto) goto err;
    if (reader.read(state, stream, onto)) goto err;
    if (cowl_ontology_finalize(onto)) goto err;

    success = true;

err:
    if (reader.free) reader.free(state);
    if (success && uvec_push(ulib_ptr, &manager->ontos, onto)) success = false;

    if (!success) {
        cowl_ontology_release(onto);
        onto = NULL;
    }

    return onto;
}

cowl_ret cowl_manager_write_path(CowlManager *manager, CowlOntology *ontology, UString path) {
    UOStream stream;
    uostream_to_path(&stream, ustring_data(path));

    cowl_ret ret = cowl_write_stream_deinit(manager, ontology, &stream);

    if (ret) {
        UString comp[] = { ustring_literal("failed to write ontology "), path };
        UString desc = ustring_concat(comp, ulib_array_count(comp));
        cowl_handle_error(ret, desc, manager);
        ustring_deinit(&desc);
    }

    return ret;
}

cowl_ret cowl_manager_write_file(CowlManager *manager, CowlOntology *ontology, FILE *file) {
    UOStream stream;
    uostream_to_file(&stream, file);
    return cowl_write_stream_deinit(manager, ontology, &stream);
}

cowl_ret cowl_manager_write_strbuf(CowlManager *manager, CowlOntology *ontology, UStrBuf *buf) {
    UOStream stream;
    uostream_to_strbuf(&stream, buf);
    return cowl_write_stream_deinit(manager, ontology, &stream);
}

cowl_ret cowl_manager_write_stream(CowlManager *manager, CowlOntology *ontology, UOStream *stream) {
    if (!(manager && stream && ontology)) return COWL_ERR;

    CowlWriter writer = cowl_manager_get_writer(manager);
    void *state = NULL;

    if (writer.alloc && !(state = writer.alloc())) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        return COWL_ERR_MEM;
    }

    cowl_ret ret = writer.write_ontology(state, stream, ontology);
    if (writer.free) writer.free(state);

    return ret;
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

CowlOntology* cowl_manager_get_ontology(CowlManager *manager, CowlOntologyId const *id) {
    if (id) {
        uvec_foreach(ulib_ptr, &manager->ontos, onto) {
            if (cowl_ontology_id_equals(cowl_ontology_get_id(*onto.item), *id)) {
                return *onto.item;
            }
        }
    }

    CowlOntology *onto = cowl_ontology(manager);

    if (!onto) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        return NULL;
    }

    if (id) {
        cowl_ontology_set_iri(onto, id->iri);
        cowl_ontology_set_version(onto, id->version);
    }

    if (uvec_push(ulib_ptr, &manager->ontos, onto)) {
        cowl_ontology_release(onto);
        onto = NULL;
    }

    return onto;
}

void cowl_manager_remove_ontology(CowlManager *manager, CowlOntology *onto) {
    uvec_remove(ulib_ptr, &manager->ontos, onto);
}
