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
#include "cowl_sym_table_private.h"

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

CowlErrorHandler cowl_manager_get_error_handler(CowlManager *manager) {
    return manager->handler.handle_error ? manager->handler : cowl_get_error_handler();
}

CowlImportLoader cowl_manager_get_import_loader(CowlManager *manager) {
    return manager->loader.load_ontology ? manager->loader : cowl_get_import_loader();
}

static CowlOntology *cowl_manager_read_stream_deinit(CowlManager *manager, UIStream *istream) {
    CowlOntology *onto = cowl_manager_read_stream(manager, istream);
    ustream_ret ret = uistream_deinit(istream);

    if (ret) {
        cowl_handle_stream_error(ret, manager);
        cowl_release(onto);
        return NULL;
    }

    return onto;
}

static cowl_ret
cowl_manager_write_stream_deinit(CowlManager *manager, CowlOntology *onto, UOStream *stream) {
    cowl_manager_write_stream(manager, onto, stream);
    ustream_ret ret = uostream_deinit(stream);
    return ret ? cowl_handle_stream_error(ret, manager) : COWL_OK;
}

CowlOntology *cowl_manager_read_path(CowlManager *manager, UString path) {
    UIStream stream;
    uistream_from_path(&stream, ustring_data(path));
    CowlOntology *onto = cowl_manager_read_stream_deinit(manager, &stream);
    if (!onto) cowl_handle_path_error(path, ustring_literal("failed to load ontology"), manager);
    return onto;
}

CowlOntology *cowl_manager_read_file(CowlManager *manager, FILE *file) {
    UIStream stream;
    uistream_from_file(&stream, file);
    return cowl_manager_read_stream_deinit(manager, &stream);
}

CowlOntology *cowl_manager_read_string(CowlManager *manager, UString const *string) {
    UIStream stream;
    uistream_from_ustring(&stream, string);
    return cowl_manager_read_stream_deinit(manager, &stream);
}

CowlOntology *cowl_manager_read_stream(CowlManager *manager, UIStream *istream) {
    if (istream->state) {
        cowl_handle_stream_error(istream->state, manager);
        return NULL;
    }

    CowlIStream *stream = NULL;
    CowlOntology *onto = cowl_ontology(manager);
    if (!onto) goto err_mem;

    stream = cowl_manager_get_istream_to_ontology(manager, onto);
    if (!stream) goto err_mem;
    if (cowl_istream_process_stream(stream, istream)) goto err;
    if (cowl_ontology_finalize(onto)) goto err_mem;

    cowl_release(stream);
    return onto;

err_mem:
    cowl_handle_error_code(COWL_ERR_MEM, manager);

err:
    cowl_release(onto);
    cowl_release(stream);
    return NULL;
}

cowl_ret cowl_manager_write_path(CowlManager *manager, CowlOntology *ontology, UString path) {
    UOStream stream;
    uostream_to_path(&stream, ustring_data(path));
    cowl_ret ret = cowl_manager_write_stream_deinit(manager, ontology, &stream);
    if (ret) cowl_handle_path_error(path, ustring_literal("failed to write ontology"), manager);
    return ret;
}

cowl_ret cowl_manager_write_file(CowlManager *manager, CowlOntology *ontology, FILE *file) {
    UOStream stream;
    uostream_to_file(&stream, file);
    return cowl_manager_write_stream_deinit(manager, ontology, &stream);
}

cowl_ret cowl_manager_write_strbuf(CowlManager *manager, CowlOntology *ontology, UStrBuf *buf) {
    UOStream stream;
    uostream_to_strbuf(&stream, buf);
    return cowl_manager_write_stream_deinit(manager, ontology, &stream);
}

cowl_ret cowl_manager_write_stream(CowlManager *manager, CowlOntology *ontology, UOStream *stream) {
    if (stream->state) return cowl_handle_stream_error(stream->state, manager);
    CowlOStream *ostream = cowl_manager_get_ostream(manager, stream);
    cowl_ret ret = cowl_ostream_write_ontology(ostream, ontology);
    cowl_release(ostream);
    return ret;
}

CowlIStream *cowl_manager_get_istream(CowlManager *manager, CowlIStreamHandlers handlers) {
    CowlSymTable *st = cowl_sym_table();
    CowlIStream *stream = cowl_istream(manager, st, handlers);
    cowl_release(st);
    return stream;
}

static cowl_ret store_iri(void *ctx, CowlIRI *iri) {
    cowl_ontology_set_iri(ctx, iri);
    return COWL_OK;
}

static cowl_ret store_version(void *ctx, CowlIRI *version) {
    cowl_ontology_set_version(ctx, version);
    return COWL_OK;
}

static cowl_ret store_import(void *ctx, CowlIRI *import) {
    return cowl_ontology_add_import(ctx, import);
}

static cowl_ret store_annot(void *ctx, CowlAnnotation *annot) {
    return cowl_ontology_add_annot(ctx, annot);
}

static cowl_ret store_axiom(void *ctx, CowlAnyAxiom *axiom) {
    return cowl_ontology_add_axiom(ctx, axiom);
}

CowlIStream *cowl_manager_get_istream_to_ontology(CowlManager *manager, CowlOntology *ontology) {
    CowlIStreamHandlers handlers = {
        .ctx = ontology,
        .iri = store_iri,
        .version = store_version,
        .import = store_import,
        .annot = store_annot,
        .axiom = store_axiom,
    };
    return cowl_istream(manager, ontology->st, handlers);
}

CowlOStream *cowl_manager_get_ostream(CowlManager *manager, UOStream *stream) {
    return cowl_ostream(manager, stream);
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
