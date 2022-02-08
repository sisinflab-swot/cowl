/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ret.h"
#include "cowl_string_private.h"

char const* cowl_ret_to_cstring(cowl_ret ret) {
    switch (ret) {
        case COWL_OK: return "success";
        case COWL_ERR_IO: return "input/output error";
        case COWL_ERR_MEM: return "memory exhausted";
        case COWL_ERR_SYNTAX: return "syntax error";
        case COWL_ERR_IMPORT: return "import error";
        default: return "unknown error";
    }
}

cowl_ret cowl_ret_from_ustream(ustream_ret ret) {
    switch (ret) {
        case USTREAM_OK: return COWL_OK;
        case USTREAM_ERR_BOUNDS:
        case USTREAM_ERR_IO: return COWL_ERR_IO;
        case USTREAM_ERR_MEM: return COWL_ERR_MEM;
        default: return COWL_ERR;
    }
}

cowl_ret cowl_ret_from_uvec(uvec_ret ret) {
    return ret == UVEC_ERR ? COWL_ERR_MEM : COWL_OK;
}

cowl_ret cowl_ret_from_uhash(uhash_ret ret) {
    return ret == UHASH_ERR ? COWL_ERR_MEM : COWL_OK;
}

CowlString* cowl_ret_to_string(cowl_ret ret) {
    char const *cstr = cowl_ret_to_cstring(ret);
    return cowl_string_alloc(ustring_copy(cstr, strlen(cstr)));
}
