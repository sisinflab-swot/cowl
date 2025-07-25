/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_any.h"
#include "cowl_error_handler.h"
#include "cowl_istream.h"
#include "cowl_istream_handlers.h"
#include "cowl_istream_private.h"
#include "cowl_iterator.h"
#include "cowl_manager_private.h"
#include "cowl_object.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_ontology.h"
#include "cowl_ontology_private.h"
#include "cowl_ostream.h"
#include "cowl_ostream_private.h"
#include "cowl_prefix_map_private.h"
#include "cowl_reader.h"
#include "cowl_ret.h"
#include "cowl_vector.h"
#include "cowl_writer.h"
#include "ulib.h"
#include <stdio.h>

static CowlManager *root_manager = NULL;

static CowlManager *cowl_manager_alloc(void) {
    CowlManager *manager = ulib_alloc(manager);
    if (!manager) return NULL;
    *manager = (CowlManager){
        .super = COWL_OBJECT_INIT(COWL_OT_MANAGER),
        .ontos = uvec(CowlObjectPtr),
    };
    return manager;
}

void cowl_manager_free(CowlManager *manager) {
    cowl_release(manager->parent);
    cowl_release(manager->pm);
    cowl_reader_free_ctx(&manager->reader);
    cowl_writer_free_ctx(&manager->writer);
    cowl_error_handler_free_ctx(&manager->handler);
    uvec_deinit(CowlObjectPtr, &manager->ontos);
    ulib_free(manager);
}

cowl_ret cowl_manager_api_init(void) {
    root_manager = cowl_manager_alloc();
    if (!(root_manager && (root_manager->pm = cowl_prefix_map()))) goto err;
    root_manager->reader = cowl_reader_default();
    root_manager->writer = cowl_writer_default();
    root_manager->handler = (CowlErrorHandler)ulib_zero_init;
    return COWL_OK;

err:
    if (root_manager) {
        cowl_manager_free(root_manager);
        root_manager = NULL;
    }
    return COWL_ERR_MEM;
}

void cowl_manager_api_deinit(void) {
    cowl_release(root_manager);
}

CowlManager *cowl_manager_root(void) {
    return root_manager;
}

CowlManager *cowl_manager(void) {
    return cowl_manager_new_child(root_manager);
}

CowlManager *cowl_manager_get_parent(CowlManager *manager) {
    return manager->parent;
}

CowlManager *cowl_manager_new_child(CowlManager *manager) {
    CowlManager *child = cowl_manager_alloc();
    if (child) child->parent = cowl_retain(manager);
    return child;
}

CowlPrefixMap *cowl_manager_get_prefix_map(CowlManager *manager) {
    if (!manager->pm) manager->pm = cowl_manager_new_prefix_map(manager->parent);
    return manager->pm;
}

CowlPrefixMap *cowl_manager_find_prefix_map(CowlManager *manager) {
    if (manager->pm || !manager->parent) return manager->pm;
    return cowl_manager_find_prefix_map(manager->parent);
}

CowlPrefixMap *cowl_manager_new_prefix_map(CowlManager *manager) {
    CowlPrefixMap *pm = cowl_manager_find_prefix_map(manager);
    return cowl_prefix_map_copy(pm);
}

CowlReader *cowl_manager_get_reader(CowlManager *manager) {
    if (manager->reader.name || !manager->parent) return &manager->reader;
    return cowl_manager_get_reader(manager->parent);
}

CowlWriter *cowl_manager_get_writer(CowlManager *manager) {
    if (manager->writer.name || !manager->parent) return &manager->writer;
    return cowl_manager_get_writer(manager->parent);
}

CowlErrorHandler *cowl_manager_get_error_handler(CowlManager *manager) {
    if (manager->handler.handle_error || !manager->parent) return &manager->handler;
    return cowl_manager_get_error_handler(manager->parent);
}

static CowlOntology *cowl_manager_read_stream_deinit(CowlManager *manager, UIStream *istream) {
    CowlOntology *onto = cowl_manager_read_stream(manager, istream);
    ulib_ret const ret = uistream_deinit(istream);

    if (ulib_is_err(ret)) {
        cowl_handle_ulib_error(ret, manager);
        cowl_release(onto);
        return NULL;
    }

    return onto;
}

