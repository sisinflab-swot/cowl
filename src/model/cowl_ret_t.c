/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ret_t.h"
#include "cowl_string.h"

char const* cowl_ret_t_to_cstring(cowl_ret_t ret) {
    static char const* const ret_desc[COWL_RET_COUNT] = {
        "Success",
        "Failure",
        "Input/output error",
        "Syntax error"
    };

    if (ret < COWL_RET_FIRST || ret >= COWL_RET_COUNT) return "Unknown error";
    return ret_desc[ret];
}

CowlString* cowl_ret_t_to_string(cowl_ret_t ret) {
    char const *cstring = cowl_ret_t_to_cstring(ret);
    return cowl_string_get(cstring, strlen(cstring), true);
}
