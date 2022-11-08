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
#include "cowl_ontology_private.h"
#include "cowl_stream_private.h"

CowlManager* cowl_manager(void) {
    CowlManager *manager = ulib_alloc(manager);
    if (!manager) return NULL;
    *manager = (CowlManager){
        .super = COWL_OBJECT_INIT(COWL_OT_MANAGER),
        .reader = {0},
        .ontos = uvec(CowlObjectPtr)
    };
    return manager;
}

void cowl_manager_release(CowlManager *manager) {
    if (!manager || cowl_object_decr_ref(manager)) return;
    if (manager->loader.free) manager->loader.free(manager->loader.ctx);
    if (manager->handler.free) manager->handler.free(manager->handler.ctx);
    uvec_deinit(CowlObjectPtr, &manager->ontos);
    ulib_free(manager);
}

CowlReader cowl_manager_get_reader(CowlManager *manager) {
    return manager->reader.name ? manager->reader : cowl_get_reader();
}

CowlWriter cowl_manager_get_writer(CowlManager *manager) {
    return manager->writer.name ? manager->writer : cowl_get_writer();
}

static cowl_ret stream_stream(CowlManager *manager, CowlStream *stream, UIStream *istream) {
    if (!stream) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        return COWL_ERR_MEM;
    }

    if (istream->state) {
        cowl_ret ret = cowl_ret_from_ustream(istream->state);
        cowl_handle_error_code(ret, manager);
        return ret;
    }

    CowlReader reader = cowl_manager_get_reader(manager);
    void *state = NULL;
    cowl_ret ret = COWL_ERR_MEM;

    if (reader.alloc && !(state = reader.alloc())) goto end;
    ret = reader.read(state, istream, stream);

end:
    if (reader.free) reader.free(state);
    if (ret) cowl_handle_error_code(ret, manager);
    return ret;
}

static cowl_ret stream_stream_deinit(CowlManager *manager, CowlStream *stream, UIStream *istream) {
    cowl_ret ret = stream_stream(manager, stream, istream);
    ustream_ret s_ret = uistream_deinit(istream);

    if (ret == COWL_OK && s_ret) {
        ret = cowl_ret_from_ustream(s_ret);
        cowl_handle_error_code(ret, manager);
    }

    cowl_stream_release(stream);
    return ret;
}

static CowlOntology* read_stream_deinit(CowlManager *manager, UIStream *istream) {
    CowlOntology *onto = cowl_ontology(manager);

    if (!onto) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        uistream_deinit(istream);
        return NULL;
    }

    if (stream_stream_deinit(manager, cowl_stream_ontology_get(onto), istream)) {
        cowl_ontology_release(onto);
        onto = NULL;
    } else if (cowl_ontology_finalize(onto)) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        cowl_ontology_release(onto);
        onto = NULL;
    }

    return onto;
}

static cowl_ret write_stream_deinit(CowlManager *manager, CowlOntology *onto, UOStream *stream) {
    cowl_ret ret;

    if (stream->state) {
        ret = cowl_ret_from_ustream(stream->state);
        cowl_handle_error_code(ret, manager);
        uostream_deinit(stream);
        return ret;
    }

    ret = cowl_manager_write_stream(manager, onto, stream);
    ustream_ret s_ret = uostream_deinit(stream);

    if (ret == COWL_OK && s_ret) {
        ret = cowl_ret_from_ustream(s_ret);
        cowl_handle_error_code(ret, manager);
    }

    return ret;
}

static void handle_path_error(CowlManager *manager, UString path) {
    UString comp[] = { ustring_literal("failed to load ontology "), path };
    UString desc = ustring_concat(comp, ulib_array_count(comp));
    cowl_handle_error(COWL_ERR, desc, manager);
    ustring_deinit(&desc);
}

CowlOntology* cowl_manager_read_path(CowlManager *manager, UString path) {
    UIStream stream;
    uistream_from_path(&stream, ustring_data(path));
    CowlOntology *onto = read_stream_deinit(manager, &stream);
    if (!onto) handle_path_error(manager, path);
    return onto;
}

