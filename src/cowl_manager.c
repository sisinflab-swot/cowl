/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_config_private.h"
#include "cowl_istream_private.h"
#include "cowl_manager_private.h"
#include "cowl_ontology_private.h"
#include "cowl_ostream_private.h"

CowlManager *cowl_manager(void) {
    CowlManager *manager = ulib_alloc(manager);
    if (!manager) return NULL;
    *manager = (CowlManager){
        .super = COWL_OBJECT_INIT(COWL_OT_MANAGER),
        .reader = { 0 },
        .ontos = uvec(CowlObjectPtr),
    };
    return manager;
}

void cowl_manager_free(CowlManager *manager) {
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

static cowl_ret stream_stream(CowlManager *manager, CowlIStream *stream, UIStream *istream) {
    if (!stream) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        return COWL_ERR_MEM;
    }

    if (istream->state) {
        cowl_ret ret = cowl_ret_from_ustream(istream->state);
        cowl_handle_error_code(ret, manager);
        return ret;
    }

    cowl_ret ret = cowl_manager_get_reader(manager).read(istream, stream);
    if (ret) cowl_handle_error_code(ret, manager);
    cowl_release(stream);
    return ret;
}

static cowl_ret stream_stream_deinit(CowlManager *manager, CowlIStream *stream, UIStream *istream) {
    cowl_ret ret = stream_stream(manager, stream, istream);
    ustream_ret s_ret = uistream_deinit(istream);

    if (ret == COWL_OK && s_ret) {
        ret = cowl_ret_from_ustream(s_ret);
        cowl_handle_error_code(ret, manager);
    }

    return ret;
}

static CowlOntology *read_stream_deinit(CowlManager *manager, UIStream *istream) {
    CowlOntology *onto = cowl_ontology(manager);

    if (!onto) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        uistream_deinit(istream);
        return NULL;
    }

    if (stream_stream_deinit(manager, cowl_istream_to_ontology(onto), istream)) {
        cowl_release(onto);
        onto = NULL;
    } else if (cowl_ontology_finalize(onto)) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        cowl_release(onto);
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

CowlOntology *cowl_manager_read_path(CowlManager *manager, UString path) {
    UIStream stream;
    uistream_from_path(&stream, ustring_data(path));
    CowlOntology *onto = read_stream_deinit(manager, &stream);
    if (!onto) handle_path_error(manager, path);
    return onto;
}

CowlOntology *cowl_manager_read_file(CowlManager *manager, FILE *file) {
    UIStream stream;
    uistream_from_file(&stream, file);
    return read_stream_deinit(manager, &stream);
}

CowlOntology *cowl_manager_read_string(CowlManager *manager, UString const *string) {
    UIStream stream;
    uistream_from_ustring(&stream, string);
    return read_stream_deinit(manager, &stream);
}

CowlOntology *cowl_manager_read_stream(CowlManager *manager, UIStream *stream) {
    CowlOntology *onto = cowl_ontology(manager);

    if (!onto) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        return NULL;
    }

    if (stream_stream(manager, cowl_istream_to_ontology(onto), stream)) {
        cowl_release(onto);
        return NULL;
    }

    return onto;
}

cowl_ret cowl_manager_stream_path(CowlManager *manager, CowlIStreamConfig config, UString path) {
    UIStream stream;
    uistream_from_path(&stream, ustring_data(path));
    cowl_ret ret = stream_stream_deinit(manager, cowl_istream(manager, config), &stream);
    if (ret) handle_path_error(manager, path);
    return ret;
}

cowl_ret cowl_manager_stream_file(CowlManager *manager, CowlIStreamConfig config, FILE *file) {
    UIStream stream;
    uistream_from_file(&stream, file);
    return stream_stream_deinit(manager, cowl_istream(manager, config), &stream);
}

cowl_ret
cowl_manager_stream_string(CowlManager *manager, CowlIStreamConfig config, UString const *string) {
    UIStream stream;
    uistream_from_ustring(&stream, string);
    return stream_stream_deinit(manager, cowl_istream(manager, config), &stream);
}

cowl_ret
cowl_manager_stream_stream(CowlManager *manager, CowlIStreamConfig config, UIStream *istream) {
    return stream_stream(manager, cowl_istream(manager, config), istream);
}

static bool onto_stream_handle_import(void *ctx, CowlAny *import_iri) {
    void **c = ctx;
    return (*((cowl_ret *)c[0]) = cowl_istream_push_import(c[1], import_iri)) == COWL_OK;
}

static bool onto_stream_handle_axiom(void *ctx, CowlAny *axiom) {
    void **c = ctx;
    return (*((cowl_ret *)c[0]) = cowl_istream_push_axiom(c[1], axiom)) == COWL_OK;
}

cowl_ret cowl_manager_stream_ontology(CowlManager *manager, CowlIStreamConfig config,
                                      CowlOntology *ontology) {
    CowlIStream *stream = cowl_istream(manager, config);
    if (!stream) return COWL_ERR_MEM;

    cowl_ret ret = COWL_OK;

    if (config.handle_iri || config.handle_version) {
        CowlOntologyId id = cowl_ontology_get_id(ontology);
        if ((ret = cowl_istream_push_iri(stream, id.iri)) ||
            (ret = cowl_istream_push_version(stream, id.version)))
            goto end;
    }

    if (config.handle_annot) {
        CowlVector *annotations = cowl_ontology_get_annot(ontology);
        cowl_vector_foreach (annotations, annot) {
            if ((ret = cowl_istream_push_annot(stream, *annot.item))) goto end;
        }
    }

    if (config.handle_import) {
        void *ctx[] = { &ret, stream };
        CowlIterator iter = { ctx, onto_stream_handle_import };
        if (!cowl_ontology_iterate_import_iris(ontology, &iter, false)) goto end;
    }

    if (config.handle_axiom) {
        void *ctx[] = { &ret, stream };
        CowlIterator iter = { ctx, onto_stream_handle_axiom };
        if (!cowl_ontology_iterate_axioms(ontology, &iter, false)) goto end;
    }

end:
    cowl_release(stream);
    return ret;
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
    cowl_ret ret = cowl_manager_get_writer(manager).write_ontology(stream, ontology);
    if (ret) cowl_handle_error_code(ret, manager);
    return ret;
}

CowlOStream *cowl_manager_open_ostream(CowlManager *manager, UOStream *stream) {
    CowlOStream *ostream = cowl_ostream(manager, stream);

    if (!ostream) {
        cowl_handle_error_code(COWL_ERR_MEM, manager);
        return NULL;
    }

    return ostream;
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

CowlOntology *cowl_manager_get_ontology(CowlManager *manager, CowlOntologyId const *id) {
    if (id) {
        uvec_foreach (CowlObjectPtr, &manager->ontos, onto) {
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
        cowl_release(onto);
        onto = NULL;
    }

    return onto;
}

void cowl_manager_remove_ontology(CowlManager *manager, CowlOntology *onto) {
    uvec_remove(CowlObjectPtr, &manager->ontos, onto);
}
