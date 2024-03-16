/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_config.h"
#include "cowl_anon_ind_private.h"
#include "cowl_entity_private.h"
#include "cowl_iri_private.h"
#include "cowl_reader.h"
#include "cowl_string_private.h"
#include "cowl_vocab_private.h"
#include "cowl_writer.h"

static bool cowl_initialized = false;
static CowlErrorHandler global_error_handler;
static CowlImportLoader global_import_loader;
static CowlReader global_reader;
static CowlWriter global_writer;

#ifdef COWL_DEFAULT_READER
#define cowl_default_reader() ULIB_MACRO_CONCAT(cowl_reader_, COWL_DEFAULT_READER)()
#else
#define cowl_default_reader() ((CowlReader){ 0 })
#endif

#ifdef COWL_DEFAULT_WRITER
#define cowl_default_writer() ULIB_MACRO_CONCAT(cowl_writer_, COWL_DEFAULT_WRITER)()
#else
#define cowl_default_writer() ((CowlWriter){ 0 })
#endif

static void cowl_config_init(void) {
    global_error_handler = (CowlErrorHandler){ 0 };
    global_import_loader = (CowlImportLoader){ 0 };
    global_reader = cowl_default_reader();
    global_writer = cowl_default_writer();

    ulib_int seed = (ulib_int)utime_get_ns();
    urand_set_seed(seed ? seed : 12345);
}

static void cowl_config_deinit(void) {
    if (global_error_handler.free) global_error_handler.free(global_error_handler.ctx);
    if (global_import_loader.free) global_import_loader.free(global_import_loader.ctx);
}

cowl_ret cowl_init(void) {
    if (cowl_initialized) return COWL_OK;
    cowl_initialized = true;
    cowl_config_init();

    if (cowl_iri_api_init() || cowl_entity_api_init() || cowl_anon_ind_api_init() ||
        cowl_string_api_init() || cowl_vocab_init()) {
        return COWL_ERR_MEM;
    }

    return COWL_OK;
}

void cowl_deinit(void) {
    if (!cowl_initialized) return;
    cowl_anon_ind_api_deinit();
    cowl_entity_api_deinit();
    cowl_iri_api_deinit();
    cowl_string_api_deinit();
    cowl_config_deinit();
    cowl_vocab_deinit();
    cowl_initialized = false;
}

CowlErrorHandler cowl_get_error_handler(void) {
    return (CowlErrorHandler){
        .ctx = global_error_handler.ctx,
        .handle_error = global_error_handler.handle_error,
    };
}

void cowl_set_error_handler(CowlErrorHandler handler) {
    global_error_handler = handler;
}

CowlImportLoader cowl_get_import_loader(void) {
    return (CowlImportLoader){
        .ctx = global_import_loader.ctx,
        .load_ontology = global_import_loader.load_ontology,
    };
}

void cowl_set_import_loader(CowlImportLoader loader) {
    global_import_loader = loader;
}

CowlReader cowl_get_reader(void) {
    return global_reader;
}

CowlWriter cowl_get_writer(void) {
    return global_writer;
}

void cowl_set_reader(CowlReader reader) {
    global_reader = reader;
}

void cowl_set_writer(CowlWriter writer) {
    global_writer = writer;
}
