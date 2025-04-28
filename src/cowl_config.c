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
#include "cowl_error_handler.h"
#include "cowl_iri_private.h"
#include "cowl_reader.h"
#include "cowl_ret.h"
#include "cowl_string_private.h"
#include "cowl_vocab_private.h"
#include "cowl_writer.h"
#include "ulib.h"

static bool cowl_initialized = false;
static CowlErrorHandler global_error_handler;
static CowlReader global_reader;
static CowlWriter global_writer;

static cowl_ret cowl_config_init(void) {
    global_error_handler = (CowlErrorHandler){ 0 };
    global_reader = cowl_reader_default();
    global_writer = cowl_writer_default();
    return COWL_OK;
}

static void cowl_config_deinit(void) {
    cowl_reader_free_ctx(&global_reader);
    cowl_writer_free_ctx(&global_writer);
    cowl_error_handler_free_ctx(&global_error_handler);
}

cowl_ret cowl_init(void) {
    if (cowl_initialized) return COWL_OK;

    ulib_int seed = (ulib_int)utime_get_ns();
    urand_set_seed(seed ? seed : 12345);

    if (cowl_string_api_init() || cowl_iri_api_init() || cowl_entity_api_init() ||
        cowl_anon_ind_api_init() || cowl_vocab_init() || cowl_config_init()) {
        return COWL_ERR_MEM;
    }

    cowl_initialized = true;
    return COWL_OK;
}

void cowl_deinit(void) {
    if (!cowl_initialized) return;
    cowl_config_deinit();
    cowl_vocab_deinit();
    cowl_anon_ind_api_deinit();
    cowl_entity_api_deinit();
    cowl_iri_api_deinit();
    cowl_string_api_deinit();
    cowl_initialized = false;
}

CowlErrorHandler const *cowl_get_error_handler(void) {
    return &global_error_handler;
}

void cowl_set_error_handler(CowlErrorHandler handler) {
    cowl_error_handler_free_ctx(&global_error_handler);
    global_error_handler = handler;
}

CowlReader const *cowl_get_reader(void) {
    return &global_reader;
}

void cowl_set_reader(CowlReader reader) {
    cowl_reader_free_ctx(&global_reader);
    global_reader = reader;
}

CowlWriter const *cowl_get_writer(void) {
    return &global_writer;
}

void cowl_set_writer(CowlWriter writer) {
    cowl_writer_free_ctx(&global_writer);
    global_writer = writer;
}
