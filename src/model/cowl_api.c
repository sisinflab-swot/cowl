/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_api.h"
#include "cowl_facet_private.h"
#include "cowl_vocab_private.h"

static bool cowl_api_initialized = false;

void cowl_api_init(void) {
    if (cowl_api_initialized) return;
    cowl_api_initialized = true;
    cowl_vocab_init();
    cowl_facet_init();
}

void cowl_api_deinit(void) {
    if (!cowl_api_initialized) return;
    cowl_facet_deinit();
    cowl_vocab_deinit();
    cowl_api_initialized = false;
}