CowlOntology* cowl_manager_read_file(CowlManager *manager, FILE *file) {
    UIStream stream;
    uistream_from_file(&stream, file);
    return read_stream_deinit(manager, &stream);
}

CowlOntology* cowl_manager_read_string(CowlManager *manager, UString const *string) {
    UIStream stream;
    uistream_from_ustring(&stream, string);
    return read_stream_deinit(manager, &stream);
}

CowlOntology* cowl_manager_read_stream(CowlManager *manager, UIStream *stream) {
    CowlOntology *onto = cowl_ontology(manager);

    if (!onto) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        return NULL;
    }

    if (stream_stream(manager, cowl_stream_ontology_get(onto), stream)) {
        cowl_ontology_release(onto);
        return NULL;
    }

    return onto;
}

cowl_ret cowl_manager_stream_path(CowlManager *manager, CowlStreamConfig config, UString path) {
    UIStream stream;
    uistream_from_path(&stream, ustring_data(path));
    cowl_ret ret = stream_stream_deinit(manager, cowl_stream_get(manager, config), &stream);
    if (ret) handle_path_error(manager, path);
    return ret;
}

cowl_ret cowl_manager_stream_file(CowlManager *manager, CowlStreamConfig config, FILE *file) {
    UIStream stream;
    uistream_from_file(&stream, file);
    return stream_stream_deinit(manager, cowl_stream_get(manager, config), &stream);
}

cowl_ret cowl_manager_stream_string(CowlManager *manager, CowlStreamConfig config,
                                    UString const *string) {
    UIStream stream;
    uistream_from_ustring(&stream, string);
    return stream_stream_deinit(manager, cowl_stream_get(manager, config), &stream);
}

cowl_ret cowl_manager_stream_stream(CowlManager *manager, CowlStreamConfig config,
                                    UIStream *istream) {
    return stream_stream(manager, cowl_stream_get(manager, config), istream);
}

cowl_ret cowl_manager_write_path(CowlManager *manager, CowlOntology *ontology, UString path) {
    UOStream stream;
    uostream_to_path(&stream, ustring_data(path));

    cowl_ret ret = write_stream_deinit(manager, ontology, &stream);

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
    return write_stream_deinit(manager, ontology, &stream);
}

cowl_ret cowl_manager_write_strbuf(CowlManager *manager, CowlOntology *ontology, UStrBuf *buf) {
    UOStream stream;
    uostream_to_strbuf(&stream, buf);
    return write_stream_deinit(manager, ontology, &stream);
}

cowl_ret cowl_manager_write_stream(CowlManager *manager, CowlOntology *ontology, UOStream *stream) {
    cowl_ret ret = COWL_ERR_MEM;
    CowlWriter writer = cowl_manager_get_writer(manager);
    void *state = NULL;

    if (writer.alloc && !(state = writer.alloc())) goto end;
    ret = writer.write_ontology(state, stream, ontology);

end:
    if (writer.free) writer.free(state);
    if (ret) cowl_handle_error_code(ret, manager);
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
        uvec_foreach(CowlObjectPtr, &manager->ontos, onto) {
            if (cowl_ontology_id_equals(cowl_ontology_get_id(*onto.item), *id)) {
                return *onto.item;
            }
        }
    }

    CowlOntology *onto = cowl_ontology(manager);
    if (!onto) return NULL;

    if (id) {
        cowl_ontology_set_iri(onto, id->iri);
        cowl_ontology_set_version(onto, id->version);
    }

    if (uvec_push(CowlObjectPtr, &manager->ontos, onto)) {
        cowl_ontology_release(onto);
        onto = NULL;
    }

    return onto;
}

void cowl_manager_remove_ontology(CowlManager *manager, CowlOntology *onto) {
    uvec_remove(CowlObjectPtr, &manager->ontos, onto);
}
