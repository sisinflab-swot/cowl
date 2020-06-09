/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_error.h"
#include "cowl_string_private.h"

VECTOR_IMPL(CowlError)

CowlString* cowl_error_to_string(CowlError error) {
    CowlRawString comp[4];

    if (error.line) {
        comp[0] = cowl_raw_string_with_format("Error %d (line %d) - ", error.code, error.line);
    } else {
        comp[0] = cowl_raw_string_with_format("Error %d - ", error.code);
    }

    // This must not be freed as the underlying string is not copied.
    comp[1] = cowl_raw_string_init_cstring(cowl_ret_t_to_cstring(error.code), false);
    cowl_uint_t n_comp = 2;

    if (error.description) {
        comp[2] = cowl_raw_string_init_static(": ", false);
        comp[3] = error.description->raw_string;
        n_comp = 4;
    }

    CowlRawString raw_string = cowl_raw_string_concat(n_comp, comp);
    cowl_raw_string_deinit(comp[0]);
    return cowl_string_alloc(raw_string);
}