static cowl_ret
cowl_manager_write_stream_deinit(CowlManager *manager, CowlOntology *onto, UOStream *stream) {
    cowl_manager_write_stream(manager, onto, stream);
    ulib_ret const ret = uostream_deinit(stream);
    return cowl_handle_ulib_error(ret, manager);
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
    if (ulib_is_err(istream->state)) {
        cowl_handle_ulib_error(istream->state, manager);
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

cowl_ret cowl_manager_write_path(CowlManager *manager, CowlOntology *onto, UString path) {
    UOStream stream;
    uostream_to_path(&stream, ustring_data(path));
    cowl_ret ret = cowl_manager_write_stream_deinit(manager, onto, &stream);
    if (ret) cowl_handle_path_error(path, ustring_literal("failed to write ontology"), manager);
    return ret;
}

cowl_ret cowl_manager_write_file(CowlManager *manager, CowlOntology *onto, FILE *file) {
    UOStream stream;
    uostream_to_file(&stream, file);
    return cowl_manager_write_stream_deinit(manager, onto, &stream);
}

cowl_ret cowl_manager_write_strbuf(CowlManager *manager, CowlOntology *onto, UStrBuf *buf) {
    UOStream stream;
    uostream_to_strbuf(&stream, buf);
    return cowl_manager_write_stream_deinit(manager, onto, &stream);
}

cowl_ret cowl_manager_write_stream(CowlManager *manager, CowlOntology *onto, UOStream *stream) {
    if (ulib_is_err(stream->state)) return cowl_handle_ulib_error(stream->state, manager);
    CowlOStream *ostream = cowl_manager_get_ostream(manager, stream);
    cowl_ret ret = cowl_ostream_write_ontology(ostream, onto);
    cowl_release(ostream);
    return ret;
}

CowlIStream *cowl_manager_get_istream(CowlManager *manager, CowlIStreamHandlers handlers) {
    CowlPrefixMap *pm = cowl_manager_new_prefix_map(manager);
    if (!pm) return NULL;
    CowlIStream *istream = cowl_istream(manager, pm, handlers);
    cowl_release(pm);
    return istream;
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

CowlIStream *cowl_manager_get_istream_to_ontology(CowlManager *manager, CowlOntology *onto) {
    CowlIStreamHandlers handlers = {
        .ctx = onto,
        .iri = store_iri,
        .version = store_version,
        .import = store_import,
        .annot = store_annot,
        .axiom = store_axiom,
    };
    return cowl_istream(manager, cowl_ontology_get_prefix_map(onto), handlers);
}

CowlOStream *cowl_manager_get_ostream(CowlManager *manager, UOStream *stream) {
    return cowl_ostream(manager, stream);
}

void cowl_manager_set_reader(CowlManager *manager, CowlReader reader) {
    cowl_reader_free_ctx(&manager->reader);
    manager->reader = reader;
}

void cowl_manager_set_writer(CowlManager *manager, CowlWriter writer) {
    cowl_writer_free_ctx(&manager->writer);
    manager->writer = writer;
}

void cowl_manager_set_error_handler(CowlManager *manager, CowlErrorHandler handler) {
    cowl_error_handler_free_ctx(&manager->handler);
    manager->handler = handler;
}

ulib_uint cowl_manager_ontology_count(CowlManager *manager) {
    ulib_uint count = uvec_count(CowlObjectPtr, &manager->ontos);
    if (manager->parent) count += cowl_manager_ontology_count(manager->parent);
    return count;
}

bool cowl_manager_iterate_ontologies(CowlManager *manager, CowlIterator *iter) {
    uvec_foreach (CowlObjectPtr, &manager->ontos, onto) {
        if (!cowl_iterator_call(iter, *onto.item)) return false;
    }
    return manager->parent ? cowl_manager_iterate_ontologies(manager->parent, iter) : true;
}

CowlOntology *cowl_manager_new_ontology(CowlManager *manager) {
    return cowl_ontology(manager);
}

CowlOntology *cowl_manager_get_ontology(CowlManager *manager, CowlIRI *iri, CowlIRI *version) {
    CowlOntology *match = NULL;
    uvec_foreach (CowlObjectPtr, &manager->ontos, onto) {
        if (cowl_ontology_get_iri(*onto.item) != iri) continue;
        match = *onto.item;
        if (cowl_ontology_get_version(*onto.item) == version) break;
    }
    if (match) return match;
    if (manager->parent) return cowl_manager_get_ontology(manager->parent, iri, version);
    return NULL;
}

cowl_ret cowl_manager_add_ontology(CowlManager *manager, CowlOntology *onto) {
    return uvec_push(CowlObjectPtr, &manager->ontos, onto) ? COWL_ERR_MEM : COWL_OK;
}

void cowl_manager_remove_ontology(CowlManager *manager, CowlOntology *onto) {
    uvec_remove(CowlObjectPtr, &manager->ontos, onto);
}
