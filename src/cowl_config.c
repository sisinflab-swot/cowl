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
#include "cowl_object.h"
#include "cowl_prefix_map.h"
#include "cowl_prefix_map_private.h"
#include "cowl_reader.h"
#include "cowl_ret.h"
#include "cowl_string_private.h"
#include "cowl_vocab_private.h"
#include "cowl_writer.h"
#include "ulib.h"
#include <stddef.h>

static bool cowl_initialized = false;
static CowlReader *default_reader = NULL;
static CowlWriter *default_writer = NULL;
static CowlPrefixMap *default_prefix_map = NULL;

static void cowl_api_deinit(void) {
    cowl_release(default_reader);
    default_reader = NULL;

    cowl_release(default_writer);
    default_writer = NULL;

    cowl_release(default_prefix_map);
    default_prefix_map = NULL;
}

static cowl_ret cowl_api_init(void) {
    if (!(default_reader = cowl_reader_default())) goto err;
    if (!(default_writer = cowl_writer_default())) goto err;
    if (!(default_prefix_map = cowl_prefix_map())) goto err;
    return COWL_OK;

err:
    cowl_api_deinit();
    return COWL_ERR_MEM;
}

cowl_ret cowl_init(void) {
    if (cowl_initialized) return COWL_OK;

    ulib_int seed = (ulib_int)utime_get_ns();
    urand_set_seed(seed ? seed : 12345);

    if (cowl_string_api_init() || cowl_iri_api_init() || cowl_entity_api_init() ||
        cowl_anon_ind_api_init() || cowl_vocab_init() || cowl_api_init()) {
        cowl_deinit();
        return COWL_ERR_MEM;
    }

    cowl_initialized = true;
    return COWL_OK;
}

void cowl_deinit(void) {
    if (!cowl_initialized) return;
    cowl_api_deinit();
    cowl_anon_ind_api_deinit();
    cowl_entity_api_deinit();
    cowl_iri_api_deinit();
    cowl_string_api_deinit();
    cowl_vocab_deinit();
    cowl_initialized = false;
}

CowlReader *cowl_get_reader(void) {
    return default_reader;
}

void cowl_set_reader(CowlReader *reader) {
    if (reader == default_reader) return;
    cowl_release(default_reader);
    default_reader = cowl_retain(reader);
}

CowlWriter *cowl_get_writer(void) {
    return default_writer;
}

void cowl_set_writer(CowlWriter *writer) {
    if (writer == default_writer) return;
    cowl_release(default_writer);
    default_writer = cowl_retain(writer);
}

CowlPrefixMap *cowl_get_prefix_map(void) {
    return default_prefix_map;
}
