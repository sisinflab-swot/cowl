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
#include "cowl_manager_private.h"
#include "cowl_ret.h"
#include "cowl_string_private.h"
#include "cowl_vocab_private.h"
#include "ulib.h"

static bool cowl_initialized = false;

cowl_ret cowl_init(void) {
    if (cowl_initialized) return COWL_OK;

    ulib_int seed = (ulib_int)utime_get_ns();
    urand_set_seed(seed ? seed : 12345);

    if (cowl_string_api_init() || cowl_iri_api_init() || cowl_entity_api_init() ||
        cowl_anon_ind_api_init() || cowl_vocab_init() || cowl_manager_api_init()) {
        return COWL_ERR_MEM;
    }

    cowl_initialized = true;
    return COWL_OK;
}

void cowl_deinit(void) {
    if (!cowl_initialized) return;
    cowl_manager_api_deinit();
    cowl_anon_ind_api_deinit();
    cowl_entity_api_deinit();
    cowl_iri_api_deinit();
    cowl_string_api_deinit();
    cowl_vocab_deinit();
    cowl_initialized = false;
}
