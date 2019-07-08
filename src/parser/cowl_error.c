/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_error.h"
#include "cowl_macros.h"
#include "cowl_string_private.h"

VECTOR_IMPL(CowlError)

// This function returns a raw string backed by a static char array, thus you must not free it.
static CowlRawString cowl_error_code_description(CowlErrorCode code) {
    static char const *const cowl_error_code_desc[] = {
        "Unable to load the ontology",
        "Parse error"
    };

    size_t const n_desc = cowl_array_size(cowl_error_code_desc);

    if (code < n_desc) {
        return cowl_raw_string_init_cstring(cowl_error_code_desc[code], false);
    } else {
        return cowl_raw_string_init_static("Unknown error", false);
    }
}

CowlString* cowl_error_to_string(CowlError error) {
    size_t n_comp = 4;
    CowlRawString comp[n_comp];

    if (error.line) {
        comp[0] = cowl_raw_string_with_format("Error %d (line %d) - ", error.code, error.line);
    } else {
        comp[0] = cowl_raw_string_with_format("Error %d - ", error.code);
    }

    comp[1] = cowl_error_code_description(error.code);

    if (error.description) {
        comp[2] = cowl_raw_string_init_static(": ", false);
        comp[3] = error.description->raw_string;
    } else {
        n_comp = 2;
    }

    CowlRawString raw_string = cowl_raw_string_concat(n_comp, comp);
    cowl_raw_string_deinit(comp[0]);
    return cowl_string_alloc(raw_string);
}
